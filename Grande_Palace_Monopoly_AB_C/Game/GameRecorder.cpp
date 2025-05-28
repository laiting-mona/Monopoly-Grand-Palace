#include "GameRecorder.hpp"
#include "Game/Game.hpp"
#include "Game/Board.hpp"
#include "Game/Player.hpp"
#include "Tiles/PropertyTile.hpp"
#include "InputManager.hpp"
#include <iostream>
#include <fstream>
#if defined(_MSC_VER) && _MSC_VER < 1920
  #include <experimental/filesystem>
  namespace filesystem = std::experimental::filesystem;
#else
  #include <filesystem>
  namespace filesystem = std::filesystem;
#endif


#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

int GameRecorder::currentSaveSlot = 0;
int GameRecorder::currentTurnNumber = 0;
json GameRecorder::logEntries = json::array();

void GameRecorder::startLogging() {
    logEntries.clear();
    currentTurnNumber = 0;
}

void GameRecorder::newTurn() {
    currentTurnNumber++;
}

void GameRecorder::autoSave(Game* game) {
    if (!game) return;

    int playerCount = static_cast<int>(game->players.size());
    int nextIndex = 0;
    if (playerCount > 0) {
        nextIndex = currentTurnNumber % playerCount;
        int start = nextIndex;
        while (game->players[nextIndex] && game->players[nextIndex]->isBankrupt()) {
            nextIndex = (nextIndex + 1) % playerCount;
            if (nextIndex == start) break;
        }
    }

    json state;
    state["turnNumber"] = currentTurnNumber;
    state["nextPlayerIndex"] = nextIndex;
    state["players"] = json::array();

    for (auto& p : game->players) {
        if (!p) continue;
        json pState;
        pState["name"] = p->getName();
        pState["position"] = p->getPosition();
        pState["money"] = p->getMoney();
        pState["isBankrupt"] = p->isBankrupt();
        pState["isInHospital"] = p->isInHospital();
        pState["hospitalRoundLeft"] = p->getHospitalRoundLeft();

        pState["properties"] = json::array();
        auto allTiles = Board::getInstance()->getTileList();
        for (auto& prop : p->getProperties()) {
            int tileId = -1;
            for (int i = 0; i < (int)allTiles.size(); i++) {
                if (allTiles[i] == prop) {
                    tileId = i;
                    break;
                }
            }
            json propState;
            propState["id"] = tileId;
            propState["level"] = static_cast<int>(prop->getPropertyLevel());
            pState["properties"].push_back(propState);
        }

        state["players"].push_back(pState);
    }

    currentSaveSlot = (currentSaveSlot % MAX_SAVES) + 1;
    string dir = "saves/";
    string file = dir + "save" + to_string(currentSaveSlot) + ".json";
    filesystem::create_directories(dir);

    ofstream ofs(file);
    if (!ofs.is_open()) {
        cout << "無法寫入存檔檔案: " << file << endl;
        return;
    }
    ofs << state.dump(4) << endl;
    ofs.close();
}

void GameRecorder::manualSave(Game* game) {
    autoSave(game);
    cout << "手動存檔完成: save" << currentSaveSlot << ".json" << endl;
}

bool GameRecorder::loadRecent(Game* game) {
    if (!game || currentSaveSlot == 0) {
        cout << "沒有可用的存檔檔案。" << endl;
        return false;
    }
    string file = "saves/save" + to_string(currentSaveSlot) + ".json";
    ifstream ifs(file);
    if (!ifs.is_open()) {
        cout << "無法開啟存檔檔案: " << file << endl;
        return false;
    }

    json loaded;
    try {
        ifs >> loaded;
    } catch (...) {
        cout << "存檔格式錯誤，載入失敗。" << endl;
        ifs.close();
        return false;
    }
    ifs.close();

    if (loaded.contains("turnNumber")) {
        currentTurnNumber = loaded["turnNumber"].get<int>();
    }

    if (loaded.contains("players")) {
        auto pList = loaded["players"];
        for (int i = 0; i < (int)pList.size() && i < (int)game->players.size(); i++) {
            auto pData = pList[i];
            auto player = game->players[i];
            if (!player || pData["name"].get<string>() != player->getName()) continue;
            long long mNew = pData["money"].get<long long>();
            long long mCur = player->getMoney();
            if (mNew > mCur) player->addMoney(mNew - mCur);
            else if (mNew < mCur) player->deductMoney(mCur - mNew);
            player->setPosition(pData["position"].get<int>());
            if (pData["isInHospital"].get<bool>()) {
                player->sendToHospital(pData["hospitalRoundLeft"].get<int>());
            } else {
                player->recoverFromHospital();
            }
            auto oldProps = player->getProperties();
            for (auto& op : oldProps) {
                if (op) {
                    op->setPropertyOwner(nullptr);
                    player->removeProperty(op);
                }
            }
            for (auto& pr : pData["properties"]){
                int tid = pr["id"].get<int>();
                auto tile = Board::getInstance()->getTile(tid);
                auto prop = dynamic_pointer_cast<PropertyTile>(tile);
                if (prop) {
                    prop->setPropertyOwner(player);
                    player->addProperty(prop);
                    prop->setPropertyLevel(static_cast<PropertyLevel>(pr["level"].get<int>()));
                }
            }
        }
    }

    if (loaded.contains("nextPlayerIndex")) {
        int idx = loaded["nextPlayerIndex"].get<int>();
        for (auto& pl : game->players) {
            if (pl) pl->setMyTurn(false);
        }
        if (idx >= 0 && idx < (int)game->players.size()) {
            if (game->players[idx]) game->players[idx]->setMyTurn(true);
        }
    }

    cout << "成功載入存檔: " << file << endl;
    return true;
}

void GameRecorder::saveLog() {
    string dir = "saves/";
    filesystem::create_directories(dir);
    string file = dir + "log.json";
    ofstream ofs(file);
    if (!ofs.is_open()) {
        cout << "無法寫入行為紀錄: " << file << endl;
        return;
    }
    ofs << logEntries.dump(4) << endl;
    ofs.close();
}

void GameRecorder::recordDiceRoll(const Player* player, int diceTotal) {
    newTurn();
    if (!player) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "DiceRoll";
    evt["result"] = diceTotal;
    logEntries.push_back(evt);
}

void GameRecorder::recordMove(const Player* player, int fromPos, int toPos) {
    if (!player) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "Move";
    evt["from"] = fromPos;
    evt["to"] = toPos;
    logEntries.push_back(evt);
}

void GameRecorder::recordBuyProperty(const Player* player, const PropertyTile* property, int price) {
    if (!player || !property) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "BuyProperty";
    evt["property"] = property->getName();
    evt["price"] = price;
    logEntries.push_back(evt);
}

void GameRecorder::recordUpgradeProperty(const Player* player, const PropertyTile* property, int cost) {
    if (!player || !property) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "UpgradeProperty";
    evt["property"] = property->getName();
    evt["upgradeLevel"] = static_cast<int>(property->getPropertyLevel());
    evt["cost"] = cost;
    logEntries.push_back(evt);
}

void GameRecorder::recordSellProperty(const Player* player, const PropertyTile* property, int sellPrice) {
    if (!player || !property) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "SellProperty";
    evt["property"] = property->getName();
    evt["sellPrice"] = sellPrice;
    logEntries.push_back(evt);
}

void GameRecorder::recordPayRent(const Player* payer, const Player* owner, int amount) {
    if (!payer || !owner) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = payer->getName();
    evt["action"] = "PayRent";
    evt["paidTo"] = owner->getName();
    evt["amount"] = amount;
    logEntries.push_back(evt);
}

void GameRecorder::recordCardUse(const Player* player, const string& cardName, const string& targetName) {
    if (!player) return;
    json evt;
    evt["turn"] = currentTurnNumber;
    evt["player"] = player->getName();
    evt["action"] = "CardUse";
    evt["card"] = cardName;
    if (!targetName.empty()) evt["target"] = targetName;
    logEntries.push_back(evt);
}

void GameRecorder::replay(Game* game) {
    if (!game) {
        cout << "無效的 Game 指標，無法回放！" << endl;
        return;
    }
    string file = "saves/log.json";
    ifstream ifs(file);
    if (!ifs.is_open()) {
        cout << "找不到行為紀錄檔案: " << file << endl;
        return;
    }
    json events;
    try {
        ifs >> events;
    } catch (...) {
        cout << "行為紀錄格式錯誤，無法回放。" << endl;
        ifs.close();
        return;
    }
    ifs.close();

    auto findPlayer = [&](const string& nm) {
        for (auto& p : game->players) {
            if (p && p->getName() == nm) return p;
        }
        return shared_ptr<Player>(nullptr);
    };

    cout << "===== 回放開始 =====" << endl;
    for (auto& ev : events) {
        string player = ev.value("player", "");
        string action = ev.value("action", "");
        if (action == "DiceRoll") {
            cout << player << " 擲出了 " << ev.value("result", 0) << " 點。" << endl;
        } else if (action == "Move") {
            int from = ev.value("from", -1);
            int to = ev.value("to", -1);
            cout << player << " 從 " << from << " 移動到 " << to << "。" << endl;
            auto p = findPlayer(player);
            if (p) p->setPosition(to);
        } else if (action == "BuyProperty") {
            cout << player << " 購買 " << ev.value("property", "") << " ($" << ev.value("price", 0) << ")。" << endl;
        } else if (action == "UpgradeProperty") {
            cout << player << " 升級 " << ev.value("property", "") << " 至等級 " << ev.value("upgradeLevel", 0)
                 << " (費用 $" << ev.value("cost", 0) << ")。" << endl;
        } else if (action == "SellProperty") {
            cout << player << " 出售 " << ev.value("property", "") << " ($" << ev.value("sellPrice", 0) << ")。" << endl;
        } else if (action == "PayRent") {
            cout << player << " 支付 $" << ev.value("amount", 0) << " 給 " << ev.value("paidTo", "") << "。" << endl;
            auto payer = findPlayer(player);
            auto owner = findPlayer(ev.value("paidTo", ""));
            if (payer) payer->deductMoney(ev.value("amount", 0));
            if (owner) owner->addMoney(ev.value("amount", 0));
        } else if (action == "CardUse") {
            string card = ev.value("card", "");
            if (ev.contains("target")) {
                cout << player << " 使用 " << card << " 對 " << ev.value("target", "") << "。" << endl;
            } else {
                cout << player << " 使用 " << card << "。" << endl;
            }
        }
        InputManager::getKey();
    }
    cout << "===== 回放結束 =====" << endl;
}
