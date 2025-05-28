/**
 * @file Bank.cpp
 * @brief Bank 類別的實作檔案。
 */

#include "Bank.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

Bank* Bank::instance = nullptr;

Bank::Bank() : totalMoneyInBank(15000000) {
    cout << "Bank initialized with $" << totalMoneyInBank << endl;
}

Bank* Bank::getInstance() {
    if (instance == nullptr) {
        instance = new Bank();
    }
    return instance;
}

void Bank::destroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
        cout << "Bank instance destroyed" << endl;
    }
}

void Bank::payToPlayer(shared_ptr<Player> player, long long amount) {
    if (amount <= 0) {
        throw invalid_argument("Payment amount must be positive");
    }
    if (totalMoneyInBank < amount) {
        throw runtime_error("Bank doesn't have enough money");
    }
    player->addMoney(amount);
    totalMoneyInBank -= amount;
    cout << "Bank paid $" << amount << " to " << player->getName()
        << ". Bank balance: $" << totalMoneyInBank << endl;
}

void Bank::receiveFromPlayer(shared_ptr<Player> player, long long amount) {
    if (amount <= 0) {
        throw invalid_argument("Payment amount must be positive");
    }
    if (player->getMoney() < amount) {
        throw runtime_error("Player doesn't have enough money");
    }
    player->deductMoney(amount);
    totalMoneyInBank += amount;
    cout << "Bank received $" << amount << " from " << player->getName()
        << ". Bank balance: $" << totalMoneyInBank << endl;
}

long long Bank::getTotalMoneyInBank() const {
    return totalMoneyInBank;
}