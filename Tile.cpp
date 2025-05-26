#include "Tile.h"
#include <iostream>

using namespace std;

/**
 * @brief 建構子，初始化地格名稱與類型
 *
 * @param name 地格名稱
 * @param type 地格類型
 */
Tile::Tile(string name, string type) : name(name), type(type) {}

/**
 * @brief 顯示地格資訊
 */
void Tile::displayTileInfo() const {
    cout << "Tile: " << name << " | Type: " << type << endl;
}