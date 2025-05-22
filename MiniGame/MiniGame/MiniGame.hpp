#ifndef MINIGAME_HPP
#define MINIGAME_HPP

class MiniGame {
public:
	virtual long long playGame(long long betAmount) = 0;
	virtual ~MiniGame() = default;
};

#include "SheLongMen.hpp"	
#include "HorseRace.hpp"
#include "MysteryBox.hpp"

#endif // !MINIGAME_HPP