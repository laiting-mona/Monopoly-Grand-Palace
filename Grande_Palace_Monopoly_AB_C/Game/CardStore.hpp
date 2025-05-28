/**
 * @file CardStore.hpp
 * @brief CardStore 類別，遊戲中的卡片商店單例。
 */
#ifndef CARDSTORE_HPP
#define CARDSTORE_HPP

#include "Cards/Card.hpp"
#include "Game/GameConfig.hpp"
#include "Game/Player.hpp"
#include <memory>
#include <vector>

 /**
  * @brief Singleton that manages the store of cards available for purchase in the game.
  */
class CardStore {
private:
    static CardStore* instance;
    std::vector<std::shared_ptr<Card>> cards; ///< Inventory of cards available in the store

    /** @brief Private constructor that initializes the store with cards from config. */
    CardStore(const GameConfig& config);
    /** @brief Private destructor. */
    ~CardStore() = default;

public:
    /**
     * @brief Get the CardStore singleton instance, creating it with game config if not already created.
     * @param config The game configuration used to initialize the card list.
     * @return Pointer to the CardStore singleton.
     */
    static CardStore* getInstance(const GameConfig& config);

    /**
     * @brief Get the CardStore singleton instance (must have been initialized).
     * @return Pointer to the existing CardStore singleton.
     * @throws std::runtime_error if not yet initialized with config.
     */
    static CardStore* getInstance();

    /**
     * @brief Destroy the CardStore singleton instance.
     */
    static void destroyInstance();

    // Delete copy constructor and assignment
    CardStore(const CardStore&) = delete;
    CardStore& operator=(const CardStore&) = delete;

    /**
     * @brief Display the store inventory to a given player (usually prints to console).
     * @param player The player viewing the store.
     */
    void displayStore(std::shared_ptr<Player> player);

    /**
     * @brief Handle the purchase of a card by a player.
     * @param player The player who wants to buy a card.
     * @param card The card the player wants to purchase.
     */
    void purchaseCard(std::shared_ptr<Player> player, std::shared_ptr<Card> card);

    /** @brief Get all cards currently available in the store. */
    std::vector<std::shared_ptr<Card>> getCards() const;

    /**
     * @brief Find a card in the store by its name.
     * @param cardName Name of the card to find.
     * @return Shared pointer to the card if found, otherwise nullptr.
     */
    std::shared_ptr<Card> getCardByName(const std::string& cardName) const;
};

#endif // CARDSTORE_HPP