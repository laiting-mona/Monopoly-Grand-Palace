#include "Board.h"
#include "Player.h"
#include "DiceRoller.h"
#include "Tile.h"
#include <iostream>

using namespace std;

int main() {
    // 測試 Board 類別
    Board board(8); // 創建一個 8x8 的遊戲地圖
    cout << "----- Displaying Board -----" << endl;
    board.displayBoard(); // 顯示遊戲地圖

    // 測試 Player 類別
    Player player("Tingying", 1500); // 創建一個名為 Tingying 的玩家，初始金額 1500
    cout << "\n----- Player Status -----" << endl;
    player.displayPlayerStatus(); // 顯示玩家資訊

    // 測試 Player 調整金錢
    player.adjustMoney(-500); // 玩家支出 500
    cout << "\n----- Player Status after spending 500 -----" << endl;
    player.displayPlayerStatus(); // 顯示更新後的玩家資訊

    player.adjustMoney(300); // 玩家收入 300
    cout << "\n----- Player Status after earning 300 -----" << endl;
    player.displayPlayerStatus(); // 顯示更新後的玩家資訊

    // 測試 DiceRoller 類別
    DiceRoller dice;
    int rollResult = dice.roll(); // 擲骰子
    cout << "\n----- Dice Roll Result -----" << endl;
    cout << "Roll result: " << rollResult << endl; // 顯示擲骰結果

    // 測試 Tile 類別
    Tile tile("Go", "Event"); // 創建一個名為 "Go" 的事件格子
    cout << "\n----- Tile Info -----" << endl;
    tile.displayTileInfo(); // 顯示地格資訊

    return 0;
}