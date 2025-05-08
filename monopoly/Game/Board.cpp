﻿// #include "Board.hpp"
// #include "../Error.hpp"
// #include "../SingletonManager.hpp"
// #include "Tiles/CardStore.hpp"
// #include "Utils/Utils.hpp"
// #include <iomanip>
// #include <iostream>
// #include <map>
// #include <vector>
// #ifdef _WIN32
// #    include <windows.h> // For system("cls")
// #endif

// Board* Board::instance = nullptr;
// std::string resetColor = "\033[0m";

// Board::Board(const GameConfig& config) {
//     throw NotImplement("`Board::Board` not implement");
// }

// void Board::init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players) {
//     throw NotImplement("`Board::init` not implement");
// }

// Board* Board::getInstance(const Config& config) {
//     throw NotImplement("`Board::getInstance` not implement");
// }

// Board* Board::getInstance() {
//     throw NotImplement("`Board::getInstance` not implement");
// }

// void Board::destroyInstance() {
//     throw NotImplement("`Board::destroyInstance` not implement");
// }

// int Board::getSize() const {
//     throw NotImplement("`Board::getSize` not implement");
// }

// std::shared_ptr<Tile> Board::getTile(int index) {
//     throw NotImplement("`Board::getTile` not implement");
// }

// std::vector<std::shared_ptr<Tile>> Board::getTileList() {
//     throw NotImplement("`Board::getTileList` not implement");
// }

// void Board::drawBoard() {
//     throw NotImplement("`Board::drawBoard` not implement");
// }

// void Board::drawMonopolyAscii() {
//     throw NotImplement("`Board::drawMonopolyAscii` not implement");
// }

// void Board::updatePlayerPositions(const std::vector<std::shared_ptr<Player>>& players) {
//     throw NotImplement("`Board::updatePlayerPositions` not implement");
// }

// std::vector<std::shared_ptr<PropertyTile>> Board::getPlayerProperty(const std::shared_ptr<Player>& player) {
//     throw NotImplement("`Board::getPlayerProperty` not implement");
// }

// void Board::updateProperty(const std::vector<std::shared_ptr<Player>>& players) {
//     throw NotImplement("`Board::updateProperty` not implement");
// }

// void Board::clearScreen() {
// #ifdef _WIN32
//     system("cls");
// #else
//     std::cout << "\033[2J\033[H"; // ANSI Escape Code to clear the screen and move the cursor to the top-left corner
// #endif
// }



#include "Board.hpp"
#include "../Error.hpp"
#include "../SingletonManager.hpp"
#include "Tiles/CardStore.hpp"
#include "Utils/Utils.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#ifdef _WIN32
#    include <windows.h> // For system("cls")
#endif

Board* Board::instance = nullptr;
std::string resetColor = "\033[0m";

Board::Board(const GameConfig& config) {
    // 假設建構子什麼都不做
    std::cout << "Board constructed (mock implementation)" << std::endl;
}

void Board::init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players) {
    std::cout << "Board initialized with " << players.size() << " players (mock implementation)" << std::endl;
}

Board* Board::getInstance(const GameConfig& config) {
    if (!instance) {
        instance = new Board(config);
    }
    return instance;
}

Board* Board::getInstance() {
    if (!instance) {
        std::cerr << "Warning: getInstance() called before Board created with config" << std::endl;
    }
    return instance;
}

void Board::destroyInstance() {
    delete instance;
    instance = nullptr;
    std::cout << "Board instance destroyed (mock implementation)" << std::endl;
}

int Board::getSize() const {
    return 0; // 假定目前沒有任何 tile
}

std::shared_ptr<Tile> Board::getTile(int index) {
    std::cerr << "Warning: getTile(" << index << ") returns nullptr (mock implementation)" << std::endl;
    return nullptr;
}

std::vector<std::shared_ptr<Tile>> Board::getTileList() {
    return {}; // 空 vector
}

void Board::drawBoard() {
    std::cout << "[Mock drawBoard] Board would be drawn here." << std::endl;
}

void Board::drawMonopolyAscii() {
    std::cout << "[Mock drawMonopolyAscii] Monopoly ASCII art would be drawn here." << std::endl;
}

void Board::updatePlayerPositions(const std::vector<std::shared_ptr<Player>>& players) {
    std::cout << "[Mock updatePlayerPositions] Updating " << players.size() << " player positions." << std::endl;
}

std::vector<std::shared_ptr<PropertyTile>> Board::getPlayerProperty(const std::shared_ptr<Player>& player) {
    return {}; // 空 vector
}

void Board::updateProperty(const std::vector<std::shared_ptr<Player>>& players) {
    std::cout << "[Mock updateProperty] Updating property info for " << players.size() << " players." << std::endl;
}

void Board::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H"; // ANSI Escape Code to clear the screen and move the cursor to the top-left corner
#endif
}
