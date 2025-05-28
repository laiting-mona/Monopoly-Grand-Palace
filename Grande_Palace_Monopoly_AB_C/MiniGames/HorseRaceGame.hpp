// /**
//  * @file HorseRaceGame.hpp
//  * @brief �䰨�p�C���������w�q
//  * @details �w�q�䰨�p�C�������O�P�ާ@��k
//  */
// #ifndef HORSERACEGAME_HPP
// #define HORSERACEGAME_HPP

// class HorseRaceGame {
// public:
//     /**
//      * @brief Play the Horse Race mini-game.
//      * @return The net money change (positive for win, negative for loss, zero for none).
//      */
//     int play();
// };

// #endif // HORSERACEGAME_HPP

#ifndef HORSE_RACE_GAME_HPP
#define HORSE_RACE_GAME_HPP

#include <vector>

class HorseRaceGame {
public:
    long long play(); 

private:
    int betHorse();
    std::vector<int> race();
    void displayRace(const int positions[]);
};

#endif
