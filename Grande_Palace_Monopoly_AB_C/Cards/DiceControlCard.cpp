/**
 * @file DiceControlCard.cpp
 * @brief DiceControlCard ���O����@�ɮסC
 */

#include "DiceControlCard.hpp"
#include "Game/Player.hpp"
#include <iostream>
#include <string>

using namespace std;

// DiceControlCard::DiceControlCard(int value)
//     : Card("Dice Control", "....", 150, "Set your next dice roll to a specific value")
//     , diceValue(value) {
//     // Ensure the dice value is within the valid range 1-6
//     if (diceValue < 1) diceValue = 1;
//     if (diceValue > 6) diceValue = 6;
// }

DiceControlCard::DiceControlCard()
    : Card("Dice Control", "....", 150, "Set your next dice roll to a specific value") {}


// void DiceControlCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
//     // Set the player's next dice roll to the specified value
//     curPlayer->setDiceControl(diceValue);
//     // Display a message indicating the effect of the card
//     string message = curPlayer->getName() + " used Dice Control card. Next roll will be " + to_string(diceValue) + "!";
//     cout << message << endl;
//     // The card is consumed after use (handled by the game engine)
// }

void DiceControlCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
    int value = 0;
    while (true) {
        std::cout << "Please enter the desired dice value (1~12): "; 
        std::cin >> value;
        if (value >= 1 && value <= 12) break; // The only chance to roll 1
        std::cout << "Invalid input, please enter a number between 1 and 12." << std::endl;
    }

    curPlayer->setDiceControl(value);
    diceValue = value; 
    std::cout << curPlayer->getName() << " used the Dice Control card, the next roll will be " << value << "!" << std::endl;
}

int DiceControlCard::getDiceValue() const {
    return diceValue;
}

// void DiceControlCard::setDiceValue(int value) {
//     if (value >= 1 && value <= 12) {
//         diceValue = value;
//     }
// }