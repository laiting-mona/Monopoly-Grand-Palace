#include "Bank.hpp"
#include <stdexcept>
#include <iostream>

// Initialize the static instance pointer to nullptr
Bank* Bank::instance = nullptr;

// Private constructor implementation
Bank::Bank() : totalMoneyInBank(15000000) {  // Default starting bank money (15 million)
    std::cout << "Bank initialized with $" << totalMoneyInBank << std::endl;
}

// Static method to get the singleton instance
Bank* Bank::getInstance() {
    if (instance == nullptr) {
        instance = new Bank();
    }
    return instance;
}

// Static method to destroy the singleton instance
void Bank::destroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
        std::cout << "Bank instance destroyed" << std::endl;
    }
}

// Method to pay money from the bank to a player
void Bank::payToPlayer(std::shared_ptr<Player> player, long long amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Payment amount must be positive");
    }
    
    if (totalMoneyInBank < amount) {
        throw std::runtime_error("Bank doesn't have enough money");
    }
    
    player->addMoney(amount);
    totalMoneyInBank -= amount;
    
    std::cout << "Bank paid $" << amount << " to " << player->getName() 
              << ". Bank balance: $" << totalMoneyInBank << std::endl;
}

// Method to receive money from a player to the bank
void Bank::receiveFromPlayer(std::shared_ptr<Player> player, long long amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Payment amount must be positive");
    }
    
    if (player->getMoney() < amount) {
        throw std::runtime_error("Player doesn't have enough money");
    }
    
    player->deductMoney(amount);
    totalMoneyInBank += amount;
    
    std::cout << "Bank received $" << amount << " from " << player->getName() 
              << ". Bank balance: $" << totalMoneyInBank << std::endl;
}

// Getter for the total money in the bank
long long Bank::getTotalMoneyInBank() const {
    return totalMoneyInBank;
}