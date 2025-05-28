/**
 * @file RocketCard.cpp
 * @brief RocketCard ���O����@�ɮסC
 */

#include "RocketCard.hpp"
#include "Game/Player.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;

RocketCard::RocketCard(int turns)
    : Card("Rocket", ">>>>", 250, "Send a player to hospital for a few turns")
    , hospitalTurns(turns)
    , targetPlayer(nullptr) {
}

void RocketCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
    if (!targetPlayer) {
        // Ask current player to select a target
        cout << "Choose a player to target with the Rocket:" << endl;
        for (size_t i = 0; i < players.size(); ++i) {
            if (players[i] != curPlayer) {
                cout << i << ": " << players[i]->getDisplayName() << endl;
            }
        }
        int choice = -1;
        cin >> choice;
        if (choice < 0 || choice >= static_cast<int>(players.size()) || players[choice] == curPlayer) {
            cout << "Invalid choice. Cancelling card use." << endl;
            delayMilliseconds(1200);
            targetPlayer = nullptr; // Reset target
            return;
        }
        targetPlayer = players[choice];
    }

    targetPlayer->sendToHospital(hospitalTurns);
    cout << curPlayer->getDisplayName() << " used Rocket card on "
         << targetPlayer->getDisplayName() << ", sending them to hospital for "
         << hospitalTurns << " turns!" << endl;
    delayMilliseconds(1200);
}

void RocketCard::setTargetPlayer(shared_ptr<Player> player) {
    targetPlayer = player;
}

shared_ptr<Player> RocketCard::getTargetPlayer() const {
    return targetPlayer;
}

void RocketCard::setHospitalTurns(int turns) {
    hospitalTurns = turns;
}

int RocketCard::getHospitalTurns() const {
    return hospitalTurns;
}