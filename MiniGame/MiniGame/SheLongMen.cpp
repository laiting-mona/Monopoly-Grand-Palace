#include "SheLongMen.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

const std::string SheLongMen::cardNames[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

int SheLongMen::drawCardInt() {
	return rand() % 13 + 1;
}

std::string SheLongMen::convertCardType(const int& cardInt) {
	return cardNames[cardInt - 1];
}

int SheLongMen::checkInRange(const int& down, const int& up, const int& third, const int& bet) {
	if (down < third && third < up) {
		std::cout << "Correct guess! You Win!! WIN bet amount\n";
		return bet;
	}
	else {
		std::cout << "Wrong guess! You Lose!! LOSE bet amount\n";
		return -bet;
	}
}

int SheLongMen::checkPosition(const int& first, const int& third, const char& guess) {
	if (guess == 'h' || guess == 'H') return first < third;
	else if (guess == 'l' || guess == 'L') return first > third;
	return false;
}

long long SheLongMen::playGame(long long betAmount) {
	std::srand(std::time(nullptr));

	int card1 = drawCardInt(), card2 = drawCardInt(), card3;
	char guess;

	std::cout << "First card	-> " << convertCardType(card1) << std::endl;
	std::cout << "Second card	-> " << convertCardType(card2) << std::endl;

	if (card1 != card2) {
		int lowerBound = std::min(card1, card2), upperBound = std::max(card1, card2);

		std::cout << "Will the next card between " << convertCardType(lowerBound) << " & " << convertCardType(upperBound) << " ? (y/n): ";
		std::cin >> guess;

		card3 = drawCardInt();
		std::cout << "Third card	-> " << card3 << std::endl;

		if (card1 == card3 || card2 == card3) {
			std::cout << "Unfortunate! You hit a pillar!! LOSE DOUBLE bet amount\n";
			return -2 * betAmount;
		}

		if (guess == 'y' || guess == 'Y') return checkInRange(lowerBound, upperBound, card3, betAmount);
		else if (guess == 'n' || guess == 'N')return checkInRange(lowerBound, upperBound, card3, betAmount);
		else {
			std::cout << "WRONG guess! LOSES bet amount\n";
			return -betAmount;
		}
	}
	else {
		std::cout << "Will the next card lower(l) or higher(h) than " << convertCardType(card1) << " ? : ";
		std::cin >> guess;

		card3 = drawCardInt();
		std::cout << "Third card	-> " << card3 << std::endl;

		if (card1 == card3) {
			std::cout << "Unfortunate! You hit a pillar!! LOSE TRIPLE bet amount\n";
			return -3 * betAmount;
		}

		if (checkPosition(card1, card3, guess)) {
			std::cout << "Correct guess! WIN bet money!!\n";
			return betAmount;
		}
		else {
			std::cout << "Wrong guess! LOSE bet money!!\n";
			return -betAmount;
		}

	}
}