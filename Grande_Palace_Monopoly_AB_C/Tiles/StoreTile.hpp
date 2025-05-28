/**
 * @file StoreTile.hpp
 * @brief StoreTile 類別，代表卡片道具商店格子。
 */
#ifndef STORETILE_HPP
#define STORETILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>
#include <string>

class Card;
class Player;

/**
 * @brief Tile where players can purchase cards (Card Store).
 */
class StoreTile : public Tile {
private:
    std::vector<std::shared_ptr<Card>> availableCards; ///< Cards currently available for purchase
    int maxCardsInStock;                               ///< Maximum number of cards the store can hold

    /** @brief Restock the store with a new set of cards. */
    void restockCards();

    /** @brief Create a random card to stock the store. */
    std::shared_ptr<Card> createRandomCard();

public:
    /**
     * @brief Constructor for StoreTile.
     * @param position The tile ID or position on the board.
     * @param name Name of the store tile (default "Card Store").
     */
    StoreTile(int position, const std::string& name = "Card Store");

    /**
     * @brief Action when a player lands on the store tile.
     *        Offers the player the opportunity to buy a card.
     * @param player The player landing on the store.
     * @return TileAction::STORE to indicate store interaction.
     */
    TileAction landOn(std::shared_ptr<Player> player) override;

    /**
     * @brief Display all cards available in the store to the console.
     */
    void displayAvailableCards();

    /**
     * @brief Attempt to have a player purchase a card from the store.
     * @param cardIndex The index of the card in the current inventory list.
     * @param player The player who wants to purchase the card.
     * @return True if the purchase is successful, false otherwise.
     */
    bool purchaseCard(int cardIndex, std::shared_ptr<Player> player);

    /**
     * @brief Add a specific card to the store's inventory.
     * @param card The card to add to the store.
     */
    void addCardToInventory(std::shared_ptr<Card> card);

    /** @brief Get the list of cards currently available in the store. */
    std::vector<std::shared_ptr<Card>> getAvailableCards() const;

    /** @brief Get the maximum number of cards the store can stock. */
    int getMaxCardsInStock() const;

    /** @brief Set the maximum stock capacity of the store. */
    void setMaxCardsInStock(int max);
};

#endif // STORETILE_HPP