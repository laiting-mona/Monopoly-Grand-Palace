#ifndef MOVE_TO_COMMAND_HPP
#define MOVE_TO_COMMAND_HPP

#include "Command.hpp"
#include "Game/Game.hpp"
#include <memory>

class MoveToCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // MOVE_TO_COMMAND_HPP
