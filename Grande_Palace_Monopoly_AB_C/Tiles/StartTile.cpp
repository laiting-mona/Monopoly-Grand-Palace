/**
 * @file StartTile.cpp
 * @brief StartTile ���O����@�ɮסC
 */

#include "StartTile.hpp"
#include "Game/Player.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;

StartTile::StartTile(size_t id, const std::string& name, int bonus)
    : Tile(id, name), passingBonus(bonus) {
}

TileAction StartTile::landOn(shared_ptr<Player> player) {
    // Player landed directly on Start, award bonus
    if (player) {
        player->addMoney(passingBonus);
        cout << player->getName() << " landed on Start tile and received $"
            << passingBonus << "!" << endl;
        delayMilliseconds(1200);
    }
    return TileAction::START_POINT;
}

void StartTile::passBy(shared_ptr<Player> player) {
    // Player passed by Start, also award bonus
    if (player) {
        player->addMoney(passingBonus);
        cout << player->getName() << " passed by Start tile and received $"
            << passingBonus << "!" << endl;
        delayMilliseconds(1200);
    }
}

int StartTile::getPassingBonus() const {
    return passingBonus;
}

void StartTile::setPassingBonus(int bonus) {
    passingBonus = bonus;
}