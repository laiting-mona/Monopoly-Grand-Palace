/**
 * @file GameRecorder.hpp
 * @brief 大富翁遊戲的遊戲記錄模組
 * @date 2025-05-17
 * 此檔案宣告 GameRecorder 類別，用於每回合備份遊戲狀態、手動存檔與讀檔，
 * 並記錄整場遊戲的行為日誌以支援回放模式。
 * @details 請在 Game 類別中加入 `friend class GameRecorder;`
 * 以便 GameRecorder 存取遊戲私有狀態（例如玩家列表）進行存檔與回放。
 */
#ifndef GAMERECORDER_HPP
#define GAMERECORDER_HPP

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

 // 前置宣告以避免循環包含
class Game;
class Player;
class PropertyTile;

class GameRecorder {
public:
    /** 每回合自動備份遊戲狀態到 JSON 檔案（循環保存最多 MAX_SAVES 份） */
    static void autoSave(Game* game);

    /** 在遊戲選單中由玩家手動觸發的存檔功能 */
    static void manualSave(Game* game);

    /** 載入最近的存檔檔案，將遊戲狀態恢復至存檔時的情況 */
    static bool loadRecent(Game* game);

    /** 初始化行為記錄（在遊戲開始時呼叫以清空先前紀錄） */
    static void startLogging();

    /** 將目前累積的行為紀錄寫出到 log.json（在遊戲結束時呼叫） */
    static void saveLog();

    /** 記錄擲骰動作 */
    static void recordDiceRoll(const Player* player, int diceTotal);

    /** 記錄玩家移動動作 */
    static void recordMove(const Player* player, int fromPos, int toPos);

    /** 記錄購買地產動作 */
    static void recordBuyProperty(const Player* player, const PropertyTile* property, int price);

    /** 記錄升級地產動作 */
    static void recordUpgradeProperty(const Player* player, const PropertyTile* property, int cost);

    /** 記錄出售地產動作 */
    static void recordSellProperty(const Player* player, const PropertyTile* property, int sellPrice);

    /** 記錄支付過路費（租金）動作 */
    static void recordPayRent(const Player* payer, const Player* owner, int amount);

    /** 記錄使用卡片動作（targetName 可為目標玩家名稱或其他目標描述） */
    static void recordCardUse(const Player* player, const std::string& cardName, const std::string& targetName = "");

    /** 啟動回放模式：讀取 log.json 並依序模擬遊戲過程 */
    static void replay(Game* game);

private:
    static constexpr int MAX_SAVES = 3;        ///< 最大存檔數量（循環使用）
    static int currentSaveSlot;               ///< 最近一次使用的存檔編號（1~MAX_SAVES）
    static int currentTurnNumber;             ///< 當前回合編號（每位玩家行動一次算一回合遞增）
    static nlohmann::json logEntries;         ///< 累積的遊戲行為紀錄（JSON 陣列）

    /** 記錄新回合的開始（回合計數 +1）。應於每位玩家行動開始時呼叫。 */
    static void newTurn();
};

#endif // GAMERECORDER_HPP