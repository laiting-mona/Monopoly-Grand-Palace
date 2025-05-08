#ifndef EVENT_TILE_HPP
#define EVENT_TILE_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>
#include <string>
#include <random>

// Define event types
enum class EventType {
    FATE,
    CHANCE
};

class EventTile : public Tile {
private:
    EventType eventType;
    int minValue;        // Minimum event value
    int maxValue;        // Maximum event value
    
    // Random number generator
    static std::mt19937 rng;
    
    // Vector of positive event messages
    std::vector<std::string> positiveEvents;
    
    // Vector of negative event messages
    std::vector<std::string> negativeEvents;
    
    // Generate a random event value
    int generateEventValue() const;
    
    // Get a random event message based on whether the value is positive or negative
    std::string getRandomEventMessage(bool isPositive) const;

public:
    // Constructor
    EventTile(size_t id, const std::string& name, EventType type, int minVal, int maxVal);
    
    // Destructor
    ~EventTile() override = default;
    
    // Player lands on this tile
    TileAction landOn(std::shared_ptr<Player> player) override;
    
    // Get the event type
    EventType getEventType() const;
    
    // Get the event type name as a string
    std::string getEventTypeName() const;
    
    // Set value range
    void setValueRange(int minVal, int maxVal);
    
    // Add custom event messages
    void addPositiveEvent(const std::string& message);
    void addNegativeEvent(const std::string& message);
};

#endif // EVENT_TILE_HPP