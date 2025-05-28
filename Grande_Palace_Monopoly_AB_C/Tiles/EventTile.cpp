/**
 * @file EventTile.cpp
 * @brief EventTile ���O����@�ɮסC
 */

#include "EventTile.hpp"
#include "Game/Player.hpp"
#include "Utils.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdio>
#include <cmath>

using namespace std;

// Initialize static random number generator
std::mt19937 EventTile::rng(static_cast<unsigned int>(time(nullptr)));

EventTile::EventTile(size_t id, const std::string& name, EventType type, int minVal, int maxVal)
    : Tile(id, name), eventType(type), minValue(minVal), maxValue(maxVal) {
    // Default positive event messages
    positiveEvents = {
        "You unexpectedly found a wallet and gained $%d.",
        "You won a small lottery and gained $%d.",
        "You received a tax refund of $%d.",
        "Your investments paid off, you gained $%d.",
        "You received a bonus at work, gaining $%d."
    };
    // Default negative event messages
    negativeEvents = {
        "Your phone broke, and you spent $%d to replace it.",
        "You had to pay medical bills of $%d.",
        "Your car needed repairs, costing you $%d.",
        "You lost money in a bad investment, losing $%d.",
        "You were fined $%d for a parking violation."
    };
    // Additional messages for CHANCE type events
    if (type == EventType::CHANCE) {
        positiveEvents.push_back("You made a big profit in real estate and gained $%d!");
        positiveEvents.push_back("You won the jackpot and gained $%d!");
        positiveEvents.push_back("You inherited $%d from a distant relative!");
        negativeEvents.push_back("You were scammed by a fraud group and lost $%d...");
        negativeEvents.push_back("Your business venture failed and you lost $%d.");
        negativeEvents.push_back("You had to pay a lawsuit settlement of $%d.");
    }
}

TileAction EventTile::landOn(shared_ptr<Player> player) {
    if (!player) {
        return TileAction::NONE;
    }
    // Generate a random event outcome value
    int eventValue = generateEventValue();
    bool isPositive = (eventValue > 0);
    // Select an appropriate event message
    string eventMessage = getRandomEventMessage(isPositive);
    char formattedMessage[256];
    snprintf(formattedMessage, sizeof(formattedMessage), eventMessage.c_str(), abs(eventValue));
    // Display the event message with event type tag
    cout << "Triggered a " << getEventTypeName() << " event!" << endl;
    cout << "[" << getEventTypeName() << "] " << formattedMessage << endl;
    // Apply the effect of the event (money gain or loss)
    if (eventValue > 0) {
        player->addMoney(eventValue);
    }
    else if (eventValue < 0) {
        player->deductMoney(abs(eventValue));
    }
    cout << player->getDisplayName() << " now has $" << player->getMoney() << "." << endl;
    waitForKey();
    return TileAction::SPECIAL_EVENT;
}

int EventTile::generateEventValue() const {
    // Random value between min and max
    uniform_int_distribution<int> valueDist(minValue, maxValue);
    int randomValue = valueDist(rng);
    // 50% chance to make it negative
    uniform_int_distribution<int> signDist(0, 1);
    bool isNegative = (signDist(rng) == 0);
    return isNegative ? -randomValue : randomValue;
}

string EventTile::getRandomEventMessage(bool isPositive) const {
    const vector<string>& messages = isPositive ? positiveEvents : negativeEvents;
    if (messages.empty()) {
        return isPositive ? "You gained $%d." : "You lost $%d.";
    }
    uniform_int_distribution<size_t> dist(0, messages.size() - 1);
    size_t index = dist(rng);
    return messages[index];
}

EventType EventTile::getEventType() const {
    return eventType;
}

string EventTile::getEventTypeName() const {
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

void EventTile::addPositiveEvent(const string& message) {
    positiveEvents.push_back(message);
}

void EventTile::addNegativeEvent(const string& message) {
    negativeEvents.push_back(message);
}