#include "CardStore.hpp"
#include "Bank.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include "Cards/FateCard.hpp"
#include "Cards/RocketCard.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Initialize static instance pointer to nullptr
CardStore* CardStore::instance = nullptr;

// Private constructor that initializes the card store with cards from the game configuration
CardStore::CardStore(const GameConfig& config) {
    std::vector<CardConfig> cardConfigs = config.getCards();
    
    for (const auto& cardConfig : cardConfigs) {
        std::shared_ptr<Card> card;

        if (cardConfig.name == "Fate") {
            card = std::make_shared<FateCard>();
        } else if (cardConfig.name == "Barrier") {
            card = std::make_shared<BarrierCard>();
        } else if (cardConfig.name == "Demolition") {
            card = std::make_shared<DemolitionCard>();
        } else if (cardConfig.name == "Rocket") {
            card = std::make_shared<RocketCard>(2);  // 預設參數
        } else if (cardConfig.name == "DiceControl") {
            card = std::make_shared<DiceControlCard>();
        } else {
            std::cout << "Unknown card type: " << cardConfig.name << std::endl;
            continue; // skip unknown types
        }

        cards.push_back(card);
    }
    
    std::cout << "Card Store initialized with " << cards.size() << " cards" << std::endl;
}

// Static method to get or create the singleton instance with configuration
CardStore* CardStore::getInstance(const GameConfig& config) {
    if (instance == nullptr) {
        instance = new CardStore(config);
    }
    return instance;
}

// Static method to get the existing singleton instance
CardStore* CardStore::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("CardStore has not been initialized with a GameConfig");
    }
    return instance;
}

// Static method to destroy the singleton instance
void CardStore::destroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
        std::cout << "Card Store instance destroyed" << std::endl;
    }
}

// Display available cards in the store to the player
void CardStore::displayStore(std::shared_ptr<Player> player) {
    if (!player) {
        throw std::invalid_argument("Invalid player pointer");
    }
    
    std::cout << "\n===== Card Store =====" << std::endl;
    std::cout << "Player: " << player->getName() << " | Available Money: $" << player->getMoney() << std::endl;
    std::cout << "-----------------------" << std::endl;
    
    if (cards.empty()) {
        std::cout << "No cards available in the store." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << i + 1 << ". ";
        std::cout << cards[i]->getName() << " [" << cards[i]->getIcon() << "]" << std::endl;
        std::cout << "   Price: $" << cards[i]->getPrice() << std::endl;
        std::cout << "   Effect: " << cards[i]->getEffect() << std::endl;
        
        // Check if player can afford the card
        if (player->getMoney() >= cards[i]->getPrice()) {
            std::cout << "   [AVAILABLE]" << std::endl;
        } else {
            std::cout << "   [CANNOT AFFORD]" << std::endl;
        }
        std::cout << "-----------------------" << std::endl;
    }
}

// Allow a player to purchase a card from the store
void CardStore::purchaseCard(std::shared_ptr<Player> player, std::shared_ptr<Card> card) {
    if (!player) {
        throw std::invalid_argument("Invalid player pointer");
    }
    
    if (!card) {
        throw std::invalid_argument("Invalid card pointer");
    }
    
    // Check if the card exists in the store
    auto it = std::find(cards.begin(), cards.end(), card);
    if (it == cards.end()) {
        throw std::runtime_error("Card not found in the store");
    }
    
    // Check if player has enough money
    if (player->getMoney() < card->getPrice()) {
        throw std::runtime_error("Player doesn't have enough money to purchase this card");
    }
    
    // Process the purchase
    Bank* bank = Bank::getInstance();
    bank->receiveFromPlayer(player, card->getPrice());
    
    // Add the card to the player's inventory
    player->addCard(card);
    
    std::cout << player->getName() << " purchased " << card->getName() 
              << " for $" << card->getPrice() << std::endl;
              
    // Remove the card from the store if it's a one-time purchase
    // Uncomment this if cards should be removed after purchase
    // cards.erase(it);
}

// Get all cards available in the store
std::vector<std::shared_ptr<Card>> CardStore::getCards() const {
    return cards;
}

// Find a card by name
std::shared_ptr<Card> CardStore::getCardByName(const std::string& cardName) const {
    auto it = std::find_if(cards.begin(), cards.end(), 
                         [&cardName](const std::shared_ptr<Card>& card) {
                             return card->getName() == cardName;
                         });
    
    if (it != cards.end()) {
        return *it;
    }
    
    return nullptr; // Card not found
}