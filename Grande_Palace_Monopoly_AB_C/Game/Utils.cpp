#include "Utils.hpp"
#include "Error.hpp"
#include <chrono>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <iostream>

#ifdef _WIN32
void setConsoleSize(int width, int height) {
    std::string command = "mode con: cols=" + std::to_string(width) + " lines="
        + std::to_string(height);
    system(command.c_str());
}
#else
void setConsoleSize(int width, int height) {
    std::string command = "stty cols " + std::to_string(width) + " rows " +
        std::to_string(height);
    system(command.c_str());
}
#endif

void delayTime(long long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string stripAnsi(const std::string& text) {
    std::regex ansi_pattern("\033\\[[0-9;]*[A-Za-z]");
    return std::regex_replace(text, ansi_pattern, "");
}

std::pair<int, int> getBoardPosition(int posIndex, int mapSize) {
    // Simple linear mapping (not implemented fully for multi-layer)
    int x = posIndex % mapSize;
    int y = posIndex / mapSize;
    return { x, y };
}

void delayMilliseconds(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

#ifdef _WIN32
#include <conio.h>
void waitForKey() {
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
}
#else
#include <limits>
void waitForKey() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
#endif