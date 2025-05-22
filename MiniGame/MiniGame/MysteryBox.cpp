#include "MysteryBox.hpp"
#include <iostream>
#include <unordered_map>

const std::string MysteryBox::symbols[24] =
{ "X", "X", "X", "X", "X", "X", "X", "X"
"C", "C", "C", "C", "C", "C", "C",
"R", "R", "R", "R", "R", "R",
"S", "S",
"J" };

std::string MysteryBox::generateSymbol() {
	return symbols[std::rand() % 24];
}

std::vector<std::string> MysteryBox::generateBoxSymbols() {
	std::vector<std::string> box;

	for (int i = 0; i < 3; i++) box.push_back(generateSymbol());

	return box;
}

void MysteryBox::displaySymbols(const std::vector<std::string>& boxSymbol) {
	std::cout << "[ ";

	for (std::string s : boxSymbol) std::cout << s << " ";

	std::cout << "]\n";
}

long long MysteryBox::calculateReward(const std::vector<std::string>& boxSymbol, long long betAmount) {
	std::unordered_map<std::string, int> count;

	for (std::string s : boxSymbol) count[s]++;

	std::cout << "Reward breakdown(rounded):\n";
	if (count["J"] == 1) std::cout << "+5x (Jackpot)\n";
	else if (count["S"] == 2) std::cout << "+4x (2x Super)\n";
	else if (count["S"] == 1) std::cout << "+3x (1x Super)\n";
	else {
		if (count["R"] > 0) std::cout << "+1.2 * " << count["R"] << " (Rare)\n";
		if (count["C"] > 0) std::cout << "+1.0 * " << count["C"] << " (Common)\n";
		if (count["X"] > 0) std::cout << "-1.0 * " << count["X"] << " (Miss)\n";
	}

	if (count["J"] == 1) return betAmount * 5;
	if (count["S"] == 2) return betAmount * 4;
	if (count["S"] == 1) return betAmount * 3;

	double total = 0.0;
	total += count["R"] * 1.2;
	total += count["C"] * 1.0;
	total += count["X"] * -1.0;

	return static_cast<long long>(total * betAmount);
}

long long MysteryBox::playGame(long long betAmount) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::cout << "\n=== Symbol TLDR ===\n";
	std::cout << "X - Miss (-1x per X)\n";
	std::cout << "C - Common (+0.75x per C)\n";
	std::cout << "R - Rare (+1x per R)\n";
	std::cout << "S - Super (+3x if 1 S, +4x if 2 S)\n";
	std::cout << "J - Jackpot (+5x instantly)\n\n";

	std::vector<std::vector<std::string>> boxes(3);
	for (int i = 0; i < 3; ++i) boxes[i] = generateBoxSymbols();

	int choice;
	std::cout << "Choose a safe [1-3]: ";
	std::cin >> choice;
	if (choice < 1 || choice > 3) {
		std::cout << "Invalid choice! Auto choose safe 1\n";
		choice = 1;
	}

	std::vector<std::string> chosenBox = boxes[choice - 1];
	std::cout << "Opening safe " << choice << "...\n";
	displaySymbols(chosenBox);

	long long reward = calculateReward(chosenBox, betAmount);
	if (reward >= 0) std::cout << "You win " << reward << "!\n";
	else std::cout << "You lose " << -reward << "!\n";

	return reward;
}