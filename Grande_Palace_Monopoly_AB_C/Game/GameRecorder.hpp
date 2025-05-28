/**
 * @file GameRecorder.hpp
 * @brief �j�I�ιC�����C���O���Ҳ�
 * @date 2025-05-17
 * ���ɮ׫ŧi GameRecorder ���O�A�Ω�C�^�X�ƥ��C�����A�B��ʦs�ɻPŪ�ɡA
 * �ðO������C�����欰��x�H�䴩�^��Ҧ��C
 * @details �Цb Game ���O���[�J `friend class GameRecorder;`
 * �H�K GameRecorder �s���C���p�����A�]�Ҧp���a�C��^�i��s�ɻP�^��C
 */
#ifndef GAMERECORDER_HPP
#define GAMERECORDER_HPP

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

 // �e�m�ŧi�H�קK�`���]�t
class Game;
class Player;
class PropertyTile;

class GameRecorder {
public:
    /** �C�^�X�۰ʳƥ��C�����A�� JSON �ɮס]�`���O�s�̦h MAX_SAVES ���^ */
    static void autoSave(Game* game);

    /** �b�C����椤�Ѫ��a���Ĳ�o���s�ɥ\�� */
    static void manualSave(Game* game);

    /** ���J�̪񪺦s���ɮסA�N�C�����A��_�ܦs�ɮɪ����p */
    static bool loadRecent(Game* game);

    /** ��l�Ʀ欰�O���]�b�C���}�l�ɩI�s�H�M�ť��e�����^ */
    static void startLogging();

    /** �N�ثe�ֿn���欰�����g�X�� log.json�]�b�C�������ɩI�s�^ */
    static void saveLog();

    /** �O���Y��ʧ@ */
    static void recordDiceRoll(const Player* player, int diceTotal);

    /** �O�����a���ʰʧ@ */
    static void recordMove(const Player* player, int fromPos, int toPos);

    /** �O���ʶR�a���ʧ@ */
    static void recordBuyProperty(const Player* player, const PropertyTile* property, int price);

    /** �O���ɯŦa���ʧ@ */
    static void recordUpgradeProperty(const Player* player, const PropertyTile* property, int cost);

    /** �O���X��a���ʧ@ */
    static void recordSellProperty(const Player* player, const PropertyTile* property, int sellPrice);

    /** �O����I�L���O�]�����^�ʧ@ */
    static void recordPayRent(const Player* payer, const Player* owner, int amount);

    /** �O���ϥΥd���ʧ@�]targetName �i���ؼЪ��a�W�٩Ψ�L�ؼдy�z�^ */
    static void recordCardUse(const Player* player, const std::string& cardName, const std::string& targetName = "");

    /** �Ұʦ^��Ҧ��GŪ�� log.json �ȩ̀Ǽ����C���L�{ */
    static void replay(Game* game);

private:
    static constexpr int MAX_SAVES = 3;        ///< �̤j�s�ɼƶq�]�`���ϥΡ^
    static int currentSaveSlot;               ///< �̪�@���ϥΪ��s�ɽs���]1~MAX_SAVES�^
    static int currentTurnNumber;             ///< ��e�^�X�s���]�C�쪱�a��ʤ@����@�^�X���W�^
    static nlohmann::json logEntries;         ///< �ֿn���C���欰�����]JSON �}�C�^

    /** �O���s�^�X���}�l�]�^�X�p�� +1�^�C����C�쪱�a��ʶ}�l�ɩI�s�C */
    static void newTurn();
};

#endif // GAMERECORDER_HPP