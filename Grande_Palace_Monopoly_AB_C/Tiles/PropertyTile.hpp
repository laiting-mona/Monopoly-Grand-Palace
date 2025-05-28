/**
 * @file PropertyTile.hpp
 * @brief PropertyTile 類別，代表可購買及升級的地產格子。
 */
#ifndef PROPERTY_TILE_HPP
#define PROPERTY_TILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>

 /**
  * @brief Levels of development for a property.
  */
enum class PropertyLevel {
    VACANT = 0,  ///< No owner or development
    LEVEL_1 = 1, ///< Level 1 development
    LEVEL_2 = 2, ///< Level 2 development
    LEVEL_3 = 3, ///< Level 3 development
    MAX_LEVEL = 4 ///< Maximum development level
};

/**
 * @brief Tile representing a property that players can own and upgrade.
 */
class PropertyTile : public Tile, public std::enable_shared_from_this<PropertyTile> {
private:
    int baseCost;                      ///< Initial purchase cost of the property
    int baseToll;                      ///< Base toll (rent) of the property at Level 1
    PropertyLevel level;              ///< Current development level of the property
    std::shared_ptr<Player> owner;    ///< Current owner of the property (nullptr if unowned)
    std::vector<int> upgradeCosts;    ///< Cost for each upgrade level
    std::vector<int> tollRates;       ///< Toll rates for each level

public:
    /**
     * @brief Constructor for PropertyTile.
     * @param id The tile ID.
     * @param name The name of the property.
     * @param cost The base purchase cost.
     * @param toll The base toll amount.
     */
    PropertyTile(size_t id, const std::string& name, int cost, int toll);

    /** @brief Destructor (default). */
    ~PropertyTile() override = default;

    /**
     * @brief Action when a player lands on this property tile.
     * @param player The player landing on the property.
     * @return TileAction indicating whether the player can purchase, must pay toll, etc.
     */
    TileAction landOn(std::shared_ptr<Player> player) override;

    /**
     * @brief Purchase this property (if it is unowned) by the given player.
     * @param player The player attempting to purchase.
     * @return True if purchase is successful, false if failed.
     */
    bool purchase(std::shared_ptr<Player> player);

    /**
     * @brief Upgrade the property by one level (if possible) by the owner.
     * @param player The player (owner) attempting to upgrade.
     * @return True if upgrade is successful.
     */
    bool upgrade(std::shared_ptr<Player> player);

    /**
     * @brief Sell this property (the owner gives it up for some money).
     * @param player The player (owner) selling the property.
     */
    void sell(std::shared_ptr<Player> player);

    /**
     * @brief Make a visiting player pay the toll to the owner.
     * @param player The player who landed on the property and must pay.
     */
    void payToll(std::shared_ptr<Player> player);

    /** @brief Get the current total price (initial cost + upgrades) of the property. */
    int getCurrentPrice() const;

    /** @brief Get the cost required to upgrade the property to the next level. */
    int getUpgradeCost() const;

    /** @brief Get the current owner of the property (nullptr if unowned). */
    std::shared_ptr<Player> getPropertyOwner() const;

    /**
     * @brief Set the owner of this property.
     * @param owner The player who will own the property (or nullptr if removing ownership).
     */
    void setPropertyOwner(std::shared_ptr<Player> owner);

    /** @brief Get the current development level of the property. */
    PropertyLevel getPropertyLevel() const;

    /** @brief Set the property's development level. */
    void setPropertyLevel(PropertyLevel newLevel) { level = newLevel; }

    /** @brief Get the current toll rate based on the property level. */
    int getCurrentToll() const;

    /** @brief Calculate the selling price of the property (e.g., half of total investment). */
    int getSellingPrice() const;

    /** @brief Check if the property can be upgraded further. */
    bool canUpgrade() const;

    /** @brief Check if this property is owned by a player. */
    bool isOwned() const;

    /**
     * @brief Get the property type name (for display purposes).
     * @return A string, e.g., "Property".
     */
    std::string getPropertyTypeName() const;

    /**
     * @brief Get the display name of the property with ID, owner, and level info.
     * @return A formatted string with property details.
     */
    std::string getNameWithId() const override;
};

#endif // PROPERTY_TILE_HPP