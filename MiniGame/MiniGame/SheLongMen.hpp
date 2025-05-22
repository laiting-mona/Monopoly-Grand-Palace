#ifndef SHELONGMEN_HPP
#define SHELONGMEN_HPP

#include "MiniGame.hpp"
#include <string>

class SheLongMen : public MiniGame {
private:
	static const std::string cardNames[13];

	int drawCardInt();
	std::string convertCardType(const int& cardInt);
	int checkInRange(const int& down, const int& up, const int& guess, const int& bet);
	int checkPosition(const int& first, const int& third, const char& guess);

public:
	long long playGame(long long betAmount) override;
};


#endif // !SHELONGMEN_HPP
