/**
 * @brief �N��@�ӹC�������a��C
 *
 * @details �C�Ӧa�榳�W�ٻP�����A�i�H�O���q��B�ƥ��B�Ϊ��ݩʮ�C
 * ���a���o�Ǯ�l�ɡA�|Ĳ�o���P����ʡC
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
     * @brief �غc�l�A��l�Ʀa��W�ٻP����
     *
     * @param name �a��W��
     * @param type �a������
     */
    Tile(string name, string type);

    /**
     * @brief ��ܦa���T
     */
    void displayTileInfo() const;

private:
    string name; ///< �a��W��
    string type; ///< �a�������]�p�G���q��B�ƥ��B�ݩʮ�^
};

#endif // TILE_H