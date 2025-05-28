#ifndef CHANGE_PHASE_COMMAND_HPP
#define CHANGE_PHASE_COMMAND_HPP

#include "Command.hpp"
#include "Game/Game.hpp"
#include <memory>

class ChangePhaseCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // CHANGE_PHASE_COMMAND_HPP
