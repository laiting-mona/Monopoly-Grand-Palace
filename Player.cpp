#include "Player.h"
#include <iostream>

/**
 * @brief �غc�l�A�Ыؤ@�Ӫ��a�ó]�m��l���B
 *
 * @param name ���a�W��
 * @param startingMoney ��l���B
 */
Player::Player(string name, int startingMoney) : name(name), money(startingMoney) {}

/**
 * @brief �վ㪱�a����
 *
 * @param amount �n�վ㪺���B�]���t�ơ^
 */
void Player::adjustMoney(int amount) {
    money += amount;
}

/**
 * @brief ��ܪ��a���򥻸�T�]�W�١B�����^
 */
void Player::displayPlayerStatus() const {
    cout << "Player: " << name << endl;
    cout << "Money: " << money << endl;
}