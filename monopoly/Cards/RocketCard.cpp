#include "RocketCard.hpp"
#include "Game/Player.hpp"

RocketCard::RocketCard(int turns) 
    : Card("Rocket", "!!!!", 250, "Send a player to the hospital")
    , hospitalTurns(turns)
    , targetPlayer(nullptr) {
    // Ensure hospital turns is at least 1
    if (hospitalTurns < 1) hospitalTurns = 1;
}

void RocketCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    // Check if a target player has been set
    if (!targetPlayer) {
        // No target player selected
        return;
    }
    
    // Check if the target player is the same as the current player
    if (targetPlayer == curPlayer) {
        // Cannot target yourself
        return;
    }
    
    // Send the target player to the hospital
    targetPlayer->sendToHospital(hospitalTurns);
    
    // Create a message about the effect
    std::string message = curPlayer->getName() + " used Rocket card on " + 
                          targetPlayer->getName() + ", sending them to the hospital for " + 
                          std::to_string(hospitalTurns) + " turns!";
    
    // Display or log the message
    // The card is consumed after use (handled by the game engine)
}

void RocketCard::setTargetPlayer(std::shared_ptr<Player> player) {
    targetPlayer = player;
}

std::shared_ptr<Player> RocketCard::getTargetPlayer() const {
    return targetPlayer;
}

void RocketCard::setHospitalTurns(int turns) {
    if (turns >= 1) {
        hospitalTurns = turns;
    }
}

int RocketCard::getHospitalTurns() const {
    return hospitalTurns;
}