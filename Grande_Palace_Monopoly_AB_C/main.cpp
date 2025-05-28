#include "Game/Game.hpp"
#include "Game/GameConfig.hpp"
#include "Game/SingletonManager.hpp"
#include "Game/Player.hpp"
#include "Game/BotPlayer.hpp"
#include "Cards/RocketCard.hpp"
#include <exception>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits> 

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr)); // Seed random generator for dice

    // Load game configuration from file
    GameConfig& config = GameConfig::getInstance();
    try {
        config.loadConfig();
    }
    catch (const std::exception& e) {
        cerr << "Config load error: " << e.what() << endl;
        return 1;
    }

    // initial game title
    std::cout << "\n\n\n\n\n\n";
    std::cout << "  __  __                             _       \n";
    std::cout << " |  \\/  | ___  _ __   ___  _ __  ___| |_   _ \n";
    std::cout << " | |\\/| |/ _ \\| '_ \\ / _ \\| '_ \\/ _ \\ | | | |\n";
    std::cout << " | |  | | (_) | | | | (_) | |_) \\__/ / |_| |\n";
    std::cout << " |_|  |_|\\___/|_| |_|\\___/| .__/\\___|_|\\__, |\n";
    std::cout << "                          |_|          |___/ \n";

    std::cout << "\n\n\n\n\n\nWelcome to the Monopoly Game!\n\n";
    #ifdef _WIN32
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
    #else
        std::cout << "Press ENTER to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    #endif

    #ifdef _WIN32
        system("cls");
    #else
        std::cout << "\033[2J\033[H";
    #endif

    // Ask for number of players (2-4)
    int numPlayers;
    cout << "Please enter the number of players (2-4): ";
    cin >> numPlayers;
    while (numPlayers < 2 || numPlayers > 4) {
        cout << "Number of players must be between 2 and 4. Please re-enter: ";
        cin >> numPlayers;
    }
    config.setPlayersNum(numPlayers);

    // Ask if including Bot players and get names
    vector<shared_ptr<Player>> players;
    for (int i = 1; i <= numPlayers; ++i) {
        char botChoice;
        cout << "Is player " << i << " a bot (y/n)? ";
        cin >> botChoice;
        bool isBot = (botChoice == 'y' || botChoice == 'Y');
        string name;
        if (isBot) {
            name = "Bot" + to_string(i);
        }
        else {
            cout << "Please enter the name of player " << i << ": ";
            cin >> name;
        }
        // Ensure name is unique
        for (const auto& p : players) {
            if (p->getName() == name) {
                name += "_";
                break;
            }
        }
        // Assign icon and color from config lists
        string icon = config.getPlayerIcons()[i - 1];
        string color = config.getPlayerColors()[i - 1];
        long long startMoney = 0;
        // Use default from config based on mode (if 2 players use DUEL, else DEBUG)
        if (numPlayers == 2) {
            config.setMode(GameMode::DUEL);
            startMoney = config.getStartMoney();
        }
        else {
            config.setMode(GameMode::DEBUG);
            startMoney = config.getStartMoney();
        }
        shared_ptr<Player> player;
        if (isBot) {
            player = make_shared<BotPlayer>(name, icon, color, startMoney);
        }
        else {
            player = make_shared<Player>(name, icon, color, startMoney);
        }
        players.push_back(player);
    }

    // Ask for victory condition
    cout << "Please select victory condition (1. Asset Target 2. Property Majority 3. Round Limit): ";
    int victoryChoice;
    cin >> victoryChoice;
    int maxRounds = 0;
    if (victoryChoice == 3) {
        cout << "Please enter the maximum number of rounds: ";
        cin >> maxRounds;
        if (maxRounds < 1) maxRounds = 10;
    }

    // Initialize game singleton and board
    shared_ptr<Game> game = Game::getInstance(config);
    game->addPlayers(players);
    game->initGame();
    // Start game loop
    game->start(victoryChoice, maxRounds);

    // End of game
    Board::destroyInstance();
    return 0;
}