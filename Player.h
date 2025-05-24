/**
 * @brief 代表一個玩家的類別
 *
 * @details 每個玩家擁有姓名、金錢、土地、卡片等屬性。
 * 玩家會輪流進行遊戲，並根據擲骰子的結果在地圖上移動。
 *
 * @author Tingying Lai
 * @date 2025/05/05
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    /**
     * @brief 建構子，創建一個玩家並設置初始金額
     *
     * @param name 玩家名稱
     * @param startingMoney 初始金額（預設為 1500）
     */
    Player(string name, int startingMoney = 1500);

    /**
     * @brief 調整玩家金錢，正數表示收入，負數表示支出
     *
     * @param amount 調整金額（正數或負數）
     */
    void adjustMoney(int amount);

    bool hasWon(int winAmount) const;

    /**
     * @brief 顯示玩家的基本資訊（名稱、金錢、擁有的土地等)
     */
    void displayPlayerStatus() const;

    int getMoney() const;
    std::string getName() const;

private:
    string name; ///< 玩家名稱
    int money;        ///< 玩家目前金錢
};

#endif // PLAYER_H
