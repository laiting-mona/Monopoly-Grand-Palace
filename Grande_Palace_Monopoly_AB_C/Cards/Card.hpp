/**
 * @file Card.hpp
 * @brief 卡片抽象基類，定義遊戲中卡片的基本屬性與介面。
 */
#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <memory>

class Player; ///< Forward declaration of Player to avoid circular dependency

/**
 * @brief Base class representing a generic card in the game.
 */
class Card {
private:
    std::string name;   ///< Card name
    std::string icon;   ///< Icon or symbol representing the card
    int price;          ///< Purchase price of the card
    std::string effect; ///< Description of the card's effect

public:
    /**
     * @brief Construct a Card with the given attributes.
     * @param n Card name.
     * @param i Card icon identifier.
     * @param p Card price.
     * @param e Description of card effect.
     */
    Card(const std::string& n, const std::string& i, int p, const std::string& e);

    /**
     * @brief Virtual destructor for Card.
     */
    virtual ~Card();

    /** @brief Get the card's name. */
    std::string getName() const;

    /** @brief Get the card's icon identifier. */
    std::string getIcon() const;

    /** @brief Get the card's price. */
    int getPrice() const;

    /** @brief Get the description of the card's effect. */
    std::string getEffect() const;

    /**
     * @brief Apply the card's effect in the game.
     *
     * This is a pure virtual function to be implemented by each specific card type.
     * @param players List of all players in the game (for context if needed).
     * @param curPlayer The player who is using the card.
     */
    virtual void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) = 0;
};

#endif // CARD_HPP