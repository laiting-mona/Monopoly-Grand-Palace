#include "StoreTile.hpp"
#include "Game/Player.hpp"
#include "Cards/Card.hpp"
#include "Cards/FateCard.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/RocketCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include <iostream>
#include <random>
#include <ctime>

StoreTile::StoreTile(int position, const std::string& name)
    : Tile(position, name), maxCardsInStock(5) {
    // Initialize the store with some cards
    restockCards();
}

TileAction StoreTile::landOn(std::shared_ptr<Player> player) {
    std::cout << player->getDisplayName() << " landed on " << getName() << "!" << std::endl;
    std::cout << "Welcome to the Card Store! Would you like to buy a card?" << std::endl;
    
    // Display available cards
    displayAvailableCards();
    
    // The actual card purchasing logic would be handled by the game's UI/controller
    // This function just notifies the player they've landed on a store tile
    return TileAction::STORE;
}

void StoreTile::displayAvailableCards() {
    std::cout << "Available Cards:" << std::endl;
    
    if (availableCards.empty()) {
        std::cout << "No cards currently in stock. Check back later!" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < availableCards.size(); ++i) {
        auto card = availableCards[i];
        std::cout << i + 1 << ". " << card->getName() << " - $" << card->getPrice() 
                  << " - " << card->getEffect() << std::endl;
    }
}

bool StoreTile::purchaseCard(int cardIndex, std::shared_ptr<Player> player) {
    // Validate the card index
    if (cardIndex < 0 || cardIndex >= static_cast<int>(availableCards.size())) {
        std::cout << "Invalid card selection." << std::endl;
        return false;
    }
    
    auto selectedCard = availableCards[cardIndex];
    long long cardPrice = selectedCard->getPrice();
    
    // Check if the player has enough money
    if (player->getMoney() < cardPrice) {
        std::cout << "Not enough money to purchase this card." << std::endl;
        return false;
    }
    
    // Deduct money and give the card to the player
    if (player->deductMoney(cardPrice)) {
        player->addCard(selectedCard);
        std::cout << player->getDisplayName() << " purchased " << selectedCard->getName() 
                  << " for $" << cardPrice << "." << std::endl;
        
        // Remove the card from the store's inventory
        availableCards.erase(availableCards.begin() + cardIndex);
        
        // Check if we need to restock
        if (availableCards.empty()) {
            std::cout << "Store inventory is now empty. Restocking..." << std::endl;
            restockCards();
        }
        
        return true;
    }
    
    std::cout << "Transaction failed." << std::endl;
    return false;
}

void StoreTile::restockCards() {
    // Clear current inventory
    availableCards.clear();
    
    // Add random cards to inventory
    for (int i = 0; i < maxCardsInStock; ++i) {
        availableCards.push_back(createRandomCard());
    }
    
    std::cout << "The store has been restocked with new cards!" << std::endl;
}

std::shared_ptr<Card> StoreTile::createRandomCard() {
    // Random number generator
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr) + rand()));
    std::uniform_int_distribution<int> dist(0, 3); // 4 different card types
    
    int cardType = dist(rng);
    std::shared_ptr<Card> newCard;
    
    switch (cardType) {
        case 0:
            newCard = std::make_shared<FateCard>();
            break;
        case 1:
            newCard = std::make_shared<BarrierCard>();
            break;
        case 2:
            newCard = std::make_shared<DemolitionCard>();
            break;
        case 3:
            newCard = std::make_shared<RocketCard>(2); // Default to 2 turns
            break;
        default:
            newCard = nullptr; // Should not happen
            break;
    }
    
    return newCard;
}

void StoreTile::addCardToInventory(std::shared_ptr<Card> card) {
    if (availableCards.size() < static_cast<size_t>(maxCardsInStock)) {
        availableCards.push_back(card);
        std::cout << "Added " << card->getName() << " to store inventory." << std::endl;
    } else {
        std::cout << "Store inventory is full. Cannot add more cards." << std::endl;
    }
}

std::vector<std::shared_ptr<Card>> StoreTile::getAvailableCards() const {
    return availableCards;
}

int StoreTile::getMaxCardsInStock() const {
    return maxCardsInStock;
}

void StoreTile::setMaxCardsInStock(int max) {
    if (max > 0) {
        maxCardsInStock = max;
        std::cout << "Store capacity updated to " << max << " cards." << std::endl;
        
        // If current inventory exceeds new maximum, trim it down
        if (availableCards.size() > static_cast<size_t>(maxCardsInStock)) {
            availableCards.resize(maxCardsInStock);
        }
    }
}