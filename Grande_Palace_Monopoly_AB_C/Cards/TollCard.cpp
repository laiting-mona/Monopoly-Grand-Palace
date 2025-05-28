#include "TollCard.hpp"
#include "Game/Player.hpp"
#include "Game/Game.hpp"
#include "Game/Board.hpp"
#include "Tiles/Tile.hpp"
#include "Game/Utils.hpp"
#include <iostream>
#include <map>

TollCard::TollCard() : Card("Toll Card", "$", 300, "Set a tile as a toll booth for 3 turns(Charge $300)") {}

void TollCard::useEffect(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> curPlayer) {
    Board* board = Game::getInstance()->getBoard();
    int pos;
    std::cout << curPlayer->getDisplayName() << " Use TollCard, choose a tile (0~27): ";
    std::cin >> pos;

    auto tile = board->getTile(pos);
    if (!tile) {
        std::cout << "Invalid position, use failed.\n";
        waitForKey();
        return;
    }

    // Set the tile as a toll booth
    tile->setTollOwner(curPlayer);
    tile->setTollRounds(3); // Valid for 3 turns
    std::cout << "Tile " << pos << " is now a toll booth. Players passing through must pay $300 to " << curPlayer->getDisplayName() << " for 3 turns!\n";
    waitForKey();
}
