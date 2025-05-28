#include "Game.hpp"
#include "GameConfig.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "Utils.hpp"
#include "Board.hpp"
#include "StartTile.hpp"
#include "StoreTile.hpp"
#include "PropertyTile.hpp"
#include "MiniGameTile.hpp"
#include "HospitalTile.hpp"
#include "EventTile.hpp"
#include "BotPlayer.hpp"
#include "Cards/Card.hpp"
#include "Cards/BarrierCard.hpp"
#include "Cards/DemolitionCard.hpp"
#include "Cards/DiceControlCard.hpp"
#include "Cards/FateCard.hpp"
#include "Cards/RocketCard.hpp"
#include "Cards/TollCard.hpp"
#include "Commands/CommandManager.hpp"
#include "Commands/ListCommandsCommand.hpp"
#include "Commands/MoveToCommand.hpp"
#include "Commands/GainMoneyCommand.hpp"
#include "Commands/TransferMoneyCommand.hpp"
#include "Commands/GainCardCommand.hpp"
#include "Commands/ChangePhaseCommand.hpp"
#include "Commands/TriggerMiniGameCommand.hpp"
#include "Commands/ShowAllPlayersCommand.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
#include <limits>
#include <climits>

std::default_random_engine Game::engine;
std::shared_ptr<Game> Game::instance = nullptr;

Game::Game(const GameConfig& cfg)
    : board(nullptr)
    , config(cfg)
    , currentState(State::INIT)
    , gameForceControl(false) {
}

std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
    if (!instance) {
        instance = std::shared_ptr<Game>(new Game(config));
    }
    return instance;
}

std::shared_ptr<Game> Game::getInstance() {
    return instance;
}

void Game::initGame() { 
    board = Board::getInstance(config);
    if (board) {
        miniGameManager = std::make_shared<MiniGameManager>();
        board->init(config, players, miniGameManager);
    }

    // initialize players
    std::default_random_engine rng(static_cast<unsigned>(time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 4);  // 5 types of cards
    miniGameManager = std::make_shared<MiniGameManager>();
    commandManager.registerCommand(std::make_shared<ListCommandsCommand>(&commandManager));
    commandManager.registerCommand(std::make_shared<MoveToCommand>());
    commandManager.registerCommand(std::make_shared<GainMoneyCommand>());
    commandManager.registerCommand(std::make_shared<TransferMoneyCommand>());
    commandManager.registerCommand(std::make_shared<GainCardCommand>());
    commandManager.registerCommand(std::make_shared<ChangePhaseCommand>());
    commandManager.registerCommand(std::make_shared<TriggerMiniGameCommand>());
    commandManager.registerCommand(std::make_shared<ShowAllPlayersCommand>());


    for (auto& player : players) {
        for (int i = 0; i < 2; ++i) {
            std::shared_ptr<Card> card;
            int type = dist(rng);
            switch (type) {
                case 0:
                    card = std::make_shared<RocketCard>(2);  // 2 turns in hospital
                    break;
                case 1:
                    card = std::make_shared<BarrierCard>();
                    break;
                case 2:
                    card = std::make_shared<DemolitionCard>();
                    break;
                case 3:
                    card = std::make_shared<DiceControlCard>();
                    break;
                case 4:
                    card = std::make_shared<FateCard>();
                    break;
                case 5:
                    card = std::make_shared<TollCard>();
                    break;
            }
            player->addCard(card);
        }
    }
}

void Game::start(int victoryCondition, int maxRounds) {
    bool gameEnd = false;
    int roundsPlayed = 0;
    int totalProperties = 0;
    if (board) {
        for (auto& tile : board->getTileList()) {
            if (std::dynamic_pointer_cast<PropertyTile>(tile)) {
                totalProperties++;
            }
        }
    }

    while (!gameEnd) {
        roundsPlayed++;
        for (auto& player : players) {
            Board::clearScreen();
            board->drawBoard();
            delayMilliseconds(800);
            std::cout << "It's " << player->getDisplayName() << "'s turn." << std::endl;
            delayMilliseconds(1200);
            player->displayInfo();
            board->clearScreen();
            board->drawBoard();
            std::cout << "Do you want to enter a command? (y/n): ";
            char input;
            std::cin >> input;
            if (input == 'y' || input == 'Y') {
                commandManager.listAllCommands();
                std::string cmdName;
                std::cout << "Enter command name: ";
                std::cin >> cmdName;
                commandManager.executeCommand(cmdName, player);
            }
            board->clearScreen();
            board->drawBoard();

            if (player->isBankrupt()) continue;

            if (player->isInHospital()) {
                std::cout << player->getDisplayName() << " is currently in the hospital, still recovering for "
                        << player->getHospitalRoundLeft() << " rounds." << std::endl;

                std::cout << "You can choose to:" << std::endl;
                std::cout << "1. Roll Dice (Must roll 10 or higher to be released)" << std::endl;
                std::cout << "2. Pay Hospital Fee (Requires $1000)" << std::endl;
                std::cout << "3. Continue Recovery (No action)" << std::endl;
                std::cout << "Please choose an action (1/2/3): ";
                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    int dice = player->rollDice();
                    std::cout << "You rolled " << dice << "." << std::endl;
                    if (dice >= 10) {
                        std::cout << "You have been released from the hospital!" << std::endl;
                        player->recoverFromHospital();
                    } else {
                        std::cout << "Failed to roll high enough, continue recovery." << std::endl;
                        player->updateHospitalStatus();
                    }
                } else if (choice == 2) {
                    if (player->getMoney() >= 3000) {
                        player->deductMoney(3000);
                        std::cout << "Successfully paid for hospital release!" << std::endl;
                        player->recoverFromHospital();
                    } else {
                        std::cout << "Insufficient funds for hospital release." << std::endl;
                        player->updateHospitalStatus();
                    }
                } else {
                    player->updateHospitalStatus();
                }

                delayMilliseconds(1200);
                continue;
            }

            if (!player->getCards().empty()) {
                std::cout << "Do you want to use a card? (y/n): ";
                char useCard;
                std::cin >> useCard;
                if (useCard == 'y' || useCard == 'Y') {
                    player->displayCards(players);
                    std::cout << "Enter the card number to use: ";
                    int cardIndex;
                    std::cin >> cardIndex;
                    player->useCard(cardIndex - 1, players);
                }
            }

            int steps = player->rollDice();
            std::cout << player->getName() << " rolled " << steps << "." << std::endl;
            delayMilliseconds(1200);
            int oldPos = player->getPosition();

            if (oldPos + steps >= board->getSize()) {
                auto startTile = board->getTile(0);
                if (startTile) {
                    auto st = std::dynamic_pointer_cast<StartTile>(startTile);
                    if (st) {
                        st->passBy(player);
                    }
                    else {
                        player->addMoney(config.getPassingStartBonus());
                        std::cout << player->getName() << " passed the start point and received $"
                            << config.getPassingStartBonus() << std::endl;
                        delayMilliseconds(1200);
                    }
                }
            }

            board->movePlayerStepByStep(player, steps);
            int newPos = player->getPosition();
            std::shared_ptr<Tile> tile = board->getTile(newPos);
            
            if (tile && tile->getTollRounds() > 0) {
                auto owner = tile->getTollOwner();
                if (owner && owner != player) {
                    std::cout << player->getDisplayName() << " pass through " << owner->getDisplayName() << "'s toll at "
                        << tile->getName() << std::endl;
                    std::cout << "Must pay $" << tile->getTollRounds() * 100 << " to " << owner->getDisplayName() << std::endl;
                    delayMilliseconds(1200);
                    player->deductMoney(300);
                    owner->addMoney(300);
                }
            }

            board->clearScreen();
            board->drawBoard();
            TileAction action = tile->landOn(player);

            if (action == TileAction::PURCHASE_PROPERTY) {
                auto prop = std::dynamic_pointer_cast<PropertyTile>(tile);
                auto bot = std::dynamic_pointer_cast<BotPlayer>(player);
                if (prop) {
                    if (bot) {
                        bot->purchaseProperty(prop);
                    }
                    else {
                        std::cout << "Do you want to buy " << prop->getName() << "? (y/n): ";
                        char buy;
                        std::cin >> buy;
                        if (buy == 'y' || buy == 'Y') {
                            prop->purchase(player);
                        }
                    }
                }
            }
            else if (action == TileAction::OWN) {
                auto prop = std::dynamic_pointer_cast<PropertyTile>(tile);
                auto bot = std::dynamic_pointer_cast<BotPlayer>(player);

                if (prop && prop->getPropertyOwner() == player) {
                    if (bot) {
                        // Bot automatically upgrades if possible
                        if (prop->canUpgrade()) {
                            bot->upgradeProperty(prop);
                        }
                    } else {
                        std::cout << "You own this property: " << prop->getName() << std::endl;
                        std::cout << "Do you want to (u)upgrade or (s)sell this property? (u/s/n): ";
                        char choice;
                        std::cin >> choice;

                        if (choice == 'u' || choice == 'U') {
                            if (prop->canUpgrade()) {
                                if (prop->upgrade(player)) {
                                    std::cout << "Upgrade successful!\n";
                                } else {
                                    std::cout << "Upgrade failed. Not enough money?\n";
                                }
                            } else {
                                std::cout << "This property is already at max level.\n";
                            }
                        } else if (choice == 's' || choice == 'S') {
                            prop->sell(player);
                            std::cout << "Property sold for $" << prop->getSellingPrice() << ".\n";
                        } else {
                            std::cout << "No action taken.\n";
                        }
                    }
                }
            }
            else if (action == TileAction::MINI_GAME) {
                std::cout << "Triggered a mini-game!" << std::endl;
                delayMilliseconds(1200);
                miniGameManager->playMiniGame(player);
            }

            bool win = false;
            std::shared_ptr<Player> winner = nullptr;

            // if (victoryCondition == 1) {
            //     if (player->getMoney() >= config.getWinMoney()) {
            //         win = true;
            //         winner = player;
            //     }
            // }
            // else if (victoryCondition == 2) {
            //     int ownedCount = player->getProperties().size();
            //     if (ownedCount > totalProperties / 2) {
            //         win = true;
            //         winner = player;
            //     }
            // }

            if (victoryCondition == 1) {
                // Asset Target Victory: check total assets (cash + property)
                long long totalAssets = player->getMoney();
                for (auto& tile : player->getProperties()) {
                    auto prop = std::dynamic_pointer_cast<PropertyTile>(tile);
                    if (prop) {
                        totalAssets += prop->getSellingPrice();
                    }
                }

                if (totalAssets >= config.getWinMoney()) {
                    std::cout << player->getName() << " has reached the asset target! (Total assets: $"
                            << totalAssets << ", Target: $" << config.getWinMoney() << ")\n";
                    delayMilliseconds(1200);
                    win = true;
                    winner = player;
                }
            }
            else if (victoryCondition == 2) {
                // Property Majority Victory: own more than half of all properties
                int playerPropertyCount = static_cast<int>(player->getProperties().size());
                int majorityThreshold = totalProperties / 2;

                if (playerPropertyCount > majorityThreshold) {
                    std::cout << player->getName() << " owns the majority of properties! ("
                            << playerPropertyCount << "/" << totalProperties << ")\n";
                    delayMilliseconds(1200);
                    win = true;
                    winner = player;
                }
            }


            int aliveCount = 0;
            for (auto& p : players) {
                if (!p->isBankrupt()) {
                    aliveCount++;
                    winner = p;
                }
            }
            if (aliveCount <= 1 && winner) {
                win = true;
            }

            if (win && winner) {
                Board::clearScreen();
                board->drawBoard();
                std::cout << "Player " << winner->getName() << " has met the victory conditions!" << std::endl;
                delayMilliseconds(1200);
                gameEnd = true;
                break;
            }

            for (auto& tile : board->getTileList()) {
                tile->updateTollStatus();
            }
        }

        if (victoryCondition == 3 && roundsPlayed >= maxRounds && maxRounds > 0) {
            Board::clearScreen();
            board->drawBoard();

            std::shared_ptr<Player> topPlayer = nullptr;
            long long topMoney = LLONG_MIN;

            for (auto& p : players) {
                if (p->isBankrupt()) continue;

                long long totalMoney = p->getMoney();
                for (auto& tile : p->getProperties()) {
                    auto prop = std::dynamic_pointer_cast<PropertyTile>(tile);
                    if (prop) totalMoney += prop->getSellingPrice();
                }

                if (!topPlayer || totalMoney > topMoney) {
                    topPlayer = p;
                    topMoney = totalMoney;
                }
                std::cout << p->getName() << " has $" << p->getMoney()
                          << " cash and $" << (totalMoney - p->getMoney()) << " in property, total: $" << totalMoney << std::endl;
            }

            if (topPlayer) {
                std::cout << "Player " << topPlayer->getName()
                        << " has the most assets after " << maxRounds << " rounds and wins!" << std::endl;
                delayMilliseconds(1500);
            } else {
                std::cout << "Game over: All players are bankrupt." << std::endl;
                delayMilliseconds(1500);
            }

            gameEnd = true;
        }

        if (gameForceControl) {
            std::cout << "Game forced to end by control command." << std::endl;
            gameEnd = true;
        }

        if (gameEnd) break;
    }
}

void Game::changeState(State newState) {
    currentState = newState;
}

void Game::addPlayers(const std::vector<std::shared_ptr<Player>>& pls) {
    players = pls;
}
