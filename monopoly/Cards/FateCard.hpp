#ifndef FATECARD_HPP
#define FATECARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>
#include <string>
#include <utility>

class Player;

// Enumeration of possible fate events
enum class FateEvent {
    GAIN_MONEY,
    LOSE_MONEY,
    TELEPORT,
    MOVE_TO_START,
    GO_TO_HOSPITAL,
    DICE_CONTROL,
    GAIN_CARD
};

class FateCard : public Card {
private:
    // List of fate events and their descriptions
    std::vector<std::pair<FateEvent, std::string>> fateEvents;
    
    // Helper method to apply the selected fate event
    void applyFateEvent(FateEvent event, std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> player);

public:
    // Constructor
    FateCard();
    
    // Override the useEffect method from Card
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
    
    // Add a new fate event to the list
    void addFateEvent(FateEvent event, const std::string& description);
    
    // Get the list of fate events
    const std::vector<std::pair<FateEvent, std::string>>& getFateEvents() const;
};

#endif // FATECARD_HPP