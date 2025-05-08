#ifndef DEMOLITIONCARD_HPP
#define DEMOLITIONCARD_HPP

#include "Card.hpp"
#include <memory>
#include <vector>

class Player;
class PropertyTile; // Forward declaration of PropertyTile instead of Property

class DemolitionCard : public Card {
private:
    std::shared_ptr<PropertyTile> targetProperty; // Changed from Property to PropertyTile

public:
    // Constructor
    DemolitionCard();
    
    // Override the useEffect method from Card
    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
    
    // Set the target property for demolition
    void setTargetProperty(std::shared_ptr<PropertyTile> property); // Changed from Property to PropertyTile
    
    // Get the target property
    std::shared_ptr<PropertyTile> getTargetProperty() const; // Changed from Property to PropertyTile
};

#endif // DEMOLITIONCARD_HPP