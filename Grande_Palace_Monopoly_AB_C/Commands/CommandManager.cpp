#include "CommandManager.hpp"
#include "Game/Utils.hpp"
#include <iostream>

void CommandManager::registerCommand(std::shared_ptr<Command> command) {
    commands.push_back(command);
}

void CommandManager::listAllCommands() const {
    std::cout << "\n=== Available Commands ===" << std::endl;
    for (const auto& command : commands) {
        std::cout << "- " << command->getName() << ": " << command->getDescription() << std::endl;
    }
    std::cout << "==========================" << std::endl;
}

void CommandManager::executeCommand(const std::string& commandName, std::shared_ptr<Player> player) const {
    for (const auto& command : commands) {
        if (command->getName() == commandName) {
            command->execute(player);
            return;
        }
    }
    std::cout << "Command not found: " << commandName << std::endl;
    delayMilliseconds(1200);
}
