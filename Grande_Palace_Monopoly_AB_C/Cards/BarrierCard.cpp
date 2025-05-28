/**
 * @file BarrierCard.cpp
 * @brief BarrierCard ���O����@�ɮסC
 */

#include "BarrierCard.hpp"
#include "Game/Player.hpp"
#include "Game/Board.hpp"
#include "Tiles/Tile.hpp"
#include <iostream>

using namespace std;

BarrierCard::BarrierCard()
    : Card("Barrier", "====", 100, "Place a barrier to block the next player who passes by")
    , tilePosition(-1)
    , targetTile(nullptr) {
}

BarrierCard::~BarrierCard() {
}

void BarrierCard::useEffect(vector<shared_ptr<Player>>& players, shared_ptr<Player> curPlayer) {
    Board* board = Board::getInstance();
    if (!board) return;

    // Check if the current player has already set a target tile
    if (targetTile && tilePosition >= 0) {
        cout << curPlayer->getDisplayName() << " has set a barrier on " << targetTile->getName() << "." << endl;
        return;
    }
    if (!targetTile && tilePosition < 0) {
        std::cout << "Choose a tile to place the barrier:" << std::endl;
        auto tileList = board->getTileList();
        for (size_t i = 0; i < tileList.size(); ++i) {
            std::cout << "[" << i << "] " << tileList[i]->getName() << std::endl;
        }

        int choice = -1;
        std::cin >> choice;
        if (choice < 0 || choice >= static_cast<int>(tileList.size())) {
            std::cout << "Invalid choice." << std::endl;
            return;
        }

        targetTile = tileList[choice];
        tilePosition = choice;
    }

    if (targetTile) {
        targetTile->setBlock(true);
        std::cout << curPlayer->getDisplayName() << " has placed a barrier on " << targetTile->getName() << "." << std::endl;
    }
}

void BarrierCard::setTargetTile(shared_ptr<Tile> tile) {
    targetTile = tile;
    if (tile) {
        // Update the position index based on the provided tile
        tilePosition = static_cast<int>(tile->getId());
    }
}

shared_ptr<Tile> BarrierCard::getTargetTile() const {
    return targetTile;
}

void BarrierCard::setTilePosition(int position) {
    tilePosition = position;
    // Note: In a real implementation, you would update targetTile using the Board.
}

int BarrierCard::getTilePosition() const {
    return tilePosition;
}