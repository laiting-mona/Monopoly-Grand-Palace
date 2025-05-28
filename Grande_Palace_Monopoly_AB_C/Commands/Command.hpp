#pragma once
#include <string>
#include <memory>
#include "Game/Player.hpp"

class Command {
public:
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(std::shared_ptr<Player> player) = 0;
    virtual ~Command() = default;
};
