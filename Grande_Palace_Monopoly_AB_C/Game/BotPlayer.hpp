#ifndef BOTPLAYER_HPP
#define BOTPLAYER_HPP

#include "Player.hpp"
#include <random>

class BotPlayer : public Player {
public:
    BotPlayer(const std::string& name, const std::string& icon, const std::string& color, long long money)
        : Player(name, icon, color, money) {}

    // Bot uses°ò base rollDice (no override) for dice roll

    void purchaseProperty(std::shared_ptr<PropertyTile> property);
    void upgradeProperty(std::shared_ptr<PropertyTile> property);
};

#endif