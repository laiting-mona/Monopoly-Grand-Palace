/**
 * @file FateCard.hpp
 * @brief FateCard 類別，隨機觸發命運事件的卡片。
 * @date 2025/05/17
 */

#ifndef FATECARD_HPP
#define FATECARD_HPP

#include "Card.hpp"
#include <vector>
#include <string>
#include <memory>

 /**
  * @brief Enumeration of possible Fate events.
  */
enum class FateEvent {
    GAIN_MONEY,
    LOSE_MONEY,
    TELEPORT,
    MOVE_TO_START,
    GO_TO_HOSPITAL,
    DICE_CONTROL,
    GAIN_CARD
};

/**
 * @brief FateCard class that triggers random fate events when used.
 */
class FateCard : public Card {
private:
    std::vector<std::pair<FateEvent, std::string>> fateEvents;

    /**
     * @brief Apply a specific fate event effect.
     * @param event The FateEvent to apply.
     * @param players List of all players.
     * @param player The player triggering the event.
     */
    void applyFateEvent(FateEvent event, std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> player);

public:
    /**
     * @brief Constructor.
     */
    FateCard();

    /**
     * @brief Use the fate card effect.
     * @param players List of all players.
     * @param curPlayer The player using the card.
     */
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;

    /**
     * @brief Add a new fate event option.
     * @param event The event enum.
     * @param description The event description.
     */
    void addFateEvent(FateEvent event, const std::string& description);

    /**
     * @brief Get all fate events with their descriptions.
     * @return Vector of pairs of FateEvent and description string.
     */
    const std::vector<std::pair<FateEvent, std::string>>& getFateEvents() const;
};

#endif // FATECARD_HPP