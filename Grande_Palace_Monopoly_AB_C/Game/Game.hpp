#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Error.hpp"
#include "GameConfig.hpp"
#include "Player.hpp"
#include "MiniGameManager.hpp"
#include "Commands/CommandManager.hpp"
#include "Tiles/Tile.hpp"
#include "nlohmann/json.hpp"
#include <memory>
#include <random>
#include <vector>

enum class State { INIT, START, MOVED, ROUND_END, FINISH };
State& operator++(State& state);

class Game {
    friend class GameRecorder;

private:
    Board* board;
    GameConfig config;
    State currentState;
    std::string diceResult;
    nlohmann::json dialogueData;
    nlohmann::json commandData;
    bool gameForceControl;

    std::vector<std::shared_ptr<Player>> players;
    static std::default_random_engine engine;
    static std::shared_ptr<Game> instance;
    std::shared_ptr<MiniGameManager> miniGameManager;
    CommandManager commandManager;

public:
    explicit Game(const GameConfig& cfg);
    Game(const Game&) = delete; // �T�����
    Game& operator=(const Game&) = delete;

    static std::shared_ptr<Game> getInstance(const GameConfig& config);

    /**
     * @brief Initialize the game (board setup, etc.).
     */
    void initGame();
    /**
     * @brief Start the main game loop with specified victory condition.
     * @param victoryCondition 1 for asset threshold, 2 for territory control, 3 for points mode.
     * @param maxRounds Maximum rounds to play (only for points mode).
     */
    void start(int victoryCondition, int maxRounds = 0);
    /**
     * @brief Add players to the game.
     */
    void addPlayers(const std::vector<std::shared_ptr<Player>>& pls);

    void checkGameOver();
    void endGame();
    void changeState(State newState);
    void setState(const std::string& state);
    std::string getStateString();
    bool isActivateState() const;
    bool isRoundState() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const { return players; }
    static std::shared_ptr<Game> getInstance();
    std::shared_ptr<MiniGameManager> getMiniGameManager() const { return miniGameManager; }
    Board* getBoard() const { return board; }
};

#endif // GAME_HPP