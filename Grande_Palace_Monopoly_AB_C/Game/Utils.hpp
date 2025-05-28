/**
 * @file Utils.hpp
 * @brief �U�ع�Ψ禡�ŧi�A�Ҧp�]�w�����j�p�B����ɶ����C
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <nlohmann/json.hpp>
#ifdef _WIN32
#  include <windows.h>
#endif
#include <string>
#include <utility>
#include <vector>

 /** @brief Set the console window size (only applicable on Windows). */
void setConsoleSize(int width, int height);

/** @brief Pause execution for the specified time in milliseconds. */
void delayTime(long long ms);

/** @brief Remove ANSI escape codes (e.g., color codes) from a string. */
std::string stripAnsi(const std::string& text);

/** @brief Calculate board (row, col) position from a linear index and board size. */
std::pair<int, int> getBoardPosition(int posIndex, int mapSize);

/** @brief Split a string by whitespace into a vector of tokens. */
std::vector<std::string> split(const std::string& str);

/** @brief Pause execution for a given number of milliseconds (alias for delay). */
void delayMilliseconds(int ms);

/** @brief Wait for a key press (cross-platform). */
void waitForKey();

#endif // UTILS_HPP