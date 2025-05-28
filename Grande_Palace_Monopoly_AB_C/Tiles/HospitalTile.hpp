/**
 * @file HospitalTile.hpp
 * @brief HospitalTile ���O�A�N����|��l�A���a�Q�e�����B�ݼȰ��C���^�X�C
 */
#ifndef HOSPITAL_TILE_HPP
#define HOSPITAL_TILE_HPP

#include "Tile.hpp"
#include <unordered_map>

 /**
  * @brief Tile representing a hospital where players may stay for multiple turns.
  */
class HospitalTile : public Tile {
private:
    std::unordered_map<std::size_t, int> patientRecoveryTurns; ///< Map of player ID to remaining turns in hospital (if tracked)
    int defaultRecoveryTime; ///< Default number of turns a player stays in hospital

public:
    /**
     * @brief Constructor for HospitalTile.
     * @param id The tile ID.
     * @param name Name of the hospital tile.
     * @param recoveryTime Default recovery turns for admitted players (default 2).
     */
    HospitalTile(const size_t id, const std::string& name, int recoveryTime = 2);

    /** @brief Destructor for HospitalTile. */
    virtual ~HospitalTile();

    /**
     * @brief Action when a player lands on the hospital tile.
     * @param player The player landing on the hospital.
     * @return TileAction::HOSPITAL if player stays in hospital, otherwise NONE.
     */
    TileAction landOn(std::shared_ptr<Player> player) override;

    /**
     * @brief Admit a player to the hospital for the default recovery time.
     * @param player The player to admit.
     */
    void admitPatient(std::shared_ptr<Player> player);

    /**
     * @brief Discharge a player from the hospital (allow them to leave).
     * @param player The player to discharge.
     */
    void dischargePatient(std::shared_ptr<Player> player);

    /**
     * @brief Check if a given player is currently admitted in this hospital.
     * @param player The player to check.
     * @return True if the player is in hospital.
     */
    bool isPatient(std::shared_ptr<Player> player) const;

    /**
     * @brief Get remaining recovery turns for a player in hospital.
     * @param player The player in hospital.
     * @return Number of turns left (0 if none or if not in hospital).
     */
    int getRemainingRecoveryTurns(std::shared_ptr<Player> player) const;

    /**
     * @brief Decrease the remaining hospital turns for a player by one.
     * @param player The player whose hospital stay is reduced.
     */
    void decrementRecoveryTurns(std::shared_ptr<Player> player);

    /**
     * @brief Set the default recovery time (in turns) for hospitalized players.
     * @param turns Number of turns to set as default.
     */
    void setDefaultRecoveryTime(int turns);

    /**
     * @brief Get the default recovery time for this hospital.
     * @return Number of turns players stay by default.
     */
    int getDefaultRecoveryTime() const;
};

#endif // HOSPITAL_TILE_HPP