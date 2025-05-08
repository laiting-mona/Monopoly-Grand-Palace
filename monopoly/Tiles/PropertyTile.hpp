#ifndef PROPERTY_TILE_HPP
#define PROPERTY_TILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>

// Define property levels
enum class PropertyLevel {
    VACANT = 0,  // Not owned
    LEVEL_1 = 1, // Basic level
    LEVEL_2 = 2,
    LEVEL_3 = 3,
    MAX_LEVEL = 4 // Maximum upgrade level
};

class PropertyTile : public Tile, public std::enable_shared_from_this<PropertyTile> {
private:
    int baseCost;                    // Initial purchase cost
    int baseToll;                    // Initial toll amount
    PropertyLevel level;             // Current level of the property
    std::shared_ptr<Player> owner;   // Property owner
    std::vector<int> upgradeCosts;   // Cost for each level upgrade
    std::vector<int> tollRates;      // Toll rates for each level

public:
    // Constructor
    PropertyTile(size_t id, const std::string& name, int cost, int toll);
    
    // Destructor
    ~PropertyTile() override = default;
    
    // Player lands on this tile
    TileAction landOn(std::shared_ptr<Player> player) override;
    
    // Operations for purchasing, upgrading, paying toll, selling, etc.
    bool purchase(std::shared_ptr<Player> player);
    bool upgrade(std::shared_ptr<Player> player);
    void sell(std::shared_ptr<Player> player);
    void payToll(std::shared_ptr<Player> player);
    
    // Get current price (may change after upgrades)
    int getCurrentPrice() const;
    
    // Get the cost required to upgrade
    int getUpgradeCost() const;
    
    // Get and set the property owner
    std::shared_ptr<Player> getPropertyOwner() const;
    void setPropertyOwner(std::shared_ptr<Player> owner);
    
    // Get the current property level
    PropertyLevel getPropertyLevel() const;
    
    // Set property level
    void setPropertyLevel(PropertyLevel newLevel);
    
    // Get current toll rate
    int getCurrentToll() const;
    
    // Calculate selling price (usually a percentage of total investment)
    int getSellingPrice() const;
    
    // Check if the property can be upgraded further
    bool canUpgrade() const;
    
    // Check if this property is owned
    bool isOwned() const;
    
    // Get the property type name for display
    std::string getPropertyTypeName() const;
    
    // Override getNameWithId to include ownership and level information
    std::string getNameWithId() const override;
};

#endif // PROPERTY_TILE_HPP