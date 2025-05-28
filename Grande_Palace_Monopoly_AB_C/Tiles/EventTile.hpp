/**
 * @file EventTile.hpp
 * @brief EventTile 類別，玩家踩到時隨機觸發事件的格子。
 */
#ifndef EVENT_TILE_HPP
#define EVENT_TILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>
#include <string>
#include <random>

 /**
  * @brief Types of random events that an EventTile can trigger.
  */
enum class EventType {
    FATE,   ///< A fate-type event (predefined set of minor events)
    CHANCE  ///< A chance-type event (perhaps larger variance events)
};

/**
 * @brief Tile that triggers a random event (fate or chance) when a player lands on it.
 */
class EventTile : public Tile {
private:
    EventType eventType;
    int minValue;        ///< Minimum value outcome of the event
    int maxValue;        ///< Maximum value outcome of the event
    static std::mt19937 rng; ///< Random number generator for events

    std::vector<std::string> positiveEvents; ///< List of messages for positive outcomes
    std::vector<std::string> negativeEvents; ///< List of messages for negative outcomes

    /**
     * @brief Generate a random event value between minValue and maxValue, randomly negated.
     * @return A positive or negative integer representing event impact.
     */
    int generateEventValue() const;

    /**
     * @brief Select a random event message based on outcome positivity.
     * @param isPositive Whether the event outcome is positive (gain) or negative (loss).
     * @return A formatted message string with a placeholder for value.
     */
    std::string getRandomEventMessage(bool isPositive) const;

public:
    /**
     * @brief Constructor for EventTile.
     * @param id The tile ID.
     * @param name The name of the event tile.
     * @param type The type of events (FATE or CHANCE).
     * @param minVal The minimum event value (could be negative for losses).
     * @param maxVal The maximum event value.
     */
    EventTile(size_t id, const std::string& name, EventType type, int minVal, int maxVal);

    /** @brief Destructor (default). */
    ~EventTile() override = default;

    /**
     * @brief Trigger an event when a player lands on this tile.
     * @param player The player who landed on the event tile.
     * @return TileAction::SPECIAL_EVENT indicating a special event occurred.
     */
    TileAction landOn(std::shared_ptr<Player> player) override;

    /** @brief Get the type of event (FATE or CHANCE) this tile produces. */
    EventType getEventType() const;

    /** @brief Get the event type as a string (e.g., "Fate" or "Chance"). */
    std::string getEventTypeName() const;

    /**
     * @brief Set the range of possible values (min and max) for the random event outcomes.
     * @param minVal Minimum event value.
     * @param maxVal Maximum event value.
     */
    void setValueRange(int minVal, int maxVal);

    /**
     * @brief Add a custom positive event message.
     * @param message The message template (should include a %d for the value).
     */
    void addPositiveEvent(const std::string& message);

    /**
     * @brief Add a custom negative event message.
     * @param message The message template (should include a %d for the value).
     */
    void addNegativeEvent(const std::string& message);
};

#endif // EVENT_TILE_HPP