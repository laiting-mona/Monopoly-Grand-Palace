#ifndef MINI_GAME_TILE_HPP
#define MINI_GAME_TILE_HPP

#include "Tile.hpp"
#include <memory>

class MiniGameManager;

/**
 * @brief A tile that triggers a mini-game when landed on.
 */
class MiniGameTile : public Tile {
private:
    std::shared_ptr<MiniGameManager> miniGameManager;

public:
    MiniGameTile(std::size_t id, const std::string& name, std::shared_ptr<MiniGameManager> manager)
        : Tile(id, name), miniGameManager(manager) {}

    virtual TileAction landOn(std::shared_ptr<Player> player) override;
};

#endif // MINI_GAME_TILE_HPP
