#include "Game/Game.hpp"
#include "Game/GameConfig.hpp"
#include "SingletonManager.hpp"
#include "Game/Player.hpp"
#include "Cards/RocketCard.hpp"
#include <exception>
#include <iostream>

using namespace std;
int main() {
    // 建立兩個玩家
    auto player1 = std::make_shared<Player>("玩家A", "iconA", "red", 1000);
    auto player2 = std::make_shared<Player>("玩家B", "iconB", "blue", 1000);

    // 建立 RocketCard (住院 3 回合)
    RocketCard rocketCard(3);

    // 設定 RocketCard 的目標玩家
    rocketCard.setTargetPlayer(player2);

    // 玩家A 使用 RocketCard
    std::vector<std::shared_ptr<Player>> players = {player1, player2};
    rocketCard.useEffect(players, player1);

    // 印出玩家B的狀態
    std::cout << player2->getName() << " 是否在醫院？ " << (player2->isInHospital() ? "是" : "否") << std::endl;
    std::cout << player1->getName() << " 是否在醫院？ " << (player1->isInHospital() ? "是" : "否") << std::endl;

    // 如果 Player 有 getHospitalRoundLeft()，可以印出剩餘回合
    // 沒有的話要在 Player.hpp 補上：
    // int getHospitalRoundLeft() const { return hospitalRoundLeft; }
    std::cout << "剩餘住院回合：" << player2->getHospitalRoundLeft() << std::endl;
    std::cout << "剩餘住院回合：" << player1->getHospitalRoundLeft() << std::endl;

    return 0;
    // try {
    //     GameMode mode = GameMode::DUEL;
    //     GameConfig::getInstance().setMode(mode);
    //     ios::sync_with_stdio(false);
    //     cin.tie(nullptr);

    //     // Game game(GameConfig::getInstance());
    //     std::shared_ptr<Game> game = Game::getInstance(GameConfig::getInstance());
    //     game->initGame();
    //     game->start();

    //     // End of the game
    //     SingletonManager::destroyAll(); // Destroy all singleton instances
    // } catch (NotImplement& e) {
    //     std::cout << e.what() << '\n';
    // }
    // return 0;
}
