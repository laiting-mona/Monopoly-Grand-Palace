#ifndef HOSPITAL_TILE_HPP
#define HOSPITAL_TILE_HPP

#include "Tile.hpp"
#include <unordered_map>

class HospitalTile : public Tile {
private:
    std::unordered_map<std::size_t, int> patientRecoveryTurns; // Maps player ID to remaining recovery turns
    int defaultRecoveryTime;  // Number of turns a player must wait before leaving

public:
    HospitalTile(const size_t id, const std::string& name, int recoveryTime = 3);
    virtual ~HospitalTile();

    // Override the landOn method from the base class
    TileAction landOn(std::shared_ptr<Player> player) override;

    // Hospital specific methods
    void admitPatient(std::shared_ptr<Player> player);
    void dischargePatient(std::shared_ptr<Player> player);
    bool isPatient(std::shared_ptr<Player> player) const;
    int getRemainingRecoveryTurns(std::shared_ptr<Player> player) const;
    void decrementRecoveryTurns(std::shared_ptr<Player> player);
    void setDefaultRecoveryTime(int turns);
    int getDefaultRecoveryTime() const;
};

#endif // HOSPITAL_TILE_HPP