// #include "Game.hpp"
// #include "../Error.hpp"
// #include "../InputManager.hpp"
// #include "MiniGames/MiniGameManager.hpp"
// #include "Utils/Utils.hpp"
// #include <algorithm>
// #include <cstdlib>
// #include <ctime>
// #include <fstream>
// #include <iostream>
// #include <random>
// #include <unordered_map>

// std::default_random_engine Game::engine;
// std::shared_ptr<Game> Game::instance = nullptr;

// Game::Game(const GameConfig& cfg)
//     : config(cfg)
//     , currentState(State::INIT)
//     , gameForceControl(false) {
//     throw NotImplement("`Game::Game` not implement");
// }

// std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
//     throw NotImplement("`Game::getInstance`not implement");
// }

// void Game::initGame() {
//     throw NotImplement("`Game::initGame` not implement");
// }

// void Game::start() {
//     throw NotImplement("`Game::start` not implement");
// }

// void Game::processPlayerAction(std::shared_ptr<Player> player, std::shared_ptr<Tile> tile, bool isCommandResult) {
//     throw NotImplement("`Game::processPlayerAction` not implement");
// }

// bool Game::processCommand(std::shared_ptr<Player> player, const std::string& input) {
//     throw NotImplement("`Game::processCommand` not implement");
// }

// void Game::throwDice(std::shared_ptr<Player> player) {
//     throw NotImplement("`Game::throwDice` not implement");
// }

// void Game::checkGameOver() {
//     throw NotImplement("`Game::checkGameOver` not implement");
// }

// void Game::endGame() {
//     throw NotImplement("`Game::endGame` not implement");
// }

// void Game::changeState(State newState) {
//     throw NotImplement("`Game::changeState` not implement");
// }

// State& operator++(State& state) {
//     throw NotImplement("not implement");
// }

// void Game::setState(const std::string& state) {
//     throw NotImplement("`Game::setState` not implement");
// }

// const nlohmann::json& Game::playerAction() {
//     throw NotImplement("`Game::playerAction` not implement");
// }

// const nlohmann::json& Game::playerAction(const std::string& key) {
//     throw NotImplement("`Game::playerAction` not implement");
// }

// void Game::movePlayer(std::shared_ptr<Player> player, int steps) {
//     throw NotImplement("`Game::movePlayer` not implement");
// }

// std::string Game::getStateString() {
//     throw NotImplement("`Game::getStateString` not implement");
// }

// bool Game::isActivateState() const {
//     throw NotImplement("`Game::isActivateState` not implement");
// }

// bool Game::isRoundState() const {
//     throw NotImplement("`Game::isRoundState` not implement");
// }



#include "Game.hpp"
#include "../Error.hpp"
#include "../InputManager.hpp"
#include "MiniGames/MiniGameManager.hpp"
#include "Utils/Utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>

std::default_random_engine Game::engine;
std::shared_ptr<Game> Game::instance = nullptr;

Game::Game(const GameConfig& cfg)
    : config(cfg)
    , currentState(State::INIT)
    , gameForceControl(false) {
    std::cout << "[Mock] Game constructed." << std::endl;
}

// std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
//     if (!instance) {
//         instance = std::make_shared<Game>(config);
//     }
//     return instance;
// }

std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
    if (!instance) {
        // Replace std::make_shared with this:
        instance = std::shared_ptr<Game>(new Game(config));
    }
    return instance;
}

void Game::initGame() {
    std::cout << "[Mock] Game initialized." << std::endl;
}

void Game::start() {
    std::cout << "[Mock] Game started." << std::endl;
}

void Game::processPlayerAction(std::shared_ptr<Player> player, std::shared_ptr<Tile> tile, bool isCommandResult) {
    std::cout << "[Mock] Processing player action (mock)." << std::endl;
}

bool Game::processCommand(std::shared_ptr<Player> player, const std::string& input) {
    std::cout << "[Mock] Processing command: " << input << std::endl;
    return false; // 假定指令沒成功
}

void Game::throwDice(std::shared_ptr<Player> player) {
    std::cout << "[Mock] Throwing dice for player." << std::endl;
}

void Game::checkGameOver() {
    std::cout << "[Mock] Checking if game over." << std::endl;
}

void Game::endGame() {
    std::cout << "[Mock] Game ended." << std::endl;
}

void Game::changeState(State newState) {
    std::cout << "[Mock] Changing state." << std::endl;
    currentState = newState;
}

State& operator++(State& state) {
    std::cout << "[Mock] Incrementing state enum." << std::endl;
    state = static_cast<State>(static_cast<int>(state) + 1);
    return state;
}

void Game::setState(const std::string& state) {
    std::cout << "[Mock] Setting state to: " << state << std::endl;
}

const nlohmann::json& Game::playerAction() {
    static nlohmann::json dummy;
    std::cout << "[Mock] Getting player action (no key)." << std::endl;
    return dummy;
}

const nlohmann::json& Game::playerAction(const std::string& key) {
    static nlohmann::json dummy;
    std::cout << "[Mock] Getting player action with key: " << key << std::endl;
    return dummy;
}

void Game::movePlayer(std::shared_ptr<Player> player, int steps) {
    std::cout << "[Mock] Moving player by " << steps << " steps." << std::endl;
}

std::string Game::getStateString() {
    std::cout << "[Mock] Getting state string." << std::endl;
    return "INIT";
}

bool Game::isActivateState() const {
    std::cout << "[Mock] Checking isActivateState." << std::endl;
    return false;
}

bool Game::isRoundState() const {
    std::cout << "[Mock] Checking isRoundState." << std::endl;
    return false;
}
