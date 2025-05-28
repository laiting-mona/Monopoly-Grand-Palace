#include "MoveToCommand.hpp"
#include "Game/Utils.hpp"
#include "Tiles/HospitalTile.hpp"
#include "Game/Board.hpp"
#include <iostream>

std::string MoveToCommand::getName() const {
    return "move_to";
}

std::string MoveToCommand::getDescription() const {
    return "Move to a specific position on the board";
}

void MoveToCommand::execute(std::shared_ptr<Player> player) {
    int pos;
    std::cout << "Enter target position (0~27): ";
    std::cin >> pos;

    // 移動
    player->setPosition(pos);
    std::cout << "Moved to space " << pos << std::endl;
    delayMilliseconds(800);

    Board* board = Game::getInstance()->getBoard();
    auto tile = board->getTile(pos);

    if (tile) {
        if (player->isInHospital()) {
            auto isHospital = std::dynamic_pointer_cast<HospitalTile>(tile);
            if (!isHospital) {
                std::cout << "(Override) Player forcibly moved out of hospital." << std::endl;
                delayMilliseconds(1200);
                player->recoverFromHospital();

                board->clearScreen();
                board->drawBoard();
            }
        }

        tile->landOn(player);
    }
    else {
        std::cout << "Invalid position: " << pos << std::endl;
        delayMilliseconds(1200);
    }
}
