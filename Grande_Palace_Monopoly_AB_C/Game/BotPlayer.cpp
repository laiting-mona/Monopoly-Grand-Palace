#include "BotPlayer.hpp"
#include "Utils.hpp"
#include "Tiles/PropertyTile.hpp"
#include <iostream>
#include <random>

// Bot decides to purchase property if possible
void BotPlayer::purchaseProperty(std::shared_ptr<PropertyTile> property) {
    if (!property || property->isOwned()) return;
    if (getMoney() >= property->getCurrentPrice()) {
        std::cout << getName() << " (Bot) decides to purchase " << property->getName() << std::endl;
        delayMilliseconds(1200);
        property->purchase(shared_from_this());
    }
}

// Bot decides to upgrade property if possible
void BotPlayer::upgradeProperty(std::shared_ptr<PropertyTile> property) {
    if (!property) return;
    if (property->canUpgrade() && getMoney() >= property->getUpgradeCost()) {
        std::cout << getName() << " (Bot) decides to upgrade " << property->getName() << std::endl;
        delayMilliseconds(1200);
        property->upgrade(shared_from_this());
    }
}