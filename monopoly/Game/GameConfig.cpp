// #include "GameConfig.hpp"
// #include "../Error.hpp"
// #include "nlohmann/json.hpp"
// #include <exception>
// #include <fstream>
// #include <iostream>
// #include <stdexcept>

// // Initialize the unique `GameConfig` instance
// GameConfig GameConfig::instance;

// GameConfig& GameConfig::getInstance() {
//     return instance;
// }

// void GameConfig::loadConfig() {
//     throw NotImplement("`GameConfig::loadConfig` not implement");
// }

// void GameConfig::setMode(GameMode newMode) {
//     throw NotImplement("`GameConfig::setMode` not implement");
// }

// GameMode GameConfig::getMode() const {
//     throw NotImplement("`GameConfig::getMode` not implement");
// }

// void GameConfig::setPlayersNum(int num) {
//     throw NotImplement("`GameConfig::setPlayersNum` not implement");
// }

// int GameConfig::getPlayersNum() const {
//     throw NotImplement("`GameConfig::getPlayersNum` not implement");
// }

// void GameConfig::setPlayersName(const std::vector<std::string>& names) {
//     throw NotImplement("`GameConfig::setPlayersName` not implement");
// }

// std::vector<std::string> GameConfig::getPlayerNames() const {
//     throw NotImplement("`GameConfig::getPlayerNames` not implement");
// }

// void GameConfig::setPlayerIcons(const std::vector<std::string>& icons) {
//     throw NotImplement("`GameConfig::setPlayerIcons` not implement");
// }

// std::vector<std::string> GameConfig::getPlayerIcons() const {
//     throw NotImplement("`GameConfig::getPlayerIcons` not implement");
// }

// void GameConfig::setPlayerColors(const std::vector<std::string>& icons) {
//     throw NotImplement("`GameConfig::setPlayerColors` not implement");
// }

// std::vector<std::string> GameConfig::getPlayerColors() const {
//     throw NotImplement("`GameConfig::getPlayerColors` not implement");
// }

// void GameConfig::setPropertyLevelIcons(const std::vector<std::string>& icons) {
//     throw NotImplement("`GameConfig::setPropertyLevelIcons` not implement");
// }

// std::vector<std::string> GameConfig::getPropertyLevelIcons() const {
//     throw NotImplement("`GameConfig::getPropertyLevelIcons` not implement");
// }

// std::map<int, std::string> GameConfig::getLocationMap() const {
//     throw NotImplement("`GameConfig::getLocationMap` not implement");
// }

// void GameConfig::setStartMoney(int amount) {
//     throw NotImplement("`GameConfig::setStartMoney` not implement");
// }

// int GameConfig::getStartMoney() const {
//     throw NotImplement("`GameConfig::getStartMoney` not implement");
// }

// void GameConfig::setWinMoney(int amount) {
//     throw NotImplement("`GameConfig::setWinMoney` not implement");
// }

// int GameConfig::getWinMoney() const {
//     throw NotImplement("`GameConfig::getWinMoney` not implement");
// }

// void GameConfig::setPassingStartBonus(int amount) {
//     throw NotImplement("`GameConfig::setPassingStartBonus` not implement");
// }

// int GameConfig::getPassingStartBonus() const {
//     throw NotImplement("`GameConfig::getPassingStartBonus` not implement");
// }

// void GameConfig::setBoardTiles(const std::vector<TileConfig>& tiles) {
//     throw NotImplement("`GameConfig::setBoardTiles` not implement");
// }

// std::vector<TileConfig> GameConfig::getBoardTiles() const {
//     throw NotImplement("`GameConfig::getBoardTiles` not implement");
// }

// void GameConfig::setCards(const std::vector<CardConfig>& cards) {
//     throw NotImplement("`GameConfig::setCards` not implement");
// }

// std::vector<CardConfig> GameConfig::getCards() const {
//     throw NotImplement("`GameConfig::getCards` not implement");
// }

// void GameConfig::setEventValueRange(const std::map<std::string, std::pair<int, int>>& range) {
//     throw NotImplement("`GameConfig::setEventValueRange` not implement");
// }

// std::map<std::string, std::pair<int, int>> GameConfig::getEventValueRange() const {
//     throw NotImplement("`GameConfig::getEventValueRange` not implement");
// }

// void GameConfig::setAnimation(bool status) {
//     throw NotImplement("`GameConfig::setAnimation` not implement");
// }

// bool GameConfig::getAnimation() const {
//     throw NotImplement("`GameConfig::getAnimation()` not implement");
// }

// int GameConfig::getMapSize() const {
//     throw NotImplement("`GameConfig::getMapSize()` not implement");
// }

// int GameConfig::getTileWidth() const {
//     throw NotImplement("`GameConfig::getTileWidth()` not implement");
// }

// long long GameConfig::getAnimationTime() const {
//     throw NotImplement("`GameConfig::getAnimationTime()` not implement");
// }




#include "GameConfig.hpp"
#include "../Error.hpp"
#include "nlohmann/json.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Initialize the unique `GameConfig` instance
GameConfig GameConfig::instance;

GameConfig& GameConfig::getInstance() {
    return instance;
}

void GameConfig::loadConfig() {
    std::cout << "[Mock] Loading config." << std::endl;
}

void GameConfig::setMode(GameMode newMode) {
    std::cout << "[Mock] Setting game mode." << std::endl;
}

GameMode GameConfig::getMode() const {
    std::cout << "[Mock] Getting game mode." << std::endl;
    return GameMode::DEBUG; // 回傳一個預設模式
}

void GameConfig::setPlayersNum(int num) {
    std::cout << "[Mock] Setting players number: " << num << std::endl;
}

int GameConfig::getPlayersNum() const {
    std::cout << "[Mock] Getting players number." << std::endl;
    return 4; // 假設預設 4 人
}

void GameConfig::setPlayersName(const std::vector<std::string>& names) {
    std::cout << "[Mock] Setting players name." << std::endl;
}

std::vector<std::string> GameConfig::getPlayerNames() const {
    std::cout << "[Mock] Getting players name." << std::endl;
    return { "Player1", "Player2", "Player3", "Player4" };
}

void GameConfig::setPlayerIcons(const std::vector<std::string>& icons) {
    std::cout << "[Mock] Setting player icons." << std::endl;
}

std::vector<std::string> GameConfig::getPlayerIcons() const {
    std::cout << "[Mock] Getting player icons." << std::endl;
    return { "icon1", "icon2", "icon3", "icon4" };
}

void GameConfig::setPlayerColors(const std::vector<std::string>& colors) {
    std::cout << "[Mock] Setting player colors." << std::endl;
}

std::vector<std::string> GameConfig::getPlayerColors() const {
    std::cout << "[Mock] Getting player colors." << std::endl;
    return { "red", "blue", "green", "yellow" };
}

void GameConfig::setPropertyLevelIcons(const std::vector<std::string>& icons) {
    std::cout << "[Mock] Setting property level icons." << std::endl;
}

std::vector<std::string> GameConfig::getPropertyLevelIcons() const {
    std::cout << "[Mock] Getting property level icons." << std::endl;
    return { "level1", "level2", "level3" };
}

std::map<int, std::string> GameConfig::getLocationMap() const {
    std::cout << "[Mock] Getting location map." << std::endl;
    return { {0, "Start"}, {1, "Park"}, {2, "Shop"} };
}

void GameConfig::setStartMoney(int amount) {
    std::cout << "[Mock] Setting start money: " << amount << std::endl;
}

int GameConfig::getStartMoney() const {
    std::cout << "[Mock] Getting start money." << std::endl;
    return 1000;
}

void GameConfig::setWinMoney(int amount) {
    std::cout << "[Mock] Setting win money: " << amount << std::endl;
}

int GameConfig::getWinMoney() const {
    std::cout << "[Mock] Getting win money." << std::endl;
    return 10000;
}

void GameConfig::setPassingStartBonus(int amount) {
    std::cout << "[Mock] Setting passing start bonus: " << amount << std::endl;
}

int GameConfig::getPassingStartBonus() const {
    std::cout << "[Mock] Getting passing start bonus." << std::endl;
    return 200;
}

void GameConfig::setBoardTiles(const std::vector<TileConfig>& tiles) {
    std::cout << "[Mock] Setting board tiles." << std::endl;
}

std::vector<TileConfig> GameConfig::getBoardTiles() const {
    std::cout << "[Mock] Getting board tiles." << std::endl;
    return {}; // 回傳空 list
}

void GameConfig::setCards(const std::vector<CardConfig>& cards) {
    std::cout << "[Mock] Setting cards." << std::endl;
}

std::vector<CardConfig> GameConfig::getCards() const {
    std::cout << "[Mock] Getting cards." << std::endl;
    return {}; // 回傳空 list
}

void GameConfig::setEventValueRange(const std::map<std::string, std::pair<int, int>>& range) {
    std::cout << "[Mock] Setting event value range." << std::endl;
}

std::map<std::string, std::pair<int, int>> GameConfig::getEventValueRange() const {
    std::cout << "[Mock] Getting event value range." << std::endl;
    return { {"bonus", {100, 500}}, {"fine", {-300, -100}} };
}

void GameConfig::setAnimation(bool status) {
    std::cout << "[Mock] Setting animation: " << (status ? "ON" : "OFF") << std::endl;
}

bool GameConfig::getAnimation() const {
    std::cout << "[Mock] Getting animation status." << std::endl;
    return false;
}

int GameConfig::getMapSize() const {
    std::cout << "[Mock] Getting map size." << std::endl;
    return 20;
}

int GameConfig::getTileWidth() const {
    std::cout << "[Mock] Getting tile width." << std::endl;
    return 50;
}

long long GameConfig::getAnimationTime() const {
    std::cout << "[Mock] Getting animation time." << std::endl;
    return 1000;
}
