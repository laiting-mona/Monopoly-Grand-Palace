#include "HorseRace.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#define CLEAR_SCREEN "CLS"
#else
#define CLEAR_SCREEN "clear"
#endif

int HorseRace::betHorse() {
	int choice;

	std::cout << "Bet a horse : ";
	std::cin >> choice;

	if (choice < 1 || choice > 4) {
		std::cout << "Invalid choice! Auto choose horse 1...\n";
		choice = 1;
	}

	return choice;
}

std::vector<int> HorseRace::race() {
	const int trackLength = 20;
	int horsePosition[4] = { 0 };
	bool end = false;

	while (!end) {
		for (int i = 0; i < 4; i++) {
			horsePosition[i] += rand() % 3 + 1;
		}

		std::system(CLEAR_SCREEN);
		displayRace(horsePosition, trackLength);
		std::this_thread::sleep_for(std::chrono::milliseconds(333));

		for (int i = 0; i < 4; i++) {
			if (horsePosition[i] >= trackLength) {
				end = true;
			}
		}
	}

	int maxDist = *std::max_element(horsePosition, horsePosition + 4);
	std::vector<int> winners;

	for (int i = 0; i < 4; i++) {
		if (horsePosition[i] == maxDist) {
			winners.push_back(i + 1);
		}
	}

	return winners;
}


void HorseRace::displayRace(const int positions[], int trackLength) {
	for (int i = 0; i < 4; i++) {
		std::cout << "Horse " << i + 1 << ": ";

		for (int j = 0; j < positions[i]; j++) std::cout << "=";

		std::cout << "H" << i + 1 << "-" << positions[i] << std::endl;
	}
}

long long HorseRace::playGame(long long betAmount) {
	std::srand(std::time(nullptr));

	int pickedHorse = betHorse();

	std::cout << "Race starting! Press Enter to begin...";
	std::cin.ignore();
	std::cin.get();

	auto winners = race();

	std::cout << "Winning horse(s): ";
	for (int w : winners) std::cout << "#" << w << " ";
	std::cout << "\n";

	if (std::find(winners.begin(), winners.end(), pickedHorse) != winners.end()) {
		if (winners.size() == 1) {
			std::cout << "Your horse won the race! WIN twice bet amount!!\n";
		}
		else {
			std::cout << "Your horse tied for 1st! WIN twice bet amount!!\n";
		}
		return betAmount * 2;
	}
	else {
		std::cout << "Your horse didn't win! LOSE bet amount!!\n";
		return -betAmount;
	}
}
