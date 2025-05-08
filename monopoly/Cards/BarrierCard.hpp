#ifndef BARRIERCARD_HPP
#define BARRIERCARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;
class Tile;

class BarrierCard : public Card {
private:
    int tilePosition;                // Position of the tile to block
    std::shared_ptr<Tile> targetTile; // Tile to place the barrier on

public:
    // Constructor
    BarrierCard();
    
    // Override the useEffect method from Card
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
    
    // Set the target tile for the barrier
    void setTargetTile(std::shared_ptr<Tile> tile);
    
    // Get the target tile
    std::shared_ptr<Tile> getTargetTile() const;
    
    // Set the position of the tile to block
    void setTilePosition(int position);
    
    // Get the position of the tile to block
    int getTilePosition() const;
};

#endif // BARRIERCARD_HPP