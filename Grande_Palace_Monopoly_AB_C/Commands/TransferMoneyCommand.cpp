#include "TransferMoneyCommand.hpp"
#include "Game/Utils.hpp"
#include <iostream>

std::string TransferMoneyCommand::getName() const {
    return "transfer_money";
}

std::string TransferMoneyCommand::getDescription() const {
    return "Transfer money to another player";
}

void TransferMoneyCommand::execute(std::shared_ptr<Player> player) {
    auto game = Game::getInstance();
    std::vector<std::shared_ptr<Player>> others;
    int idx = 1;

    std::cout << "Available players to transfer to:" << std::endl;
    for (const auto& p : game->getPlayers()) {
        if (p != player && !p->isBankrupt()) {
            std::cout << idx << ". " << p->getDisplayName() << std::endl;
            others.push_back(p);
            idx++;
        }
    }

    if (others.empty()) {
        std::cout << "No valid players to transfer to." << std::endl;
        return;
    }

    int choice, amount;
    std::cout << "Select player index: ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(others.size())) {
        std::cout << "Invalid choice." << std::endl;
        return;
    }

    std::cout << "Enter amount to transfer: ";
    std::cin >> amount;

    if (player->deductMoney(amount)) {
        others[choice - 1]->addMoney(amount);
        std::cout << "Transferred $" << amount << " successfully." << std::endl;
        std::cout << "Your new balance: $" << player->getMoney() << std::endl;
        delayMilliseconds(1200);
    } 
    else {
        std::cout << "Transfer failed: not enough money." << std::endl;
        delayMilliseconds(1200);
    }
}
