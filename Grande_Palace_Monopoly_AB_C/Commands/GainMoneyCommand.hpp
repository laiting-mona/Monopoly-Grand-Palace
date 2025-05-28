#ifndef GAIN_MONEY_COMMAND_HPP
#define GAIN_MONEY_COMMAND_HPP

#include "Command.hpp"
#include <memory>

class GainMoneyCommand : public Command {
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // GAIN_MONEY_COMMAND_HPP
