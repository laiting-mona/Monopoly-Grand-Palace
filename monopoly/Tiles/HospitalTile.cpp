#include "HospitalTile.hpp"
#include "Game/Player.hpp"

HospitalTile::HospitalTile(const size_t id, const std::string& name, int recoveryTime)
    : Tile(id, name), defaultRecoveryTime(recoveryTime) {
}

HospitalTile::~HospitalTile() {
}

TileAction HospitalTile::landOn(std::shared_ptr<Player> player) {
    // When a player lands on hospital tile, we don't automatically admit them
    // They're only admitted if sent here by other  logic
    
    if (blocked) {
        return TileAction::NONE;
    }
    
    // Check if player is already a patient
    if (player->isInHospital()) {
        // Player is already in hospital, they need to continue recovery
        return TileAction::HOSPITAL;
    }
    
    // Player is just visiting the hospital, no special action
    return TileAction::NONE;
}

void HospitalTile::admitPatient(std::shared_ptr<Player> player) {
    // Admit the player to the hospital for the default recovery time
    player->sendToHospital(defaultRecoveryTime);
}

void HospitalTile::dischargePatient(std::shared_ptr<Player> player) {
    // Discharge the player from the hospital
    player->recoverFromHospital();
}

bool HospitalTile::isPatient(std::shared_ptr<Player> player) const {
    // Use the player's internal state to check if they're in the hospital
    return player->isInHospital();
}

int HospitalTile::getRemainingRecoveryTurns(std::shared_ptr<Player> player) const {
    // We can't directly access this from the Player class as implemented
    // This would require adding a getter in the Player class
    // For now, we'll return 0 if the player is not in hospital
    return player->isInHospital() ? 1 : 0; // Default to 1 if in hospital
}

void HospitalTile::decrementRecoveryTurns(std::shared_ptr<Player> player) {
    // Let the player handle its own hospital status update
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