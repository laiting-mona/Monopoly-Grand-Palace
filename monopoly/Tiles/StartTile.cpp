#include "StartTile.hpp"
#include "Game/Player.hpp"
#include <iostream>

StartTile::StartTile(size_t id, const std::string& name, int bonus)
    : Tile(id, name)
    , passingBonus(bonus) {
}

TileAction StartTile::landOn(std::shared_ptr<Player> player) {
    // Player landed on start tile, give them the bonus
    if (player) {
        player->addMoney(passingBonus);
        std::cout << player->getName() << " landed on Start tile and received $" 
                  << passingBonus << "!" << std::endl;
    }
    
    return TileAction::START_POINT;
}

void StartTile::passBy(std::shared_ptr<Player> player) {
    // Player passed by start tile, also give them the bonus
    if (player) {
        player->addMoney(passingBonus);
        std::cout << player->getName() << " passed by Start tile and received $" 
                  << passingBonus << "!" << std::endl;
    }
}

int StartTile::getPassingBonus() const {
    return passingBonus;
}

void StartTile::setPassingBonus(int bonus) {
    passingBonus = bonus;
}