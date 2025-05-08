#include "DiceControlCard.hpp"
#include "Game/Player.hpp"

DiceControlCard::DiceControlCard(int value) 
    : Card("Dice Control", "....", 150, "Set your next dice roll to a specific value")
    , diceValue(value) {
    // Validate dice value is within proper range (typically 1-6)
    if (diceValue < 1) diceValue = 1;
    if (diceValue > 6) diceValue = 6;
}

void DiceControlCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    // Set the player's next dice roll to the specified value
    curPlayer->setDiceControl(diceValue);
    
    // Display a message indicating the card has been used
    std::string message = curPlayer->getName() + " used Dice Control card. Next roll will be " + std::to_string(diceValue) + "!";
    // Here you might want to call a display method or log the message
    
    // The card is consumed after use (handled by the game engine)
}

int DiceControlCard::getDiceValue() const {
    return diceValue;
}

void DiceControlCard::setDiceValue(int value) {
    // Validate input before setting
    if (value >= 1 && value <= 6) {
        diceValue = value;
    }
}