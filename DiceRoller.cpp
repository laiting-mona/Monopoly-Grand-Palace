#include "DiceRoller.h"

using namespace std;

/**
 * @brief 建構子，設置隨機數生成器
 */
DiceRoller::DiceRoller() : distribution(1, 6) {}

/**
 * @brief 擲出兩顆骰子，並回傳總和
 *
 * @return 兩顆骰子的總和
 */
int DiceRoller::roll() {
    return distribution(generator) + distribution(generator); // 擲兩顆骰子
}