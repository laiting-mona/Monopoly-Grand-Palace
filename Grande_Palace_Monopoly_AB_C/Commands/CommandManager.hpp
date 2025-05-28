#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include "Command.hpp"
#include <vector>
#include <string>
#include <memory>

class CommandManager {
private:
    std::vector<std::shared_ptr<Command>> commands;

public:
    void registerCommand(std::shared_ptr<Command> command);
    void listAllCommands() const;
    void executeCommand(const std::string& commandName, std::shared_ptr<Player> player) const;
};

#endif // COMMAND_MANAGER_HPP
