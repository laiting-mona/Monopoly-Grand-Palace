#include "Board.hpp"
#include "Error.hpp"
#include "Utils.hpp"
#include "Tiles/PropertyTile.hpp"
#include "Tiles/EventTile.hpp"
#include "Tiles/StartTile.hpp"
#include "Tiles/StoreTile.hpp"
#include "Tiles/HospitalTile.hpp"
#include "Tiles/MiniGameTile.hpp"
#include <iostream>
#include <thread> 
#include <chrono>
using namespace std;

// Initialize static instance
Board* Board::instance = nullptr;

Board::Board(const GameConfig& config) {
    mapSize = config.getMapSize();
    tileWidth = config.getTileWidth();
    animation = config.getAnimation();
    animationTime = static_cast<int>(config.getAnimationTime());
    propertyLevelIcons = config.getPropertyLevelIcons();
}

Board* Board::getInstance(const GameConfig& config) {
    if (!instance) {
        instance = new Board(config);
    }
    return instance;
}

Board* Board::getInstance() {
    if (!instance) {
        std::cerr << "Warning: Board::getInstance() called before initialization." << std::endl;
    }
    return instance;
}

void Board::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void Board::init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<MiniGameManager> miniGameManager) {
    // Store players list and initial positions
    playersList = players;
    playersPosition.clear();
    for (auto& p : playersList) {
        p->setPosition(0);
        playersPosition[p] = 0;
    }
    // Create tiles according to configuration
    tiles.clear();
    auto tileConfigs = config.getBoardTiles();
    // Prepare event value ranges
    std::map<std::string, std::pair<int, int>> eventRanges = config.getEventValueRange();
    for (auto& tcfg : tileConfigs) {
        std::string type = tcfg.type;
        for (char& c : type) c = std::tolower(c);
        std::shared_ptr<Tile> tile;
        if (type == "start") {
            tile = std::make_shared<StartTile>(tcfg.id, tcfg.name, config.getPassingStartBonus());
        }
        else if (type == "property") {
            tile = std::make_shared<PropertyTile>(tcfg.id, tcfg.name, tcfg.cost, tcfg.rent);
        }
        else if (type == "fate") {
            int minVal = 0, maxVal = 0;
            if (eventRanges.find("FATE") != eventRanges.end()) {
                minVal = eventRanges["FATE"].first;
                maxVal = eventRanges["FATE"].second;
            }
            tile = std::make_shared<EventTile>(tcfg.id, tcfg.name, EventType::FATE, minVal, maxVal);
        }
        else if (type == "chance") {
            int minVal = 0, maxVal = 0;
            if (eventRanges.find("CHANCE") != eventRanges.end()) {
                minVal = eventRanges["CHANCE"].first;
                maxVal = eventRanges["CHANCE"].second;
            }
            tile = std::make_shared<EventTile>(tcfg.id, tcfg.name, EventType::CHANCE, minVal, maxVal);
        }
        else if (type == "store") {
            tile = std::make_shared<StoreTile>(tcfg.id, tcfg.name);
        }
        else if (type == "hospital") {
            tile = std::make_shared<HospitalTile>(tcfg.id, tcfg.name);
        }
        else if (type == "minigame") {
            tile = std::make_shared<MiniGameTile>(tcfg.id, tcfg.name, miniGameManager); 
        }
        else {
            // Unknown tile type
            tile = nullptr;
        }
        if (tile) {
            tiles.push_back(tile);
        }
    }
}

int Board::getSize() const {
    return static_cast<int>(tiles.size());
}

std::shared_ptr<Tile> Board::getTile(int index) {
    if (index < 0 || index >= static_cast<int>(tiles.size())) {
        throw std::out_of_range("Tile index out of range");
    }
    return tiles[index];
}

std::vector<std::shared_ptr<Tile>> Board::getTileList() {
    return tiles;
}

void Board::drawBoard() {
    playersPosition.clear();
    for (auto& p : playersList) {
        playersPosition[p] = p->getPosition();
    }

    int totalTiles = static_cast<int>(tiles.size());
    if (totalTiles == 0) return;

    int sideLen = mapSize; // 8

    // Index ranges for the board layout
    int topStart = 0;
    int topEnd = sideLen - 2;             // 0~6

    int rightStart = sideLen - 1;             // 7
    int rightEnd = rightStart + sideLen - 2; // 7~13

    int bottomStart = rightEnd + 1;       // 14
    int bottomEnd = bottomStart + sideLen - 2; // 14~20

    int leftStart = bottomEnd + 1;        // 21
    int leftEnd = leftStart + sideLen - 2; // 21~27

    // Top row: 0~6
    for (int i = topStart; i <= topEnd; ++i) {
        printTile(i);
    }
    std::cout << std::endl;

    // Middle rows: left (27~21), right (7~13)
    for (int i = 0; i < sideLen - 1; ++i) {
        int leftIndex = leftEnd - i;     // 27~21
        int rightIndex = rightStart + i; // 7~13

        printTile(leftIndex);
        std::cout << std::string((sideLen - 3) * tileWidth, ' ');
        printTile(rightIndex);
        std::cout << std::endl;
    }

    // Bottom row: 20~14 (reverse order)
    for (int i = bottomEnd; i >= bottomStart; --i) {
        printTile(i);
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "=========================================================================================================================" << std::endl;
    std::cout << std::endl;
}

// void Board::movePlayerStepByStep(std::shared_ptr<Player> player, int steps) {
//     int currentPos = player->getPosition();
//     int totalTiles = static_cast<int>(tiles.size());

//     for (int i = 1; i <= steps; ++i) {
//         int newPos = (currentPos + i) % totalTiles;
//         player->setPosition(newPos);
//         clearScreen();
//         drawBoard();
//         std::this_thread::sleep_for(std::chrono::milliseconds(animationTime));
//     }
// }

void Board::movePlayerStepByStep(std::shared_ptr<Player> player, int steps) {
    int currentPos = player->getPosition();
    int totalTiles = static_cast<int>(tiles.size());

    for (int i = 1; i <= steps; ++i) {
        int newPos = (currentPos + i) % totalTiles;
        auto tile = tiles[newPos];

        // 若該 tile 有障礙物，玩家會強制停在這一格
        if (tile->isBlocked()) {
            std::cout << player->getDisplayName() << " is stopped by a barrier at "
                      << tile->getName() << "!\n";
            delayMilliseconds(1200);
            player->setPosition(newPos);
            tile->setBlock(false);  // 只擋一次
            clearScreen();
            drawBoard();
            std::this_thread::sleep_for(std::chrono::milliseconds(animationTime));
            return;
        }

        // 正常一步步移動
        player->setPosition(newPos);
        clearScreen();
        drawBoard();
        std::this_thread::sleep_for(std::chrono::milliseconds(animationTime));
    }
}

// void Board::printTile(int index) {
//     if (index < 0 || index >= static_cast<int>(tiles.size())) return;

//     auto tile = tiles[index];
//     std::string content = std::to_string(tile->getId()) + ":" + tile->getName();

//     // display property level if applicable
//     if (auto prop = std::dynamic_pointer_cast<PropertyTile>(tile)) {
//         if (prop->isOwned()) {
//             std::string levelStr = "(Lv" + std::to_string(static_cast<int>(prop->getPropertyLevel())) + ")";
//             for (auto& p : playersList) {
//                 if (p == prop->getPropertyOwner()) {
//                     levelStr = p->getColor() + levelStr + "\033[0m";
//                     break;
//                 }
//             }
//             content += levelStr;
//         }
//     }

//     std::string bgColor = "";
//     if (tile->getName() == "START") bgColor = "\033[42m";
//     else if (std::dynamic_pointer_cast<StoreTile>(tile)) bgColor = "\033[43m";
//     else if (std::dynamic_pointer_cast<HospitalTile>(tile)) bgColor = "\033[41m";
//     else if (auto evt = std::dynamic_pointer_cast<EventTile>(tile)) {
//         if (evt->getEventType() == EventType::FATE) bgColor = "\033[44m";
//         else if (evt->getEventType() == EventType::CHANCE) bgColor = "\033[45m";
//     }
//     else if (std::dynamic_pointer_cast<MiniGameTile>(tile)) bgColor = "\033[46m";

//     std::string coloredContent = bgColor.empty() ? content : (bgColor + content + "\033[0m");

//     std::string iconStr;
//     for (auto& p : playersList) {
//         if (p->getPosition() == tile->getId()) {
//             iconStr += p->getIconWithColor();
//         }
//     }

//     std::string total = coloredContent + iconStr;
//     std::string visible = stripAnsi(total);
//     if ((int)visible.size() < tileWidth)
//         total += std::string(tileWidth - visible.size(), ' ');

//     std::cout << total;
// }

void Board::printTile(int index) {
    if (index < 0 || index >= static_cast<int>(tiles.size())) return;

    auto tile = tiles[index];
    std::string content = std::to_string(tile->getId()) + ":" + tile->getName();

    // 顯示地產等級
    if (auto prop = std::dynamic_pointer_cast<PropertyTile>(tile)) {
        if (prop->isOwned()) {
            std::string levelStr = "(Lv" + std::to_string(static_cast<int>(prop->getPropertyLevel())) + ")";
            for (auto& p : playersList) {
                if (p == prop->getPropertyOwner()) {
                    levelStr = p->getColor() + levelStr + "\033[0m";
                    break;
                }
            }
            content += levelStr;
        }
    }

    // 如果這個 tile 被設置了障礙，額外加上黃色字的 (X)
    if (tile->isBlocked()) {
        content += "\033[33m(X)\033[0m";  // 黃色字體
    }
    if (tile->getTollRounds() > 0) {
        content += "\033[33m($)\033[0m";  // 黃色字體表示正在收費
    }

    std::string bgColor = "";
    if (tile->getName() == "START") bgColor = "\033[42m";
    else if (std::dynamic_pointer_cast<StoreTile>(tile)) bgColor = "\033[43m";
    else if (std::dynamic_pointer_cast<HospitalTile>(tile)) bgColor = "\033[41m";
    else if (auto evt = std::dynamic_pointer_cast<EventTile>(tile)) {
        if (evt->getEventType() == EventType::FATE) bgColor = "\033[44m";
        else if (evt->getEventType() == EventType::CHANCE) bgColor = "\033[45m";
    }
    else if (std::dynamic_pointer_cast<MiniGameTile>(tile)) bgColor = "\033[46m";

    std::string coloredContent = bgColor.empty() ? content : (bgColor + content + "\033[0m");

    std::string iconStr;
    for (auto& p : playersList) {
        if (p->getPosition() == tile->getId()) {
            iconStr += p->getIconWithColor();
        }
    }

    std::string total = coloredContent + iconStr;
    std::string visible = stripAnsi(total);
    if ((int)visible.size() < tileWidth)
        total += std::string(tileWidth - visible.size(), ' ');

    std::cout << total;
}

void Board::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}