#include "FateCard.hpp"
#include "Game/Player.hpp"
#include <random>
#include <ctime>
#include <iostream> // For logging messages

FateCard::FateCard() 
    : Card("Fate", "****", 180, "Trigger a random event") {
    // Initialize the list of fate events with their descriptions
    fateEvents = {
        {FateEvent::GAIN_MONEY, "Gain 200 money"},
        {FateEvent::LOSE_MONEY, "Lose 150 money"},
        {FateEvent::TELEPORT, "Teleport to a random tile"},
        {FateEvent::MOVE_TO_START, "Move to the start position"},
        {FateEvent::GO_TO_HOSPITAL, "Go to hospital for 2 rounds"},
        {FateEvent::DICE_CONTROL, "Control your next dice roll"},
        {FateEvent::GAIN_CARD, "Gain a random card"}
    };
}

void FateCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    // Make sure we have fate events to choose from
    if (fateEvents.empty()) {
        return;
    }
    
    // Random number generator
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, fateEvents.size() - 1);
    
    // Select a random fate event
    size_t eventIndex = dist(rng);
    FateEvent selectedEvent = fateEvents[eventIndex].first;
    std::string eventDescription = fateEvents[eventIndex].second;
    
    // Create a message about the effect
    std::string message = curPlayer->getDisplayName() + " used Fate card and triggered: " + 
                          eventDescription + "!";
    
    // Display or log the message
    std::cout << message << std::endl;
    
    // Apply the selected fate event
    applyFateEvent(selectedEvent, players, curPlayer);
    
    // The card is consumed after use (handled by the game engine)
}

void FateCard::applyFateEvent(FateEvent event, std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> player) {
    // Random number generator for events that need randomization
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    
    switch (event) {
        case FateEvent::GAIN_MONEY:
            player->addMoney(200);
            break;
            
        case FateEvent::LOSE_MONEY:
            player->deductMoney(150);
            break;
            
        case FateEvent::TELEPORT: {
            // Random position on the board (assuming the board has 40 tiles)
            std::uniform_int_distribution<int> dist(0, 39);
            int newPosition = dist(rng);
            player->setPosition(newPosition);
            break;
        }
            
        case FateEvent::MOVE_TO_START:
            player->sendToStart();
            break;
            
        case FateEvent::GO_TO_HOSPITAL:
            player->sendToHospital(2); // Send to hospital for 2 rounds
            break;
            
        case FateEvent::DICE_CONTROL: {
            // Set dice control to a random value between 1-6
            std::uniform_int_distribution<int> dist(1, 6);
            int diceValue = dist(rng);
            player->setDiceControl(diceValue);
            break;
        }
            
        case FateEvent::GAIN_CARD: {
            // This would need to be implemented by creating a new card
            // and adding it to the player's inventory
            // Since we don't have access to card creation logic, this is a placeholder
            std::cout << "Player would gain a card here, but implementation depends on game engine" << std::endl;
            break;
        }
    }
}

void FateCard::addFateEvent(FateEvent event, const std::string& description) {
    fateEvents.push_back({event, description});
}

const std::vector<std::pair<FateEvent, std::string>>& FateCard::getFateEvents() const {
    return fateEvents;
}