/**
 * @file StoreTile.cpp
 * @brief StoreTile ���O����@�ɮסC
 */

#include "StoreTile.hpp"
#include "Game/Player.hpp"
#include "Game/BotPlayer.hpp"
#include "Cards/Card.hpp"
#include "Cards/FateCard.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/RocketCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include "Cards/TollCard.hpp"
#include "Utils.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

StoreTile::StoreTile(int position, const std::string& name)
    : Tile(position, name), maxCardsInStock(5) {
    // Initialize store with some cards in stock
    restockCards();
}

TileAction StoreTile::landOn(shared_ptr<Player> player) {
    cout << player->getDisplayName() << " landed on " << getName() << "!" << endl;
    cout << "Welcome to the Card Store! Would you like to buy a card?" << endl;
    delayMilliseconds(1200);
    // Show available cards to the player
    displayAvailableCards();
    auto bot = std::dynamic_pointer_cast<BotPlayer>(player);
    if (bot) {
        auto stock = getAvailableCards();
        for (size_t i = 0; i < stock.size(); ++i) {
            if (player->getMoney() >= stock[i]->getPrice()) {
                purchaseCard(i, player);
                break;
            }
        }
    } else {
        std::cout << "Do you want to buy a card? (Enter card number, 0 to skip): ";
        int choice;
        std::cin >> choice;
        if (choice > 0) {
            purchaseCard(choice - 1, player);
        }
    }
    return TileAction::STORE;
}

void StoreTile::displayAvailableCards() {
    if (availableCards.empty()) {
        cout << "No cards currently in stock. Check back later!" << endl;
        delayMilliseconds(1200);
        return;
    }
    cout << "Available Cards:" << endl;
    for (size_t i = 0; i < availableCards.size(); ++i) {
        auto card = availableCards[i];
        cout << i + 1 << ". " << card->getName() << " - $" << card->getPrice()
            << " - " << card->getEffect() << endl;
    }
    delayMilliseconds(1200);
}

bool StoreTile::purchaseCard(int cardIndex, shared_ptr<Player> player) {
    // Validate selected index
    if (cardIndex < 0 || cardIndex >= static_cast<int>(availableCards.size())) {
        cout << "Invalid card selection." << endl;
        delayMilliseconds(1200);
        return false;
    }
    auto selectedCard = availableCards[cardIndex];
    long long cardPrice = selectedCard->getPrice();
    // Check player funds
    if (player->getMoney() < cardPrice) {
        cout << "Not enough money to purchase this card." << endl;
        delayMilliseconds(1200);
        return false;
    }
    // Deduct money and give card to player
    if (player->deductMoney(cardPrice)) {
        player->addCard(selectedCard);
        cout << player->getDisplayName() << " purchased " << selectedCard->getName()
            << " for $" << cardPrice << "." << endl;
        delayMilliseconds(1200);
        // Remove the card from store inventory
        availableCards.erase(availableCards.begin() + cardIndex);
        // Restock if empty
        if (availableCards.empty()) {
            cout << "Store inventory is now empty. Restocking..." << endl;
            delayMilliseconds(1200);
            restockCards();
        }
        return true;
    }
    cout << "Transaction failed." << endl;
    delayMilliseconds(1200);
    return false;
}

void StoreTile::restockCards() {
    // Clear current inventory and add random new cards up to stock limit
    availableCards.clear();
    for (int i = 0; i < maxCardsInStock; ++i) {
        availableCards.push_back(createRandomCard());
    }
}

shared_ptr<Card> StoreTile::createRandomCard() {
    // Randomly generate one of the card types to stock
    mt19937 rng(static_cast<unsigned int>(time(nullptr) + rand()));
    uniform_int_distribution<int> dist(0, 5); // 6 different card types
    int cardType = dist(rng);
    shared_ptr<Card> newCard;
    switch (cardType) {
    case 0: newCard = make_shared<FateCard>(); break;
    case 1: newCard = make_shared<BarrierCard>(); break;
    case 2: newCard = make_shared<DemolitionCard>(); break;
    case 3: newCard = make_shared<RocketCard>(2); break;
    case 4: newCard = make_shared<DiceControlCard>(); break;
    case 5: newCard = make_shared<TollCard>(); break;
    default: newCard = nullptr; break;
    }
    return newCard;
}

void StoreTile::addCardToInventory(shared_ptr<Card> card) {
    if (availableCards.size() < static_cast<size_t>(maxCardsInStock)) {
        availableCards.push_back(card);
        cout << "Added " << card->getName() << " to store inventory." << endl;
        delayMilliseconds(1200);
    }
    else {
        cout << "Store inventory is full. Cannot add more cards." << endl;
        delayMilliseconds(1200);
    }
}

vector<shared_ptr<Card>> StoreTile::getAvailableCards() const {
    return availableCards;
}

int StoreTile::getMaxCardsInStock() const {
    return maxCardsInStock;
}

void StoreTile::setMaxCardsInStock(int max) {
    maxCardsInStock = max;
}