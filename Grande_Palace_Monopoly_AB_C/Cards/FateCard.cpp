/**
 * @file FateCard.cpp
 * @brief FateCard ���O����@�ɮסC
 */

#include "FateCard.hpp"
#include "Game/Player.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/RocketCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

FateCard::FateCard()
    : Card("Fate", "****", 180, "Trigger a random event") {
    // Initialize the list of fate events and their descriptions
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

void FateCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
    if (fateEvents.empty()) {
        return;
    }
    // Randomly select one fate event to trigger
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<size_t> dist(0, fateEvents.size() - 1);
    size_t eventIndex = dist(rng);
    FateEvent selectedEvent = fateEvents[eventIndex].first;
    string eventDescription = fateEvents[eventIndex].second;
    // Announce the event triggered
    string message = curPlayer->getDisplayName() + " used Fate card and triggered: " + eventDescription + "!";
    cout << message << endl;
    // Apply the effect of the selected fate event
    applyFateEvent(selectedEvent, players, curPlayer);
    // The card is consumed after use (handled by the game engine)
}

void FateCard::applyFateEvent(FateEvent event, vector<shared_ptr<Player>>& players, shared_ptr<Player> player) {
    // Random number generator for events requiring randomness
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    switch (event) {
    case FateEvent::GAIN_MONEY:
        player->addMoney(200);
        break;
    case FateEvent::LOSE_MONEY:
        player->deductMoney(150);
        break;
    case FateEvent::TELEPORT: {
        // Teleport player to a random tile (assuming 0-39 range)
        uniform_int_distribution<int> dist(0, 39);
        int newPosition = dist(rng);
        player->setPosition(newPosition);
        break;
    }
    case FateEvent::MOVE_TO_START:
        player->sendToStart();
        break;
    case FateEvent::GO_TO_HOSPITAL:
        player->sendToHospital(2); // hospital for 2 rounds
        break;
    case FateEvent::DICE_CONTROL: {
        // Give player a random dice control value between 1-6
        uniform_int_distribution<int> dist(1, 6);
        int diceValue = dist(rng);
        player->setDiceControl(diceValue);
        break;
    }
    case FateEvent::GAIN_CARD: {
        // Grant the player a random card (Fate, Barrier, Demolition, Rocket, or Dice Control)
        uniform_int_distribution<int> cardDist(0, 4);
        int cardType = cardDist(rng);
        shared_ptr<Card> newCard;
        switch (cardType) {
        case 0: newCard = make_shared<FateCard>(); break;
        case 1: newCard = make_shared<BarrierCard>(); break;
        case 2: newCard = make_shared<DemolitionCard>(); break;
        case 3: newCard = make_shared<RocketCard>(2); break;
        case 4: newCard = make_shared<DiceControlCard>(); break;
        }
        player->addCard(newCard);
        cout << player->getName() << " received a " << newCard->getName() << " card!" << endl;
        break;
    }
    }
}

void FateCard::addFateEvent(FateEvent event, const string& description) {
    fateEvents.push_back({ event, description });
}

const vector<pair<FateEvent, string>>& FateCard::getFateEvents() const {
    return fateEvents;
}