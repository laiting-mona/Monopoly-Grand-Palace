#ifndef STORETILE_HPP
#define STORETILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>
#include <string>

class Card;
class Player;

class StoreTile : public Tile {
private:
    std::vector<std::shared_ptr<Card>> availableCards; // Cards available for purchase
    int maxCardsInStock;                              // Maximum number of cards in stock
    
    // Internal helper functions
    void restockCards();                              // Restock the store with cards
    std::shared_ptr<Card> createRandomCard();         // Create a random card 

public:
    // Constructor
    StoreTile(int position, const std::string& name = "Card Store");
    
    // Override the landOn method from Tile
    TileAction landOn(std::shared_ptr<Player> player) override;
    
    // Store-specific methods
    void displayAvailableCards();                      // Display cards available for purchase
    bool purchaseCard(int cardIndex, std::shared_ptr<Player> player); // Player purchases a card
    void addCardToInventory(std::shared_ptr<Card> card); // Add a specific card to store inventory
    
    // Accessors
    std::vector<std::shared_ptr<Card>> getAvailableCards() const;
    int getMaxCardsInStock() const;
    
    // Mutators
    void setMaxCardsInStock(int max);
};

#endif // STORETILE_HPP