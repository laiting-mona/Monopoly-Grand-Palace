#include "ChangePhaseCommand.hpp"
#include <iostream>

std::string ChangePhaseCommand::getName() const {
    return "change_phase";
}

std::string ChangePhaseCommand::getDescription() const {
    return "Manually change the game phase (for debugging)";
}

void ChangePhaseCommand::execute(std::shared_ptr<Player> player) {
    // int phase;
    // std::cout << "Enter new phase ID (int): ";
    // std::cin >> phase;
    // Game::getInstance()->changeState(static_cast<Game::State>(phase));
    // std::cout << "Game phase updated." << std::endl;
}
