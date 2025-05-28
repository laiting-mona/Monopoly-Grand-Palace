/**
 * @file DiceControlCard.hpp
 * @brief DiceControlCard ���O�A�����a�i�H���w�U�@���Y���I�ƪ��d���C
 */
#ifndef DICE_CONTROL_CARD_HPP
#define DICE_CONTROL_CARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;

/**
 * @brief Card that allows a player to control the outcome of their next dice roll.
 */
class DiceControlCard : public Card {
private:
    int diceValue; ///< The fixed dice value that this card will enforce

public:
    /**
     * @brief Constructor for DiceControlCard.
     */
    DiceControlCard();

    /**
     * @brief Use the effect to fix the current player's next dice roll to a specific value.
     * @param players A list of all players (not used in this effect).
     * @param curPlayer The player who is using the card.
     */
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;

    /** @brief Get the predetermined dice value set by this card. */
    int getDiceValue() const;

    // /** @brief Set the predetermined dice value (must be 1-6). */
    // void setDiceValue(int value);
};

#endif // DICE_CONTROL_CARD_HPP