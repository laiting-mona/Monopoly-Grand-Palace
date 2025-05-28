/**
 * @file HospitalTile.cpp
 * @brief HospitalTile ���O����@�ɮסC
 */

#include "HospitalTile.hpp"
#include "Game/Player.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;

HospitalTile::HospitalTile(const size_t id, const std::string& name, int recoveryTime)
    : Tile(id, name), defaultRecoveryTime(recoveryTime) {
}

HospitalTile::~HospitalTile() {
}

// TileAction HospitalTile::landOn(shared_ptr<Player> player) {
//     if (blocked) {
//         return TileAction::NONE;
//     }

//     if (player->isInHospital()) {
//         cout << player->getDisplayName() << " is currently hospitalized." << endl;
//         delayMilliseconds(1200);

//         // roll the dice to see if they can recover
//         int roll = player->rollDice();
//         cout << "You rolled a " << roll << "." << endl;

//         if (roll >= 10) {
//             cout << "Roll successful, you can leave early!" << endl;
//             delayMilliseconds(1200);
//             player->recoverFromHospital();
//         }
//         else {
//             cout << "Roll failed, you cannot leave yet." << endl;
//             cout << "Would you like to pay $3000 to leave early? (y/n): ";
//             char choice;
//             std::cin >> choice;
//             if (choice == 'y' || choice == 'Y') {
//                 if (player->deductMoney(3000)) {
//                     cout << "You paid $3000 and successfully left the hospital early." << endl;
//                     delayMilliseconds(1200);
//                     player->recoverFromHospital();
//                 }
//                 else {
//                     cout << "Insufficient funds to leave early." << endl;
//                     delayMilliseconds(1200);
//                 }
//             }
//         }

//         delayMilliseconds(1200);
//         return TileAction::HOSPITAL;
//     }

//     // If the player is not in hospital, admit them
//     admitPatient(player);
//     cout << player->getDisplayName() << " has been admitted to the hospital for "
//          << defaultRecoveryTime << " turns." << endl;
//     delayMilliseconds(1200);
//     return TileAction::HOSPITAL;
// }

// TileAction HospitalTile::landOn(shared_ptr<Player> player) {
//     if (blocked) {
//         return TileAction::NONE;
//     }

//     if (player->isInHospital()) {
//         cout << player->getDisplayName() << " is currently hospitalized." << endl;
//         delayMilliseconds(1200);

//         int roll = player->rollDice();
//         cout << "You rolled a " << roll << "." << endl;

//         if (roll >= 10) {
//             cout << "Roll successful, you can leave early!" << endl;
//             player->recoverFromHospital();
//         } else {
//             cout << "Roll failed. Would you like to pay $3000 to leave early? (y/n): ";
//             char choice;
//             std::cin >> choice;
//             if (choice == 'y' || choice == 'Y') {
//                 if (player->deductMoney(3000)) {
//                     cout << "Payment successful. You left the hospital." << endl;
//                     player->recoverFromHospital();
//                 } else {
//                     cout << "Insufficient funds." << endl;
//                 }
//             }
//         }

//         delayMilliseconds(1200);
//         return TileAction::HOSPITAL;
//     }

//     admitPatient(player); 
//     return TileAction::HOSPITAL;
// }

TileAction HospitalTile::landOn(shared_ptr<Player> player) {
    if (blocked) {
        return TileAction::NONE;
    }

    if (!player->isInHospital()) {
        admitPatient(player); // only admit if not already hospitalized
    }

    return TileAction::HOSPITAL;
}


void HospitalTile::admitPatient(shared_ptr<Player> player) {
    player->sendToHospital(defaultRecoveryTime);
    // cout << player->getDisplayName() << " has been admitted to the hospital for "
    //      << defaultRecoveryTime << " turns." << endl;
    // delayMilliseconds(1200);
}

void HospitalTile::dischargePatient(shared_ptr<Player> player) {
    // Remove the player from the hospital (they can resume playing)
    player->recoverFromHospital();
}

bool HospitalTile::isPatient(shared_ptr<Player> player) const {
    // Determine if the player is in hospital based on their state
    return player->isInHospital();
}

int HospitalTile::getRemainingRecoveryTurns(shared_ptr<Player> player) const {
    // We rely on Player's state (if accessible) for this information
    return player->getHospitalRoundLeft();
}

void HospitalTile::decrementRecoveryTurns(shared_ptr<Player> player) {
    if (player->isInHospital()) {
        player->updateHospitalStatus();
    }
}

void HospitalTile::setDefaultRecoveryTime(int turns) {
    defaultRecoveryTime = turns;
}

int HospitalTile::getDefaultRecoveryTime() const {
    return defaultRecoveryTime;
}