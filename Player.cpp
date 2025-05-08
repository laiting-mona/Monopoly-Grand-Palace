#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int money)
    : name_(name), money_(money) {}

void Player::adjustMoney(int amount) {
    money_ += amount;
}

void Player::displayPlayerStatus() const {
    std::cout << name_ << " 現有金額: " << money_ << std::endl;
}

bool Player::hasWon(int winAmount) const {
    return money_ >= winAmount;
}

int Player::getMoney() const {
    return money_;
}

std::string Player::getName() const {
    return name_;
}
