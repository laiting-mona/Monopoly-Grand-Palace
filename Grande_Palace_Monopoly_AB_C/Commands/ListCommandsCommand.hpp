#ifndef LIST_COMMANDS_COMMAND_HPP
#define LIST_COMMANDS_COMMAND_HPP

#include "Command.hpp"
#include "CommandManager.hpp"
#include <memory>

class ListCommandsCommand : public Command {
private:
    CommandManager* manager;

public:
    explicit ListCommandsCommand(CommandManager* mgr);

    std::string getName() const override;
    std::string getDescription() const override;
    void execute(std::shared_ptr<Player> player) override;
};

#endif // LIST_COMMANDS_COMMAND_HPP
