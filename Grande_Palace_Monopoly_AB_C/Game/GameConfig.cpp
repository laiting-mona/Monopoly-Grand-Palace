#include "GameConfig.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

GameConfig GameConfig::instance;

GameConfig& GameConfig::getInstance() {
    return instance;
}

void GameConfig::setMode(GameMode newMode) {
    mode = newMode;
}

GameMode GameConfig::getMode() const {
    return mode;
}

void GameConfig::setPlayersNum(int num) {
    playersNum = num;
}

int GameConfig::getPlayersNum() const {
    return playersNum;
}

void GameConfig::setPlayersName(const std::vector<std::string>& names) {
    playersName = names;
}

std::vector<std::string> GameConfig::getPlayerNames() const {
    return playersName;
}

void GameConfig::setPlayerIcons(const std::vector<std::string>& icons) {
    playerIcons = icons;
}

std::vector<std::string> GameConfig::getPlayerIcons() const {
    return playerIcons;
}

void GameConfig::setPlayerColors(const std::vector<std::string>& colors) {
    playerColors = colors;
}

std::vector<std::string> GameConfig::getPlayerColors() const {
    return playerColors;
}

void GameConfig::setPropertyLevelIcons(const std::vector<std::string>& icons) {
    propertyLevelIcons = icons;
}

std::vector<std::string> GameConfig::getPropertyLevelIcons() const {
    return propertyLevelIcons;
}

std::map<int, std::string> GameConfig::getLocationMap() const {
    return locationMap;
}

void GameConfig::setStartMoney(int amount) {
    startMoney = amount;
}

int GameConfig::getStartMoney() const {
    return startMoney;
}

void GameConfig::setWinMoney(int amount) {
    winMoney = amount;
}

int GameConfig::getWinMoney() const {
    return winMoney;
}

void GameConfig::setPassingStartBonus(int amount) {
    passingStartBonus = amount;
}

int GameConfig::getPassingStartBonus() const {
    return passingStartBonus;
}

void GameConfig::setBoardTiles(const std::vector<TileConfig>& tiles) {
    boardTiles = tiles;
}

std::vector<TileConfig> GameConfig::getBoardTiles() const {
    return boardTiles;
}

void GameConfig::setCards(const std::vector<CardConfig>& cardList) {
    cards = cardList;
}

std::vector<CardConfig> GameConfig::getCards() const {
    return cards;
}

void GameConfig::setEventValueRange(const std::map<std::string, std::pair<int, int>>& range) {
    eventValueRange = range;
}

std::map<std::string, std::pair<int, int>> GameConfig::getEventValueRange() const {
    return eventValueRange;
}

void GameConfig::setAnimation(bool status) {
    animation = status;
}

bool GameConfig::getAnimation() const {
    return animation;
}

int GameConfig::getMapSize() const {
    return mapSize;
}

int GameConfig::getTileWidth() const {
    return static_cast<int>(tileWidth);
}

long long GameConfig::getAnimationTime() const {
    return animationTime;
}

void GameConfig::loadConfig() {
    using nlohmann::json;
    std::ifstream file("config.json");
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config.json");
    }
    json j;
    file >> j;
    // Load basic arrays
    if (j.contains("playerIcons")) playerIcons = j["playerIcons"].get<std::vector<std::string>>();
    if (j.contains("playerColors")) playerColors = j["playerColors"].get<std::vector<std::string>>();
    if (j.contains("propertyLevelIcons")) propertyLevelIcons = j["propertyLevelIcons"].get<std::vector<std::string>>();
    if (j.contains("tileWidth")) tileWidth = j["tileWidth"];
    if (j.contains("animation")) animation = j["animation"];
    if (j.contains("animationTime")) animationTime = j["animationTime"];
    // Event value ranges
    if (j.contains("eventValueRange")) {
        for (auto it = j["eventValueRange"].begin(); it != j["eventValueRange"].end(); ++it) {
            std::string key = it.key();
            int minVal = it.value()[0];
            int maxVal = it.value()[1];
            eventValueRange[key] = { minVal, maxVal };
        }
    }
    // Modes settings
    if (j.contains("modes")) {
        if (j["modes"].contains("DEBUG")) {
            auto dbg = j["modes"]["DEBUG"];
            startMoney = dbg["startMoney"];
            winMoney = dbg["winMoney"];
            passingStartBonus = dbg["passingStartBonus"];
        }
        if (j["modes"].contains("DUEL")) {
            auto duel = j["modes"]["DUEL"];
            if (mode == GameMode::DUEL) {
                startMoney = duel["startMoney"];
                winMoney = duel["winMoney"];
                passingStartBonus = duel["passingStartBonus"];
            }
        }
    }
    // Map and tiles
    if (j.contains("mapSize")) mapSize = j["mapSize"];
    if (j.contains("boardTiles")) {
        boardTiles.clear();
        for (auto& jt : j["boardTiles"]) {
            TileConfig tc;
            tc.id = jt["index"];
            tc.type = jt["type"];
            tc.name = jt["name"];
            tc.cost = jt["price"];
            tc.rent = jt["toll"];
            boardTiles.push_back(tc);
        }
    }
    if (j.contains("cards")) {
        cards.clear();
        for (auto& jc : j["cards"]) {
            CardConfig cc;
            cc.name = jc["name"];
            cc.icon = jc["icon"];
            cc.price = jc["price"];
            cc.effect = jc["effect"];
            cards.push_back(cc);
        }
    }
}