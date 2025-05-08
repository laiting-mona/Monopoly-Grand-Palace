/**
 * @brief 代表大富翁遊戲的遊戲地圖，採用 8x8 格局。
 *
 * @details 地圖由許多地格組成，每個地格都有不同的功能（例如：屬性、事件等）。
 * 遊戲進行時，玩家根據擲骰子的結果在這些地格間移動，每個地格會有不同的行動觸發。
 *
 * @author Tingying Lai
 * @date 2025/05/05
 */
#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Board {
public:
    /**
     * @brief 建構子，初始化遊戲地圖的地格。
     *
     * @param size 地圖的尺寸（預設為 8x8 格）
     */
    Board(int size = 8);

    /**
     * @brief 顯示遊戲地圖
     */
    void displayBoard();

private:
    int size;                     ///< 地圖大小（預設為 8x8）
    vector<string> tiles; ///< 地圖上每個地格的名稱或類型
};

class Board {
public:
    /**
     * @brief 初始化遊戲地圖與所有地格
     *
     * @param size 地圖大小（預設為 8x8）
     */
    Board(int size = 8);

    /**
     * @brief 顯示整個地圖
     */
    void displayBoard();

private:
    int size;                      ///< 地圖大小（預設為 8x8）
    vector<Tile> tiles;            ///< 遊戲地圖上的所有地格
};

#endif // BOARD_H