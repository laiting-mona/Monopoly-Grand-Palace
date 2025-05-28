#include "ListCommandsCommand.hpp"
#include <iostream>

ListCommandsCommand::ListCommandsCommand(CommandManager* mgr)
    : manager(mgr) {}

std::string ListCommandsCommand::getName() const {
    return "list_commands";
}

std::string ListCommandsCommand::getDescription() const {
    return "List all available commands";
}

void ListCommandsCommand::execute(std::shared_ptr<Player> player) {
    manager->listAllCommands();
}
