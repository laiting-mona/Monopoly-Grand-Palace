/**
 * @file CardStore.cpp
 * @brief CardStore ���O����@�ɮסC
 */

#include "CardStore.hpp"
#include "Bank.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include "Cards/FateCard.hpp"
#include "Cards/RocketCard.hpp"
#include "Cards/TollCard.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

CardStore* CardStore::instance = nullptr;

CardStore::CardStore(const GameConfig& config) {
    // Initialize store inventory based on game configuration
    vector<CardConfig> cardConfigs = config.getCards();
    for (const auto& cardConfig : cardConfigs) {
        shared_ptr<Card> card;
        if (cardConfig.name == "Fate") {
            card = make_shared<FateCard>();
        }
        else if (cardConfig.name == "Barrier") {
            card = make_shared<BarrierCard>();
        }
        else if (cardConfig.name == "Demolition") {
            card = make_shared<DemolitionCard>();
        }
        else if (cardConfig.name == "Rocket") {
            card = make_shared<RocketCard>(2); // default 2 turns
        }
        else if (cardConfig.name == "DiceControl") {
            card = make_shared<DiceControlCard>();
        }
        else if(cardConfig.name == "Toll"){
            card = make_shared<TollCard>();
        }
        else {
            cout << "Unknown card type: " << cardConfig.name << endl;
            continue;
        }
        cards.push_back(card);
    }
    cout << "Card Store initialized with " << cards.size() << " cards" << endl;
}

CardStore* CardStore::getInstance(const GameConfig& config) {
    if (instance == nullptr) {
        instance = new CardStore(config);
    }
    return instance;
}

CardStore* CardStore::getInstance() {
    if (instance == nullptr) {
        throw runtime_error("CardStore has not been initialized with a GameConfig");
    }
    return instance;
}

void CardStore::destroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
        cout << "Card Store instance destroyed" << endl;
    }
}

void CardStore::displayStore(shared_ptr<Player> player) {
    if (!player) {
        throw invalid_argument("Invalid player pointer");
    }
    cout << "\n===== Card Store =====" << endl;
    cout << "Player: " << player->getName() << " | Available Money: $" << player->getMoney() << endl;
    cout << "-----------------------" << endl;
    if (cards.empty()) {
        cout << "No cards available in the store." << endl;
        return;
    }
    for (size_t i = 0; i < cards.size(); ++i) {
        cout << i + 1 << ". " << cards[i]->getName() << " [" << cards[i]->getIcon() << "]" << endl;
        cout << "   Price: $" << cards[i]->getPrice() << endl;
        cout << "   Effect: " << cards[i]->getEffect() << endl;
        if (player->getMoney() >= cards[i]->getPrice()) {
            cout << "   [AVAILABLE]" << endl;
        }
        else {
            cout << "   [CANNOT AFFORD]" << endl;
        }
        cout << "-----------------------" << endl;
    }
}

void CardStore::purchaseCard(shared_ptr<Player> player, shared_ptr<Card> card) {
    if (!player) {
        throw invalid_argument("Invalid player pointer");
    }
    if (!card) {
        throw invalid_argument("Invalid card pointer");
    }
    auto it = find(cards.begin(), cards.end(), card);
    if (it == cards.end()) {
        throw runtime_error("Card not found in the store");
    }
    if (player->getMoney() < card->getPrice()) {
        throw runtime_error("Player doesn't have enough money to purchase this card");
    }
    Bank* bank = Bank::getInstance();
    bank->receiveFromPlayer(player, card->getPrice());
    player->addCard(card);
    cout << player->getName() << " purchased " << card->getName() << " for $" << card->getPrice() << endl;
    // Remove the card from the store if it's a one-time purchase
    // cards.erase(it);
}

vector<shared_ptr<Card>> CardStore::getCards() const {
    return cards;
}

shared_ptr<Card> CardStore::getCardByName(const string& cardName) const {
    auto it = find_if(cards.begin(), cards.end(), [&cardName](const shared_ptr<Card>& card) {
        return card->getName() == cardName;
        });
    if (it != cards.end()) {
        return *it;
    }
    return nullptr;
}