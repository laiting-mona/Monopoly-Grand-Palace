/**
 * @brief 代表一個遊戲中的地格。
 *
 * @details 每個地格有名稱與類型，可以是普通格、事件格、或者屬性格。
 * 當玩家踩到這些格子時，會觸發不同的行動。
 *
 * @author Tingying Lai
 * @date 2025/05/05
 */
#ifndef TILE_H
#define TILE_H

#include <string>
using namespace std;

class Tile {
public:
    /**
     * @brief 建構子，初始化地格名稱與類型
     *
     * @param name 地格名稱
     * @param type 地格類型
     */
    Tile(string name, string type);

    /**
     * @brief 顯示地格資訊
     */
    void displayTileInfo() const;

private:
    string name; ///< 地格名稱
    string type; ///< 地格類型（如：普通格、事件格、屬性格）
};

#endif // TILE_H