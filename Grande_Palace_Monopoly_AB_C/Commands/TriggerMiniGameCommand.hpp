#ifndef TRIGGER_MINI_GAME_COMMAND_HPP
#define TRIGGER_MINI_GAME_COMMAND_HPP

#include "Command.hpp"
#include "Game/Game.hpp"
#include <memory>

class TriggerMiniGameCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // TRIGGER_MINI_GAME_COMMAND_HPP
