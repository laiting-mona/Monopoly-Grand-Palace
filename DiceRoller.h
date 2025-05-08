/**
 * @brief ������l�Y�X�ʧ@�����O
 *
 * @details �C���Y��|�Y�X����������A�æ^�Ǩ�����l���`�M�C
 *
 * @author Tingying Lai
 * @date 2025/05/05
 */
#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

#include <random>
using namespace std;

class DiceRoller {
public:
    /**
     * @brief �غc�l�A�]�w�H���ƥͦ���
     */
    DiceRoller();

    /**
     * @brief �Y�X������l�A�æ^���`�M
     *
     * @return ������l���`�M
     */
    int roll();

private:
    default_random_engine generator; ///< �H���ƥͦ���
    uniform_int_distribution<int> distribution; ///< ���ͻ�l���H���ơ]1��6�^
};

#endif // DICE_ROLLER_H