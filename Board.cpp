#include "Board.h"

/**
 * @brief 建構子，初始化遊戲地圖的地格。
 * 預設初始化為空地格。
 *
 * @param size 地圖的尺寸
 */
Board::Board(int size) : size(size) {
    tiles.resize(size * size, "Empty"); // 預設所有地格為空地
}

/**
 * @brief 顯示當前的遊戲地圖，將每個地格名稱印出來
 */
void Board::displayBoard() {
    cout << "Displaying the Board:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << tiles[i * size + j] << "\t";
        }
        cout << endl;
    }
}