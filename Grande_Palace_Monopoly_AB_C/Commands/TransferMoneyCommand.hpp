#ifndef TRANSFER_MONEY_COMMAND_HPP
#define TRANSFER_MONEY_COMMAND_HPP

#include "Command.hpp"
#include "Game/Game.hpp"
#include <memory>

class TransferMoneyCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // TRANSFER_MONEY_COMMAND_HPP
