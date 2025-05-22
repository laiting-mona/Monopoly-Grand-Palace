#ifndef MYSTERYBOX_HPP
#define MYSTERYBOX_HPP

#include "MiniGame.hpp"
#include <vector>
#include <string>

class MysteryBox : public MiniGame {
private:
	static const std::string symbols[24];

	std::string generateSymbol();
	std::vector<std::string> generateBoxSymbols();
	void displaySymbols(const std::vector<std::string>& boxSymbols);
	long long calculateReward(const std::vector<std::string>& boxSymbols, long long bet);

public:
	long long playGame(long long betAmount) override;
};

#endif // !MYSTERYBOX_HPP