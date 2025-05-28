#include "MiniGameTile.hpp"
#include "Game/MiniGameManager.hpp"
#include "Game/Player.hpp"

TileAction MiniGameTile::landOn(std::shared_ptr<Player> player) {
    if (blocked) {
        return TileAction::NONE;
    }
    return TileAction::MINI_GAME;
}
