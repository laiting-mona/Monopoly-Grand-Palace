/**
 * @file MiniGameManager.cpp
 * @brief �p�C���޲z�Ҳժ���@
 * @details ��@�p�C���޲z���\��A�i�ھڿ�ܱҰʤ��P���p�C���æ^�ǵ��G
 */
#include "MiniGameManager.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

MiniGameManager::MiniGameManager() {
    // Initialize random seed for mini-games
    srand(time(nullptr));
}

int MiniGameManager::playMiniGame(std::shared_ptr<Player> player) {
    cout << "====== Mini-Game Menu ======" << endl;
    cout << "1. Dragon Gate Game" << endl;
    cout << "2. Horse Race Game" << endl;
    cout << "Please enter the number of the game you want to play: ";
    int choice = 0;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        choice = 0;
    }
    // Validate choice
    if (choice != 1 && choice != 2) {
        cout << "Invalid selection. No mini-game will be played." << endl;
        return 0;
    }

    // Play selected game
    int result = playGame(choice);
    if (result != 0 && player) {
        if (result > 0) {
            player->addMoney(result);
        } else {
            player->deductMoney(-result); // result 是負數
        }
    }

    // Display result
    if (result > 0) {
        cout << "Mini-game result: You won $" << result << "!" << endl;
        cout << "Your new balance: $" << player->getMoney() << endl;
        delayMilliseconds(1200);
    }
    else if (result < 0) {
        cout << "Mini-game result: You lost $" << (-result) << "." << endl;
        cout << "Your new balance: $" << player->getMoney() << endl;
        delayMilliseconds(1200);
    }
    else {
        cout << "Mini-game result: No win/loss." << endl;
        cout << "Your balance remains: $" << player->getMoney() << endl;
        delayMilliseconds(1200);
    }
    cout << "============================" << endl;
    waitForKey();
    return result;
}

int MiniGameManager::playGame(int gameType) {
    switch (gameType) {
    case 1:
        return dragonGateGame.play();
    case 2:
        return horseRaceGame.play();
    default:
        return 0;
    }
}