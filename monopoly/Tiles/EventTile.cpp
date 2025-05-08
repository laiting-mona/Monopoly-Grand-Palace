#include "EventTile.hpp"
#include "Game/Player.hpp"
#include <iostream>
#include <random>
#include <ctime>

std::mt19937 EventTile::rng(static_cast<unsigned int>(std::time(nullptr)));

EventTile::EventTile(size_t id, const std::string& name, EventType type, int minVal, int maxVal)
    : Tile(id, name)
    , eventType(type)
    , minValue(minVal)
    , maxValue(maxVal)
    {
    
    // Initialize default positive event messages
    positiveEvents = {
        "You unexpectedly found a wallet and gained $%d.",
        "You won a small lottery and gained $%d.",
        "You received a tax refund of $%d.",
        "Your investments paid off, you gained $%d.",
        "You received a bonus at work, gaining $%d."
    };
    
    // Initialize default negative event messages
    negativeEvents = {
        "Your phone broke, and you spent $%d to replace it.",
        "You had to pay medical bills of $%d.",
        "Your car needed repairs, costing you $%d.",
        "You lost money in a bad investment, losing $%d.",
        "You were fined $%d for a parking violation."
    };
    
    // Add additional messages based on event type
    if (type == EventType::CHANCE) {
        positiveEvents.push_back("You made a big profit in real estate and gained $%d!");
        positiveEvents.push_back("You won the jackpot and gained $%d!");
        positiveEvents.push_back("You inherited $%d from a distant relative!");
        
        negativeEvents.push_back("You were scammed by a fraud group and lost $%d...");
        negativeEvents.push_back("Your business venture failed and you lost $%d.");
        negativeEvents.push_back("You had to pay a lawsuit settlement of $%d.");
    }
}

TileAction EventTile::landOn(std::shared_ptr<Player> player) {
    if (!player) {
        return TileAction::NONE;
    }
    
    if (isBlocked()) {
        std::cout << player->getName() << " landed on a blocked tile: " << name << std::endl;
        setBlock(false); // Remove the block after landing
        return TileAction::NONE;
    }
    
    // Generate a random event value
    int eventValue = generateEventValue();
    
    // Determine if this is a positive or negative event
    bool isPositive = (eventValue > 0);
    
    // Get a random event message
    std::string eventMessage = getRandomEventMessage(isPositive);
    
    // Format the message with the actual value
    char formattedMessage[256];
    snprintf(formattedMessage, sizeof(formattedMessage), eventMessage.c_str(), std::abs(eventValue));
    
    // Display the event message with the event type
    std::cout << "[" << getEventTypeName() << "] " << formattedMessage << std::endl;
    
    // Apply the event effect to the player
    if (eventValue > 0) {
        player->addMoney(eventValue);
    } else if (eventValue < 0) {
        player->deductMoney(std::abs(eventValue));
    }
    
    return TileAction::SPECIAL_EVENT;
}

int EventTile::generateEventValue() const {
    // Create distribution for the range
    std::uniform_int_distribution<int> valueDist(minValue, maxValue);
    
    // Generate a random value
    int randomValue = valueDist(rng);
    
    // 50% chance of it being negative
    std::uniform_int_distribution<int> signDist(0, 1);
    bool isNegative = (signDist(rng) == 0);
    
    return isNegative ? -randomValue : randomValue;
}

std::string EventTile::getRandomEventMessage(bool isPositive) const {
    const std::vector<std::string>& messages = isPositive ? positiveEvents : negativeEvents;
    
    if (messages.empty()) {
        return isPositive ? "You gained $%d." : "You lost $%d.";
    }
    
    // Select a random message
    std::uniform_int_distribution<size_t> dist(0, messages.size() - 1);
    size_t index = dist(rng);
    
    return messages[index];
}

EventType EventTile::getEventType() const {
    return eventType;
}

std::string EventTile::getEventTypeName() const {
    switch (eventType) {
        case EventType::FATE:
            return "Fate";
        case EventType::CHANCE:
            return "Chance";
        default:
            return "Unknown";
    }
}

void EventTile::setValueRange(int minVal, int maxVal) {
    if (minVal < maxVal) {
        minValue = minVal;
        maxValue = maxVal;
    }
}

void EventTile::addPositiveEvent(const std::string& message) {
    positiveEvents.push_back(message);
}

void EventTile::addNegativeEvent(const std::string& message) {
    negativeEvents.push_back(message);
}