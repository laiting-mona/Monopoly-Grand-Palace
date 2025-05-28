#include "GainCardCommand.hpp"
#include "Cards/FateCard.hpp"
#include "Game/Utils.hpp"
#include <iostream>

std::string GainCardCommand::getName() const {
    return "gain_card";
}

std::string GainCardCommand::getDescription() const {
    return "Add a random card to your inventory";
}

void GainCardCommand::execute(std::shared_ptr<Player> player) {
    auto card = std::make_shared<FateCard>();
    player->addCard(card);
    std::cout << "You received a card: " << card->getName() << std::endl;
    delayMilliseconds(1200);
}
