/**
 * @file DemolitionCard.cpp
 * @brief DemolitionCard ���O����@�ɮסC
 */

#include "DemolitionCard.hpp"
#include "Game/Player.hpp"
#include "Tiles/PropertyTile.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;

DemolitionCard::DemolitionCard()
    : Card("Demolition", "XXXX", 200, "Lower the level of a property by 1")
    , targetProperty(nullptr) {
}
    
void DemolitionCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
    if (!targetProperty) {
        // List all properties owned by players
        std::vector<std::shared_ptr<PropertyTile>> allProps;
        for (const auto& p : players) {
            auto props = p->getProperties();
            allProps.insert(allProps.end(), props.begin(), props.end());
        }

        if (allProps.empty()) {
            std::cout << "There are no properties available for demolition." << std::endl;
            delayMilliseconds(1200);
            return;
        }

        std::cout << "Select a property to demolish:" << std::endl;
        for (size_t i = 0; i < allProps.size(); ++i) {
            std::cout << "[" << i << "] " << allProps[i]->getName()
                      << " (Lv" << static_cast<int>(allProps[i]->getPropertyLevel()) << ")"
                      << " - Owner: " << allProps[i]->getPropertyOwner()->getName()
                      << std::endl;
        }

        int choice = -1;
        std::cin >> choice;
        if (choice < 0 || choice >= static_cast<int>(allProps.size())) {
            std::cout << "Invalid choice, cancelling use." << std::endl;
            delayMilliseconds(1200);
            targetProperty = nullptr; // Reset target
            return;
        }

        targetProperty = allProps[choice];
    }
    // Get current level of the property
    PropertyLevel currentLevel = targetProperty->getPropertyLevel();
    if (currentLevel == PropertyLevel::VACANT) {
        cout << "Property is already vacant and cannot be demolished further." << endl;
        delayMilliseconds(1200);
        targetProperty = nullptr; // Reset target
        return;
    }
    // Determine the new level (one level lower)
    PropertyLevel newLevel;
    switch (currentLevel) {
    case PropertyLevel::LEVEL_1:
        newLevel = PropertyLevel::VACANT;
        break;
    case PropertyLevel::LEVEL_2:
        newLevel = PropertyLevel::LEVEL_1;
        break;
    case PropertyLevel::LEVEL_3:
        newLevel = PropertyLevel::LEVEL_2;
        break;
    case PropertyLevel::MAX_LEVEL:
        newLevel = PropertyLevel::LEVEL_3;
        break;
    default:
        newLevel = PropertyLevel::VACANT;
    }
    // Set the property's new level
    targetProperty->setPropertyLevel(newLevel);
    // If property becomes vacant, remove ownership
    if (newLevel == PropertyLevel::VACANT) {
        shared_ptr<Player> owner = targetProperty->getPropertyOwner();
        if (owner) {
            owner->removeProperty(targetProperty);
            targetProperty->setPropertyOwner(nullptr);
        }
    }
    // Output the demolition result
    string message = curPlayer->getDisplayName() + " used Demolition card on " + targetProperty->getName() +
        ". Level reduced to " + to_string(static_cast<int>(newLevel)) + "!";
    cout << message << endl;
    // The card is consumed after use (handled by the game engine)
}

void DemolitionCard::setTargetProperty(shared_ptr<PropertyTile> property) {
    targetProperty = property;
}

shared_ptr<PropertyTile> DemolitionCard::getTargetProperty() const {
    return targetProperty;
}