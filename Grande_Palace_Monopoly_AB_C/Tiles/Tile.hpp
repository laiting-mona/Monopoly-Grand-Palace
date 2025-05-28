/**
 * @file Tile.hpp
 * @brief Tile ��H�����O�A�w�q�C���a�ϤW����l�����C
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "Game/Player.hpp"
#include <memory>
#include <string>

 /**
  * @brief Enumeration of possible actions when a player lands on a tile.
  */
enum class TileAction {
    NONE,               ///< No special action
    PURCHASE_PROPERTY,  ///< Player can purchase an unowned property
    OWN,                ///< Player's own property (option to upgrade)
    PAY_TOLL,           ///< Player must pay toll/rent
    STORE,              ///< Player landed on a store tile
    SPECIAL_EVENT,      ///< A special event is triggered
    TRADE,              ///< A trade opportunity (if applicable)
    HOSPITAL,           ///< Player is in hospital (skip turns)
    MINI_GAME,         ///< Player triggered a mini-game
    START_POINT         ///< Player reached or passed the Start tile
};

/**
 * @brief Abstract base class representing a board tile.
 */
class Tile {
protected:
    std::size_t id;   ///< Unique identifier for the tile
    std::string name; ///< Name of the tile
    bool blocked;     ///< Whether the tile is currently blocked by a barrier
    std::shared_ptr<Player> tollOwner = nullptr; ///< Owner of the tile for toll payments (if applicable)
    int tollRounds = 0; 

public:
    /**
     * @brief Constructor for a Tile.
     * @param id The ID of the tile.
     * @param n The name of the tile.
     */
    Tile(const size_t id, const std::string& n)
        : id(id), name(n), blocked(false) {}

    /** @brief Virtual destructor for Tile. */
    virtual ~Tile() {}

    /** @brief Get the name of the tile. */
    std::string getName() const { return name; }

    /**
     * @brief Get the display name of the tile with its ID.
     * @return A string combining the tile's ID and name.
     */
    virtual std::string getNameWithId() const {
        return std::to_string(id) + " " + name;
    }

    /** @brief Get the unique ID of the tile. */
    size_t getId() const { return id; }

    /** @brief Set or remove a barrier on this tile. */
    void setBlock(bool b) { blocked = b; }

    /** @brief Check if this tile is currently blocked by a barrier. */
    bool isBlocked() const { return blocked; }

    /**
     * @brief Action performed when a player lands on this tile.
     * @param player The player who landed on the tile.
     * @return The TileAction indicating what happens (purchase, pay toll, etc.).
     */
    virtual TileAction landOn(std::shared_ptr<Player> player) = 0;

    void setTollOwner(std::shared_ptr<Player> owner) { tollOwner = owner; }
    void setTollRounds(int rounds) { tollRounds = rounds; }
    std::shared_ptr<Player> getTollOwner() const { return tollOwner; }
    int getTollRounds() const { return tollRounds; }
    void updateTollStatus() {
        if (tollRounds > 0) {
            tollRounds--;
            if (tollRounds == 0) {
                tollOwner = nullptr;
            }
        }
    }
};

#endif // TILE_HPP