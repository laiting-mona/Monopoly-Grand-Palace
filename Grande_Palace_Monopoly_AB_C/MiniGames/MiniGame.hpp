/**
 * @file MiniGame.hpp
 * @brief MiniGame ��H�����A�w�q�Ҧ��p�C�����򥻤����P�欰�C
 * @date 2025/05/17
 */

#ifndef MINIGAME_HPP
#define MINIGAME_HPP

#include <string>
#include <memory>
#include <vector>

class Player;

/**
 * @brief Abstract base class for mini games triggered during gameplay.
 */
class MiniGame {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~MiniGame() = default;

    /**
     * @brief Get the name of the mini game.
     * @return Name string.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Start the mini game.
     * @param players The list of players participating.
     * @param currentPlayer The player currently playing.
     */
    virtual void start(std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<Player> currentPlayer) = 0;

    /**
     * @brief Check if the mini game is finished.
     * @return true if finished, false otherwise.
     */
    virtual bool isFinished() const = 0;

    /**
     * @brief Get the winner(s) of the mini game.
     * @return Vector of winning players.
     */
    virtual std::vector<std::shared_ptr<Player>> getWinners() const = 0;
};

#endif // MINIGAME_HPP