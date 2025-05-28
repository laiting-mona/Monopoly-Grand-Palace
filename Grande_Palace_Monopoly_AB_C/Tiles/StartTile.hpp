/**
 * @file StartTile.hpp
 * @brief StartTile ���O�A�N���C���_�I��l�A���a�g�L�ΰ��d����o�����C
 */
#ifndef START_TILE_HPP
#define START_TILE_HPP

#include "Tile.hpp"
#include <memory>

 /**
  * @brief Tile representing the Start position of the board, giving a bonus when passed or landed on.
  */
class StartTile : public Tile {
private:
    int passingBonus; ///< Amount of money given when a player passes or lands on this tile

public:
    /**
     * @brief Constructor for StartTile.
     * @param id The tile ID.
     * @param name The name of the tile.
     * @param bonus The bonus amount awarded for passing/landing on this tile.
     */
    StartTile(size_t id, const std::string& name, int bonus);

    /** @brief Destructor (default). */
    ~StartTile() override = default;

    /**
     * @brief Player lands on the Start tile and receives the bonus.
     * @param player The player who landed on the start tile.
     * @return TileAction::START_POINT indicating the start was reached.
     */
    TileAction landOn(std::shared_ptr<Player> player) override;

    /**
     * @brief Called when a player passes by this start tile (without landing on it) to give the bonus.
     * @param player The player passing by Start.
     */
    void passBy(std::shared_ptr<Player> player);

    /** @brief Get the bonus amount for passing/landing on this tile. */
    int getPassingBonus() const;

    /** @brief Set the bonus amount for passing/landing on this tile. */
    void setPassingBonus(int bonus);
};

#endif // START_TILE_HPP