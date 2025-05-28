// /**
//  * @file DragonGateGame.cpp
//  * @brief �g�s���p�C������@
//  * @details ��@�g�s���C�����C���޿�A�]�A�o�P�B�P�w�ӭt�P½���D��
//  */
// #include "DragonGateGame.hpp"
// #include "Game/Utils.hpp"
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <cctype>
// #include <string>
// #include <limits>
// using namespace std;

// int DragonGateGame::play() {
//     cout << "========== Dragon Gate Game ==========" << endl;
//     // Prompt for bet amount
//     int bet = 0;
//     do {
//         cout << "Enter your bet amount: ";
//         if (!(cin >> bet)) {
//             cin.clear();
//             cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//             bet = 0;
//         }
//         if (bet <= 0) {
//             cout << "Bet must be a positive integer." << endl;
//         }
//     } while (bet <= 0);

//     // Initialize net result (money change) and pot for tracking current stake
//     int netResult = 0;
//     int pot = bet;
//     // Subtract the bet from player's money (to be returned as negative if lost)
//     netResult -= bet;

//     bool playing = true;
//     while (playing) {
//         // Draw two cards ensuring a gap exists
//         int c1, c2;
//         int low, high;
//         do {
//             c1 = 1 + rand() % 13;
//             c2 = 1 + rand() % 13;
//             low = (c1 < c2 ? c1 : c2);
//             high = (c1 > c2 ? c1 : c2);
//         } while (high <= low + 1);

//         // Helper lambda to get card name
//         auto cardName = [&](int value) -> string {
//             switch (value) {
//             case 1: return string("A");
//             case 11: return string("J");
//             case 12: return string("Q");
//             case 13: return string("K");
//             default: return to_string(value);
//             }
//         };

//         cout << "First card: " << cardName(c1) << ", Second card: " << cardName(c2) << endl;
//         cout << "Will the next card be between them? Drawing the next card..." << endl;

//         int c3 = 1 + rand() % 13;
//         cout << "Third card: " << cardName(c3) << endl;

//         if (c3 > low && c3 < high) {
//             // Win this round
//             cout << "Congratulations! The third card is between the first two." << endl;
//             // Double the pot
//             pot *= 2;
//             cout << "Your current winnings (pot) are now $" << pot << "." << endl;
//             // Ask if player wants to continue to double or quit
//             cout << "Do you want to try double or nothing? (Y/N): ";
//             char choice;
//             cin >> choice;
//             if (tolower(choice) == 'y') {
//                 // Continue playing with current pot
//                 playing = true;
//             }
//             else {
//                 // Stop playing, player takes the pot
//                 netResult += pot;
//                 cout << "You decided to stop. You walk away with $" << pot << "!" << endl;
//                 playing = false;
//             }
//         }
//         else {
//             // Lose this round
//             cout << "Sorry, the third card is not between the first two. You lost your bet." << endl;
//             // Player loses the pot, which was their stake (already deducted from netResult)
//             playing = false;
//         }

//         cout << "--------------------------------------" << endl;
//         waitForKey();
//     }
//     return netResult;
// }

#include "DragonGateGame.hpp"
#include "Game/Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <limits>
using namespace std;

long long DragonGateGame::play() {
    cout << "========== Dragon Gate Game ==========" << endl;

    long long bet = 0;
    do {
        cout << "Enter your bet amount: ";
        if (!(cin >> bet)) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            bet = 0;
        }
        if (bet <= 0) {
            cout << "Bet must be a positive number." << endl;
        }
    } while (bet <= 0);

    // Lambda to convert card number to name
    auto cardName = [](int value) -> string {
        const string names[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        return names[value - 1];
    };

    int card1 = rand() % 13 + 1;
    int card2 = rand() % 13 + 1;
    int card3;
    char guess;

    cout << "First card: " << cardName(card1) << endl;
    cout << "Second card: " << cardName(card2) << endl;

    if (card1 != card2) {
        int lower = min(card1, card2);
        int upper = max(card1, card2);

        cout << "Will the next card be between " << cardName(lower)
             << " and " << cardName(upper) << "? (Y/N): ";
        cin >> guess;

        card3 = rand() % 13 + 1;
        cout << "Third card: " << cardName(card3) << endl;

        if (card3 == card1 || card3 == card2) {
            cout << "Unfortunate! You hit a pillar!! You lose DOUBLE your bet.\n";
            return -2 * bet;
        }

        bool isBetween = (card3 > lower && card3 < upper);
        if ((tolower(guess) == 'y' && isBetween) || (tolower(guess) == 'n' && !isBetween)) {
            cout << "Correct guess! You win your bet amount!\n";
            return bet;
        } else {
            cout << "Wrong guess! You lose your bet.\n";
            return -bet;
        }
    } else {
        cout << "Cards are equal! Predict if the next is Higher (H) or Lower (L) than "
             << cardName(card1) << ": ";
        cin >> guess;

        card3 = rand() % 13 + 1;
        cout << "Third card: " << cardName(card3) << endl;

        if (card3 == card1) {
            cout << "Unfortunate! You hit a pillar!! You lose TRIPLE your bet.\n";
            return -3 * bet;
        }

        bool win = (tolower(guess) == 'h' && card3 > card1) ||
                   (tolower(guess) == 'l' && card3 < card1);
        if (win) {
            cout << "Correct guess! You win your bet amount!\n";
            return bet;
        } else {
            cout << "Wrong guess! You lose your bet.\n";
            return -bet;
        }
    }
}
