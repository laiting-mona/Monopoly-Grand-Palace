#include "GainMoneyCommand.hpp"
#include "Game/Utils.hpp"
#include <iostream>

std::string GainMoneyCommand::getName() const {
    return "gain_money";
}

std::string GainMoneyCommand::getDescription() const {
    return "Add money to yourself";
}

void GainMoneyCommand::execute(std::shared_ptr<Player> player) {
    int amount;
    std::cout << "Enter the amount to gain: ";
    std::cin >> amount;
    player->addMoney(amount);
    std::cout << "You received $" << amount << "." << std::endl;
    std::cout << "Current balance: $" << player->getMoney() << std::endl;
    delayMilliseconds(1200);
}
