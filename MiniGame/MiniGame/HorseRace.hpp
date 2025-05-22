#ifndef HORSERACE_HPP
#define HORSERACE_HPP

#include "MiniGame.hpp"
#include <string>
#include <vector>

class HorseRace : public MiniGame {
private:
	int betHorse();
	std::vector<int> race();
	void displayRace(const int positiosns[], int trackLength);

public:
	long long playGame(long long betAmount) override;
};

#endif // !HORSERACE_HPP
