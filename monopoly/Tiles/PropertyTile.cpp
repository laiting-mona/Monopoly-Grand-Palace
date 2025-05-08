#include "PropertyTile.hpp"
#include "Game/Player.hpp"
#include <iostream>
#include <sstream>

PropertyTile::PropertyTile(size_t id, const std::string& name, int cost, int toll)
    : Tile(id, name)
    , baseCost(cost)
    , baseToll(toll)
    , level(PropertyLevel::VACANT)
    , owner(nullptr) {
    
    // Initialize upgrade costs (each level costs 50% more than the previous)
    upgradeCosts = {
        0,                    // No cost for VACANT
        static_cast<int>(baseCost * 0.5),  // Level 1 to 2
        static_cast<int>(baseCost * 0.75), // Level 2 to 3
        static_cast<int>(baseCost * 1.0)   // Level 3 to MAX
    };
    
    // Initialize toll rates (each level increases toll by a multiplier)
    tollRates = {
        0,                   // No toll for VACANT
        baseToll,            // Level 1
        baseToll * 2,        // Level 2
        baseToll * 3,        // Level 3
        baseToll * 4         // MAX_LEVEL
    };
}

TileAction PropertyTile::landOn(std::shared_ptr<Player> player) {
    if (!player) {
        return TileAction::NONE;
    }
    
    if (isBlocked()) {
        std::cout << player->getName() << " landed on a blocked tile: " << name << std::endl;
        setBlock(false); // Remove the block after landing
        return TileAction::NONE;
    }
    
    // If the property is owned by someone else, pay toll
    if (isOwned() && owner != player) {
        std::cout << player->getName() << " landed on " << name 
                  << " owned by " << owner->getName() << std::endl;
        payToll(player);
        return TileAction::PAY_TOLL;
    }
    
    // If the property is owned by the current player, offer upgrade option
    if (isOwned() && owner == player) {
        std::cout << player->getName() << " landed on their own property: " << name << std::endl;
        if (canUpgrade()) {
            std::cout << "You can upgrade this property for $" << getUpgradeCost() << std::endl;
            // The actual upgrade decision would be handled by the game controller
            return TileAction::OWN;
        } else {
            std::cout << "This property is already at maximum level." << std::endl;
            return TileAction::OWN;
        }
    }
    
    // If the property is not owned, offer purchase option
    if (!isOwned()) {
        std::cout << player->getName() << " landed on unowned property: " << name << std::endl;
        std::cout << "This property is available for purchase at $" << baseCost << std::endl;
        // The actual purchase decision would be handled by the game controller
        return TileAction::PURCHASE_PROPERTY;
    }
    
    return TileAction::NONE;
}

bool PropertyTile::purchase(std::shared_ptr<Player> player) {
    if (!player || isOwned()) {
        return false;
    }
    
    // Check if player has enough money
    if (player->getMoney() < baseCost) {
        std::cout << player->getName() << " doesn't have enough money to purchase " 
                  << name << std::endl;
        return false;
    }
    
    // Deduct money and set owner
    player->deductMoney(baseCost);
    owner = player;
    level = PropertyLevel::LEVEL_1;
    
    // Add property to player's properties (assuming Player class has this method)
    player->addProperty(std::static_pointer_cast<PropertyTile>(shared_from_this()));
    
    std::cout << player->getName() << " purchased " << name << " for $" << baseCost << std::endl;
    return true;
}

bool PropertyTile::upgrade(std::shared_ptr<Player> player) {
    if (!player || !isOwned() || owner != player || !canUpgrade()) {
        return false;
    }
    
    int cost = getUpgradeCost();
    
    // Check if player has enough money
    if (player->getMoney() < cost) {
        std::cout << player->getName() << " doesn't have enough money to upgrade " 
                  << name << std::endl;
        return false;
    }
    
    // Deduct money and upgrade level
    player->deductMoney(cost);
    level = static_cast<PropertyLevel>(static_cast<int>(level) + 1);
    
    std::cout << player->getName() << " upgraded " << name << " to level " 
              << static_cast<int>(level) << " for $" << cost << std::endl;
    std::cout << "New toll rate: $" << getCurrentToll() << std::endl;
    
    return true;
}

void PropertyTile::sell(std::shared_ptr<Player> player) {
    if (!player || !isOwned() || owner != player) {
        return;
    }
    
    int sellPrice = getSellingPrice();
    
    // Add money to player
    player->addMoney(sellPrice);
    
    // Remove property from player's properties
    player->removeProperty(std::static_pointer_cast<PropertyTile>(shared_from_this()));
    
    // Reset property status
    owner = nullptr;
    level = PropertyLevel::VACANT;
    
    std::cout << player->getName() << " sold " << name << " for $" << sellPrice << std::endl;
}

void PropertyTile::payToll(std::shared_ptr<Player> player) {
    if (!player || !isOwned() || owner == player) {
        return;
    }
    
    int toll = getCurrentToll();
    
    // Check if player has enough money
    if (player->getMoney() < toll) {
        std::cout << player->getName() << " doesn't have enough money to pay the toll!" << std::endl;
        // Handle bankruptcy or other scenarios
        // For now, just take what they have
        toll = player->getMoney();
    }
    
    // Transfer money from player to owner
    player->deductMoney(toll);
    owner->addMoney(toll);
    
    std::cout << player->getName() << " paid $" << toll << " toll to " 
              << owner->getName() << std::endl;
}

int PropertyTile::getCurrentPrice() const {
    if (!isOwned()) {
        return baseCost;
    }
    
    // Sum up the base cost and all upgrade costs up to the current level
    int totalInvestment = baseCost;
    for (int i = 0; i < static_cast<int>(level) - 1; ++i) {
        totalInvestment += upgradeCosts[i];
    }
    
    return totalInvestment;
}

int PropertyTile::getUpgradeCost() const {
    if (!isOwned() || !canUpgrade()) {
        return 0;
    }
    
    return upgradeCosts[static_cast<int>(level) - 1];
}

std::shared_ptr<Player> PropertyTile::getPropertyOwner() const {
    return owner;
}

void PropertyTile::setPropertyOwner(std::shared_ptr<Player> newOwner) {
    owner = newOwner;
    if (!owner) {
        level = PropertyLevel::VACANT;
    } else if (level == PropertyLevel::VACANT) {
        level = PropertyLevel::LEVEL_1;
    }
}

PropertyLevel PropertyTile::getPropertyLevel() const {
    return level;
}

void PropertyTile::setPropertyLevel(PropertyLevel newLevel) {
    if (newLevel == PropertyLevel::VACANT) {
        owner = nullptr;
    }
    level = newLevel;
}

int PropertyTile::getCurrentToll() const {
    if (!isOwned()) {
        return 0;
    }
    
    return tollRates[static_cast<int>(level)];
}

int PropertyTile::getSellingPrice() const {
    if (!isOwned()) {
        return 0;
    }
    
    // Selling price is 80% of total investment
    return static_cast<int>(getCurrentPrice() * 0.8);
}

bool PropertyTile::canUpgrade() const {
    return isOwned() && level < PropertyLevel::MAX_LEVEL;
}

bool PropertyTile::isOwned() const {
    return owner != nullptr;
}

std::string PropertyTile::getPropertyTypeName() const {
    switch (level) {
        case PropertyLevel::VACANT:
            return "Vacant";
        case PropertyLevel::LEVEL_1:
            return "Level 1";
        case PropertyLevel::LEVEL_2:
            return "Level 2";
        case PropertyLevel::LEVEL_3:
            return "Level 3";
        case PropertyLevel::MAX_LEVEL:
            return "Maximum Level";
        default:
            return "Unknown";
    }
}

std::string PropertyTile::getNameWithId() const {
    std::stringstream ss;
    ss << std::to_string(id) << " " << name;
    
    if (isOwned()) {
        ss << " (Owner: " << owner->getName() << ", Level: " << static_cast<int>(level) << ")";
    } else {
        ss << " (Unowned)";
    }
    
    return ss.str();
}