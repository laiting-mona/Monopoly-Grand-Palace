/**
 * @file RocketCard.hpp
 * @brief RocketCard 類別，將目標玩家送往醫院的卡片。
 */
#ifndef ROCKET_CARD_HPP
#define ROCKET_CARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;

/**
 * @brief Card that sends a target player to the hospital for a number of turns.
 */
class RocketCard : public Card {
private:
    int hospitalTurns;                  ///< Number of turns the target player stays in hospital
    std::shared_ptr<Player> targetPlayer; ///< The player to send to the hospital

public:
    /**
     * @brief Constructor for RocketCard.
     * @param turns The number of hospital turns (default 2).
     */
    RocketCard(int turns = 2);

    /**
     * @brief Use the rocket card effect to send the target player to the hospital.
     * @param players A list of all players (not used directly in this effect).
     * @param curPlayer The player who is using the card.
     */
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;

    /**
     * @brief Set the target player who will be sent to the hospital.
     * @param player The player to target.
     */
    void setTargetPlayer(std::shared_ptr<Player> player);

    /**
     * @brief Get the currently set target player.
     * @return Shared pointer to the target Player.
     */
    std::shared_ptr<Player> getTargetPlayer() const;

    /**
     * @brief Set how many turns the target player will stay in the hospital.
     * @param turns Number of turns.
     */
    void setHospitalTurns(int turns);

    /**
     * @brief Get the number of turns the target player will remain in the hospital.
     * @return Number of hospital turns.
     */
    int getHospitalTurns() const;
};

#endif // ROCKET_CARD_HPP