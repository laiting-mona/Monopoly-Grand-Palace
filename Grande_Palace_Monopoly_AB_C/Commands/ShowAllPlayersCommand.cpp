#include "ShowAllPlayersCommand.hpp"

std::string ShowAllPlayersCommand::getName() const {
    return "show_players";
}

std::string ShowAllPlayersCommand::getDescription() const {
    return "Display the status of all players";
}

void ShowAllPlayersCommand::execute(std::shared_ptr<Player> player) {
    for (const auto& p : Game::getInstance()->getPlayers()) {
        p->displayInfo();
    }
}
