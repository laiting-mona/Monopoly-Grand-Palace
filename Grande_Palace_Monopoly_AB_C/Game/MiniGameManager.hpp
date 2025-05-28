/**
 * @file MiniGameManager.hpp
 * @brief �p�C���޲z�Ҳժ������w�q
 * @details ���ѲΤ@�����H�޲z�ñҰʤ��P���p�C��
 */
#ifndef MINIGAMEMANAGER_HPP
#define MINIGAMEMANAGER_HPP

#include "MiniGames/DragonGateGame.hpp"
#include "MiniGames/HorseRaceGame.hpp"
#include "Game/Player.hpp"
#include <memory>

class MiniGameManager {
public:
    /**
     * @brief Constructor for MiniGameManager.
     *
     * Initializes the mini-game manager.
     */
    MiniGameManager();

    /**
     * @brief Present a menu and play a selected mini-game.
     * @param player The player who is playing the mini-game.
     * @return The net result (money gained or lost) from the played mini-game.
     */
    int playMiniGame(std::shared_ptr<Player> player);

    /**
     * @brief Play a specific mini-game based on choice.
     * @param gameType An identifier for the mini-game (e.g., 1 for Dragon Gate, 2 for Horse Race).
     * @return The net result (money gained or lost) from the played mini-game.
     */
    int playGame(int gameType);

private:
    DragonGateGame dragonGateGame;
    HorseRaceGame horseRaceGame;
};

#endif // MINIGAMEMANAGER_HPP