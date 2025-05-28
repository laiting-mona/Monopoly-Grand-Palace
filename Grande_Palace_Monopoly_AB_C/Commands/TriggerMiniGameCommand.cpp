#include "TriggerMiniGameCommand.hpp"
#include "Game/Utils.hpp"
#include <iostream>

std::string TriggerMiniGameCommand::getName() const {
    return "trigger_mini";
}

std::string TriggerMiniGameCommand::getDescription() const {
    return "Trigger a mini-game manually";
}

void TriggerMiniGameCommand::execute(std::shared_ptr<Player> player) {
    std::cout << "Mini-game executed." << std::endl;
    delayMilliseconds(1200);
    Game::getInstance()->getMiniGameManager()->playMiniGame(player);
}
