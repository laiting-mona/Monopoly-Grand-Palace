#include "DiceRoller.h"

using namespace std;

/**
 * @brief �غc�l�A�]�m�H���ƥͦ���
 */
DiceRoller::DiceRoller() : distribution(1, 6) {}

/**
 * @brief �Y�X������l�A�æ^���`�M
 *
 * @return ������l���`�M
 */
int DiceRoller::roll() {
    return distribution(generator) + distribution(generator); // �Y������l
}