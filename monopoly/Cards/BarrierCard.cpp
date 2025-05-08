#include "BarrierCard.hpp"
#include "Game/Player.hpp"
#include "Tiles/Tile.hpp" // Include Tile class
#include <iostream>

BarrierCard::BarrierCard() 
    : Card("Barrier", "====", 100, "Place a barrier to block the next player who passes by")
    , tilePosition(-1)
    , targetTile(nullptr) {
}

void BarrierCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    // Check if a target tile has been set
    if (!targetTile && tilePosition < 0) {
        std::cout << "No target tile selected for the barrier!" << std::endl;
        return;
    }
    
    // If we have a position but no tile, we need to find the tile
    if (!targetTile && tilePosition >= 0) {
        // In a real implementation, you would get the tile from the game board
        // using the position. Here we'll just return as we don't have access to the board.
        std::cout << "Unable to locate the tile at position " << tilePosition << std::endl;
        return;
    }
    
    // Place the barrier on the target tile
    if (targetTile) {
        targetTile->setBlock(true);
        
        // Create a message about the effect
        std::string message = curPlayer->getDisplayName() + " placed a Barrier on tile " + 
                              targetTile->getName() + "!";
        
        // Display the message
        std::cout << message << std::endl;
    }
    
    // The card is consumed after use (handled by the game engine)
}

void BarrierCard::setTargetTile(std::shared_ptr<Tile> tile) {
    targetTile = tile;
    if (tile) {
        // Update position based on the tile if it's provided
        tilePosition = static_cast<int>(tile->getId());
    }
}

std::shared_ptr<Tile> BarrierCard::getTargetTile() const {
    return targetTile;
}

void BarrierCard::setTilePosition(int position) {
    tilePosition = position;
    // Note: In a real implementation, you would update the targetTile
    // based on the position by fetching it from the game board
}

int BarrierCard::getTilePosition() const {
    return tilePosition;
}