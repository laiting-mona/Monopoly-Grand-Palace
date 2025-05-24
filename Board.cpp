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

int Board::movePosition(int currentPos, int steps) const {
    int totalTiles = size * size;                // 地圖上總格數
    int newPos = currentPos + steps;             // 計算前進後的位置
    // 環繞前進：如果 newPos 超過地圖最後，就從頭開始
    if (newPos >= totalTiles) {
        newPos %= totalTiles;
    }
    
    // 如果不想環繞，而是停在邊界，改成：
    if (newPos >= totalTiles) newPos = totalTiles - 1;
    return newPos;
}
