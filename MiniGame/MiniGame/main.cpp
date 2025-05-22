#include "MiniGame.hpp"
#include <iostream>
#include <memory>

int main() {
	std::unique_ptr<MiniGame> game;
	int choice;
	long long bet;

	std::cout << "=== Mini Game Hub ===\n";
	std::cout << "[1] She Long Men\n";
	std::cout << "[2] Horse Racing\n";
	std::cout << "[3] Mystery Box\n";
	std::cout << "Choose a game to play: ";
	std::cin >> choice;

	if (choice == 1) {
		game = std::make_unique<SheLongMen>();
	}
	else if (choice == 2) {
		game = std::make_unique<HorseRace>();
	}
	else if (choice == 3) {
		game = std::make_unique<MysteryBox>();
	}
	else {
		std::cout << "Invalid choice.\n";
		return 0;
	}

	std::cout << "Enter your bet amount: ";
	std::cin >> bet;

	long long result = game->playGame(bet);
	std::cout << "Net result: " << result << "\n";

	return 0;
}