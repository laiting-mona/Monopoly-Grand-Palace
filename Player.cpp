#include "Player.h"
#include <iostream>

/**
 * @brief 建構子，創建一個玩家並設置初始金額
 *
 * @param name 玩家名稱
 * @param startingMoney 初始金額
 */
Player::Player(string name, int startingMoney) : name(name), money(startingMoney) {}

/**
 * @brief 調整玩家金錢
 *
 * @param amount 要調整的金額（正負數）
 */
void Player::adjustMoney(int amount) {
    money += amount;
}

/**
 * @brief 顯示玩家的基本資訊（名稱、金錢）
 */
void Player::displayPlayerStatus() const {
    cout << "Player: " << name << endl;
    cout << "Money: " << money << endl;
}