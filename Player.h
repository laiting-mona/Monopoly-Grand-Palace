/**
 * @brief �N��@�Ӫ��a�����O
 *
 * @details �C�Ӫ��a�֦��m�W�B�����B�g�a�B�d�����ݩʡC
 * ���a�|���y�i��C���A�îھ��Y��l�����G�b�a�ϤW���ʡC
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
     * @brief �غc�l�A�Ыؤ@�Ӫ��a�ó]�m��l���B
     *
     * @param name ���a�W��
     * @param startingMoney ��l���B�]�w�]�� 1500�^
     */
    Player(string name, int startingMoney = 1500);

    /**
     * @brief �վ㪱�a�����A���ƪ�ܦ��J�A�t�ƪ�ܤ�X
     *
     * @param amount �վ���B�]���Ʃέt�ơ^
     */
    void adjustMoney(int amount);

    /**
     * @brief ��ܪ��a���򥻸�T�]�W�١B�����B�֦����g�a���^
     */
    void displayPlayerStatus() const;

private:
    string name; ///< ���a�W��
    int money;        ///< ���a�ثe����
};

#endif // PLAYER_H