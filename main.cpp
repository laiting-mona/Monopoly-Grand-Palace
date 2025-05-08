#include "Board.h"
#include "Player.h"
#include "DiceRoller.h"
#include "Tile.h"
#include <iostream>

using namespace std;

int main() {
    // ���� Board ���O
    Board board(8); // �Ыؤ@�� 8x8 ���C���a��
    cout << "----- Displaying Board -----" << endl;
    board.displayBoard(); // ��ܹC���a��

    // ���� Player ���O
    Player player("Tingying", 1500); // �Ыؤ@�ӦW�� Tingying �����a�A��l���B 1500
    cout << "\n----- Player Status -----" << endl;
    player.displayPlayerStatus(); // ��ܪ��a��T

    // ���� Player �վ����
    player.adjustMoney(-500); // ���a��X 500
    cout << "\n----- Player Status after spending 500 -----" << endl;
    player.displayPlayerStatus(); // ��ܧ�s�᪺���a��T

    player.adjustMoney(300); // ���a���J 300
    cout << "\n----- Player Status after earning 300 -----" << endl;
    player.displayPlayerStatus(); // ��ܧ�s�᪺���a��T

    // ���� DiceRoller ���O
    DiceRoller dice;
    int rollResult = dice.roll(); // �Y��l
    cout << "\n----- Dice Roll Result -----" << endl;
    cout << "Roll result: " << rollResult << endl; // ����Y�뵲�G

    // ���� Tile ���O
    Tile tile("Go", "Event"); // �Ыؤ@�ӦW�� "Go" ���ƥ��l
    cout << "\n----- Tile Info -----" << endl;
    tile.displayTileInfo(); // ��ܦa���T

    return 0;
}