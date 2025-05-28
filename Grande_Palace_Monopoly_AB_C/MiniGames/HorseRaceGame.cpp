// /**
//  * @file HorseRaceGame.cpp
//  * @brief �䰨�p�C������@
//  * @details ��@�䰨�C�����C���޿�A�]�A��`�B�H�����ɵ��G�P�����p��
//  */
// #include "HorseRaceGame.hpp"
// #include "Game/Utils.hpp"
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <limits>
// using namespace std;

// int HorseRaceGame::play() {
//     cout << "========== Horse Race Game ==========" << endl;
//     // Prompt for bet amount
//     int bet = 0;
//     do {
//         cout << "Enter your bet amount: ";
//         if (!(cin >> bet)) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             bet = 0;
//         }
//         if (bet <= 0) {
//             cout << "Bet must be a positive integer." << endl;
//         }
//     } while (bet <= 0);

//     // Prompt for horse choice
//     int horseCount = 3;  // number of horses in the race
//     int choice = 0;
//     do {
//         cout << "Choose a horse to bet on (1-" << horseCount << "): ";
//         if (!(cin >> choice)) {
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             choice = 0;
//         }
//         if (choice < 1 || choice > horseCount) {
//             cout << "Invalid choice. Please select a horse between 1 and " << horseCount << "." << endl;
//         }
//     } while (choice < 1 || choice > horseCount);

//     // Initialize net result and subtract bet from player's money
//     int netResult = 0;
//     netResult -= bet;

//     cout << "The race is about to start... and they're off!" << endl;

//     // Simulate a simple race commentary
//     int winner = 1 + rand() % horseCount;
//     int lead1 = 1 + rand() % horseCount;
//     if (lead1 == winner) {
//         // ensure initial lead is not the same as eventual winner
//         lead1 = (lead1 % horseCount) + 1;
//     }
//     cout << "Horse " << lead1 << " takes an early lead!" << endl;
//     cout << "Around the final turn, horse " << winner << " is making a move!" << endl;

//     // Announce winner
//     cout << "And the winner is... Horse " << winner << "!" << endl;

//     // Determine outcome
//     if (choice == winner) {
//         cout << "Congratulations! Your horse won the race!" << endl;
//         // Winner gets double the bet (profit equal to bet)
//         netResult += bet * 2;
//     }
//     else {
//         cout << "Your horse didn't win. Better luck next time!" << endl;
//         // netResult remains -bet (lost bet)
//     }

//     cout << "======================================" << endl;
//     waitForKey();
//     return netResult;
// }

#include "HorseRaceGame.hpp"
#include "Game/Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <thread>
#include <chrono>
#include <algorithm>

#ifdef _WIN32
#define CLEAR_SCREEN "CLS"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

namespace {
    const int horseCount = 4;
    const int trackLength = 20;
}

int HorseRaceGame::betHorse() {
    int choice = 0;
    do {
        cout << "Choose a horse to bet on (1-" << horseCount << "): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            choice = 0;
        }
        if (choice < 1 || choice > horseCount) {
            cout << "Invalid choice. Defaulting to horse 1...\n";
            choice = 1;
        }
    } while (choice < 1 || choice > horseCount);

    return choice;
}

vector<int> HorseRaceGame::race() {
    int horsePosition[horseCount] = { 0 };
    bool end = false;

    while (!end) {
        for (int i = 0; i < horseCount; ++i)
            horsePosition[i] += rand() % 3 + 1;

        system(CLEAR_SCREEN);
        displayRace(horsePosition);
        this_thread::sleep_for(chrono::milliseconds(333));

        for (int i = 0; i < horseCount; ++i)
            if (horsePosition[i] >= trackLength) end = true;
    }

    int maxDist = *max_element(horsePosition, horsePosition + horseCount);
    vector<int> winners;
    for (int i = 0; i < horseCount; ++i) {
        if (horsePosition[i] == maxDist)
            winners.push_back(i + 1);
    }
    return winners;
}

void HorseRaceGame::displayRace(const int positions[]) {
    for (int i = 0; i < horseCount; ++i) {
        cout << "Horse " << i + 1 << ": ";
        for (int j = 0; j < positions[i]; ++j)
            cout << "=";
        cout << "H" << i + 1 << "-" << positions[i] << endl;
    }
}

long long HorseRaceGame::play() {
    cout << "========== Horse Race Game ==========" << endl;

    long long bet = 0;
    do {
        cout << "Enter your bet amount: ";
        if (!(cin >> bet)) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            bet = 0;
        }
        if (bet <= 0) {
            cout << "Bet must be a positive amount." << endl;
        }
    } while (bet <= 0);

    int pickedHorse = betHorse();
    cout << "Press Enter to start the race...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cin.get();

    auto winners = race();

    cout << "Winning horse(s): ";
    for (int w : winners) cout << "#" << w << " ";
    cout << "\n";

    long long netResult = -bet;
    if (find(winners.begin(), winners.end(), pickedHorse) != winners.end()) {
        cout << (winners.size() == 1 ? "Your horse won! " : "Your horse tied for 1st! ");
        cout << "You win 2x your bet!\n";
        netResult += bet * 2;
    } else {
        cout << "Your horse didn't win. You lose your bet.\n";
    }
    return netResult;
}
