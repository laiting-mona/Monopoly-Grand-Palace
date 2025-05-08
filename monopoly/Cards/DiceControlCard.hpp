#ifndef DICE_CONTROL_CARD_HPP
#define DICE_CONTROL_CARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;

class DiceControlCard : public Card {
private:
    int diceValue; // The value to set the dice to

public:
    // Constructor
    DiceControlCard(int value = 6);
    
    // Use the card effect
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
    
    // Getter for dice value
    int getDiceValue() const;
    
    // Setter for dice value
    void setDiceValue(int value);
};

#endif // DICE_CONTROL_CARD_HPP