#include "DemolitionCard.hpp"
#include "Game/Player.hpp"
#include "Tiles/PropertyTile.hpp" // Updated to include PropertyTile instead of Property
#include <iostream>

DemolitionCard::DemolitionCard() 
    : Card("Demolition", "XXXX", 200, "Lower the level of a property by 1")
    , targetProperty(nullptr) {
}

void DemolitionCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    // Check if a target property has been set
    if (!targetProperty) {
        std::cout << "No target property selected for demolition!" << std::endl;
        return;
    }
    
    // Get the current level of the property
    PropertyLevel currentLevel = targetProperty->getPropertyLevel();
    
    // Check if the property has any levels to demolish
    if (currentLevel == PropertyLevel::VACANT) {
        std::cout << "Property is already vacant and cannot be demolished further." << std::endl;
        return;
    }
    
    // Calculate the new level (one level lower)
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
    
    // Update the property level
    targetProperty->setPropertyLevel(newLevel);
    
    // If the level drops to VACANT, the property becomes unowned
    if (newLevel == PropertyLevel::VACANT) {
        std::shared_ptr<Player> owner = targetProperty->getPropertyOwner();
        if (owner) {
            // Remove the property from the owner's list
            owner->removeProperty(targetProperty);
            
            // Set the property as unowned
            targetProperty->setPropertyOwner(nullptr);
        }
    }
    
    // Create a message about the demolition
    std::string message = curPlayer->getDisplayName() + " used Demolition card on " + 
                         targetProperty->getName() + ". Level reduced to " + 
                         std::to_string(static_cast<int>(newLevel)) + "!";
    
    // Display the message
    std::cout << message << std::endl;
    
    // The card is consumed after use (handled by the game engine)
}

void DemolitionCard::setTargetProperty(std::shared_ptr<PropertyTile> property) {
    targetProperty = property;
}

std::shared_ptr<PropertyTile> DemolitionCard::getTargetProperty() const {
    return targetProperty;
}