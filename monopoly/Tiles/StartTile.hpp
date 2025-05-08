#ifndef START_TILE_HPP
#define START_TILE_HPP

#include "Tile.hpp"
#include <memory>

class StartTile : public Tile {
private:
    int passingBonus; // Amount of money given when passing or landing on this tile

public:
    // Constructor
    StartTile(size_t id, const std::string& name, int bonus);
    
    // Destructor
    ~StartTile() override = default;
    
    // Player lands on this tile
    TileAction landOn(std::shared_ptr<Player> player) override;
    
    // Called when a player passes this tile (not lands on it)
    void passBy(std::shared_ptr<Player> player);
    
    // Get the bonus amount
    int getPassingBonus() const;
    
    // Set the bonus amount
    void setPassingBonus(int bonus);
};

#endif // START_TILE_HPP