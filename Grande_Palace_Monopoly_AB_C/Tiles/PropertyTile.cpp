/**
 * @file PropertyTile.cpp
 * @brief PropertyTile ���O����@�ɮסC
 */

#include "PropertyTile.hpp"
#include "Game/Player.hpp"
#include "Utils.hpp"
#include <iostream>
#include <sstream>

using namespace std;

PropertyTile::PropertyTile(size_t id, const string& name, int cost, int toll)
    : Tile(id, name)
    , baseCost(cost)
    , baseToll(toll)
    , level(PropertyLevel::VACANT)
    , owner(nullptr) {
    // Initialize upgrade costs for each level (each subsequent level cost is higher)
    upgradeCosts = {
        0,                                   // VACANT (no cost)
        static_cast<int>(baseCost * 0.5),    // Cost to go from Level 1 to 2
        static_cast<int>(baseCost * 0.75),   // Cost to go from Level 2 to 3
        static_cast<int>(baseCost * 1.0)     // Cost to go from Level 3 to MAX_LEVEL
    };
    // Initialize toll rates for each level
    tollRates = {
        0,            // VACANT (no toll)
        baseToll,     // Level 1 toll
        baseToll * 2, // Level 2 toll
        baseToll * 3, // Level 3 toll
        baseToll * 4  // MAX_LEVEL toll
    };
}

TileAction PropertyTile::landOn(shared_ptr<Player> player) {
    if (!player) {
        return TileAction::NONE;
    }
    if (isOwned() && owner != player) {
        cout << player->getName() << " landed on " << name
            << " owned by " << owner->getName() << endl;
        delayMilliseconds(1200);
        payToll(player);
        return TileAction::PAY_TOLL;
    }
    if (isOwned() && owner == player) {
        cout << player->getName() << " landed on their own property: " << name << endl;
        if (canUpgrade()) {
            cout << "You can upgrade this property for $" << getUpgradeCost() << endl;
            delayMilliseconds(1200);
            return TileAction::OWN;
        }
        else {
            cout << "This property is already at maximum level." << endl;
            delayMilliseconds(1200);
            return TileAction::OWN;
        }
    }
    if (!isOwned()) {
        cout << player->getName() << " landed on unowned property: " << name << endl;
        cout << "This property is available for purchase at $" << baseCost << endl;
        delayMilliseconds(1200);
        return TileAction::PURCHASE_PROPERTY;
    }
    return TileAction::NONE;
}

bool PropertyTile::purchase(shared_ptr<Player> player) {
    if (!player || isOwned()) {
        return false;
    }
    if (player->getMoney() < baseCost) {
        cout << player->getName() << " doesn't have enough money to purchase "
            << name << endl;
        delayMilliseconds(1200);
        return false;
    }
    // Deduct money and transfer ownership
    player->deductMoney(baseCost);
    owner = player;
    level = PropertyLevel::LEVEL_1;
    // Add this property to the player's owned properties list
    player->addProperty(static_pointer_cast<PropertyTile>(shared_from_this()));
    cout << player->getName() << " purchased " << name << " for $" << baseCost << endl;
    delayMilliseconds(1200);
    return true;
}

bool PropertyTile::upgrade(shared_ptr<Player> player) {
    if (!player || !isOwned() || owner != player || !canUpgrade()) {
        return false;
    }
    int cost = getUpgradeCost();
    if (player->getMoney() < cost) {
        cout << player->getName() << " doesn't have enough money to upgrade "
            << name << endl;
        delayMilliseconds(1200);
        return false;
    }
    // Deduct money and increase property level
    player->deductMoney(cost);
    level = static_cast<PropertyLevel>(static_cast<int>(level) + 1);
    cout << player->getName() << " upgraded " << name << " to level "
        << static_cast<int>(level) << " for $" << cost << endl;
    cout << "New toll rate: $" << getCurrentToll() << endl;
    delayMilliseconds(1200);
    return true;
}

void PropertyTile::sell(shared_ptr<Player> player) {
    if (!player || !isOwned() || owner != player) {
        return;
    }
    int sellPrice = getSellingPrice();
    // Give money back to player
    player->addMoney(sellPrice);
    // Remove property from player's ownership list
    player->removeProperty(static_pointer_cast<PropertyTile>(shared_from_this()));
    // Reset property to unowned state
    owner = nullptr;
    level = PropertyLevel::VACANT;
    cout << player->getName() << " sold " << name << " for $" << sellPrice << endl;
    delayMilliseconds(1200);
    cout << "Property is now vacant." << endl;
}

void PropertyTile::payToll(shared_ptr<Player> player) {
    if (!player || !isOwned() || owner == player) {
        return;
    }
    int toll = getCurrentToll();
    if (player->getMoney() < toll) {
        cout << player->getName() << " doesn't have enough money to pay the toll!" << endl;
        delayMilliseconds(1200);
        // If player can't afford full toll, take all their money (simplified scenario)
        toll = player->getMoney();
    }
    // Transfer money from the landing player to the owner
    player->deductMoney(toll);
    owner->addMoney(toll);
    cout << player->getName() << " paid $" << toll << " toll to " << owner->getName() << endl;
    delayMilliseconds(1200);
    cout << "Remaining money: $" << player->getMoney() << endl;
    delayMilliseconds(1200);
}

int PropertyTile::getCurrentPrice() const {
    if (!isOwned()) {
        return baseCost;
    }
    // Sum base cost and all upgrade costs up to current level
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
    // Cost to upgrade from current level to next level
    return upgradeCosts[static_cast<int>(level) - 1];
}

shared_ptr<Player> PropertyTile::getPropertyOwner() const {
    return owner;
}

void PropertyTile::setPropertyOwner(shared_ptr<Player> newOwner) {
    owner = newOwner;
    if (!owner) {
        // No owner: property becomes vacant
        level = PropertyLevel::VACANT;
    }
    else if (level == PropertyLevel::VACANT) {
        // If now owned and was vacant, initialize to level 1
        level = PropertyLevel::LEVEL_1;
    }
}

PropertyLevel PropertyTile::getPropertyLevel() const {
    return level;
}

int PropertyTile::getCurrentToll() const {
    // Determine toll based on current property level
    return tollRates[static_cast<int>(level)];
}

int PropertyTile::getSellingPrice() const {
    // For simplicity, selling price is 80% of total investment
    return getCurrentPrice() * 0.8;
}

bool PropertyTile::canUpgrade() const {
    return level < PropertyLevel::MAX_LEVEL;
}

bool PropertyTile::isOwned() const {
    return owner != nullptr;
}

string PropertyTile::getPropertyTypeName() const {
    return "Property";
}

string PropertyTile::getNameWithId() const {
    ostringstream oss;
    oss << id << " " << name;
    if (owner) {
        oss << " (Owner: " << owner->getName() << ", Level " << static_cast<int>(level) << ")";
    }
    else {
        oss << " (Vacant)";
    }
    return oss.str();
}