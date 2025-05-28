#ifndef TOLLCARD_HPP
#define TOLLCARD_HPP

#include "Card.hpp"
#include <unordered_map>
#include <memory>

class TollCard : public Card {
public:
    TollCard();

    void useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) override;
};

#endif // TOLLCARD_HPP
