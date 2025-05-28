/**
 * @file DemolitionCard.hpp
 * @brief DemolitionCard 類別，降低目標地產等級的卡片。
 */
#ifndef DEMOLITIONCARD_HPP
#define DEMOLITIONCARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;
class PropertyTile;

/**
 * @brief Card that demolishes a property, reducing its level by one.
 */
class DemolitionCard : public Card {
private:
    std::shared_ptr<PropertyTile> targetProperty; ///< The property to be demolished

public:
    /** @brief Constructor for DemolitionCard. */
    DemolitionCard();

    /**
     * @brief Use the demolition effect on the target property (level -1).
     * @param players A list of all players (not directly used by this effect).
     * @param curPlayer The player who is using the card.
     */
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;

    /**
     * @brief Set the target property for demolition.
     * @param property The PropertyTile to be demolished.
     */
    void setTargetProperty(std::shared_ptr<PropertyTile> property);

    /**
     * @brief Get the target property set for demolition.
     * @return Shared pointer to the target PropertyTile.
     */
    std::shared_ptr<PropertyTile> getTargetProperty() const;
};

#endif // DEMOLITIONCARD_HPP