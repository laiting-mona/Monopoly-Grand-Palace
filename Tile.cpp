#include "Tile.h"
#include <iostream>

using namespace std;

/**
 * @brief �غc�l�A��l�Ʀa��W�ٻP����
 *
 * @param name �a��W��
 * @param type �a������
 */
Tile::Tile(string name, string type) : name(name), type(type) {}

/**
 * @brief ��ܦa���T
 */
void Tile::displayTileInfo() const {
    cout << "Tile: " << name << " | Type: " << type << endl;
}