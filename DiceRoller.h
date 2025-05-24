/**
 * @brief 模擬骰子擲出動作的類別
 *
 * @details 每次擲骰會擲出兩顆六面骰，並回傳兩顆骰子的總和。
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
     * @brief 建構子，設定隨機數生成器
     */
    DiceRoller();

    /**
     * @brief 擲出兩顆骰子，並回傳總和
     *
     * @return 兩顆骰子的總和
     */
    int roll();

private:
    default_random_engine generator; ///< 隨機數生成器
    uniform_int_distribution<int> distribution; ///< 產生骰子的隨機數（1到6）
};

#endif // DICE_ROLLER_H