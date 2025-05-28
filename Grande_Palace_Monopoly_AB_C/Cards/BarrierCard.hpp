/**
 * @file BarrierCard.hpp
 * @brief BarrierCard 類別，在地圖格子上設置路障以阻擋玩家通行的卡片。
 */
#ifndef BARRIERCARD_HPP
#define BARRIERCARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;
class Tile;

/**
 * @brief Card that places a barrier on a board tile to block other players.
 */
class BarrierCard : public Card {
private:
    int tilePosition;                 ///< Position index of the tile to block
    std::shared_ptr<Tile> targetTile; ///< The tile on which the barrier will be placed

public:
    /** @brief Constructor for BarrierCard. */
    BarrierCard();

    /** @brief Destructor for BarrierCard. */
    virtual ~BarrierCard();

    /**
     * @brief Use the barrier effect to block a target tile.
     * @param players A list of all players (not used directly in this effect).
     * @param curPlayer The player who is using the card.
     */
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;

    /**
     * @brief Set the target tile for the barrier.
     * @param tile The tile where the barrier will be placed.
     */
    void setTargetTile(std::shared_ptr<Tile> tile);

    /**
     * @brief Get the currently set target tile for the barrier.
     * @return Shared pointer to the target Tile.
     */
    std::shared_ptr<Tile> getTargetTile() const;

    /** @brief Set the position index of the tile to block. */
    void setTilePosition(int position);

    /** @brief Get the position index of the tile to block. */
    int getTilePosition() const;
};

#endif // BARRIERCARD_HPP