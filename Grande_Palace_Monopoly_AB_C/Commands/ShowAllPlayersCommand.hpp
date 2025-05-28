#ifndef SHOW_ALL_PLAYERS_COMMAND_HPP
#define SHOW_ALL_PLAYERS_COMMAND_HPP

#include "Command.hpp"
#include "Game/Game.hpp"
#include <memory>

class ShowAllPlayersCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // SHOW_ALL_PLAYERS_COMMAND_HPP
