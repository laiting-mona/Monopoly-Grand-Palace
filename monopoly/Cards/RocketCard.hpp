#ifndef ROCKET_CARD_HPP
#define ROCKET_CARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;

class RocketCard : public Card {
private:
    int hospitalTurns; // Number of turns the target player will stay in hospital
    std::shared_ptr<Player> targetPlayer; // The player to send to the hospital

public:
    // Constructor
    RocketCard(int turns = 2);
    
    // Use the card effect
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
    
    // Set the target player
    void setTargetPlayer(std::shared_ptr<Player> player);
    
    // Get the target player
    std::shared_ptr<Player> getTargetPlayer() const;
    
    // Set the number of hospital turns
    void setHospitalTurns(int turns);
    
    // Get the number of hospital turns
    int getHospitalTurns() const;
};

#endif // ROCKET_CARD_HPP