#ifndef BOARD_HPP
#define BOARD_HPP

#include "Error.hpp"
#include "GameConfig.hpp"
#include "Tiles/Tile.hpp"
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

class PropertyTile;
class Board {
private:
    static Board* instance;
    Board(const GameConfig& config);
    ~Board() = default;

    std::vector<std::shared_ptr<Player>> playersList;
    std::map<std::shared_ptr<Player>, int> playersPosition;
    int mapSize = 0;
    size_t tileWidth = 0;
    bool animation = true;
    bool animationDone = false;
    int animationTime = 0;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::vector<std::string>> board;
    std::vector<std::vector<std::string>> playerBoard;
    std::vector<std::vector<int>> propertyLevelBoard;
    std::vector<std::string> propertyLevelIcons;
    void updatePlayerPositions(const std::vector<std::shared_ptr<Player>>& players);
    void updateProperty(const std::vector<std::shared_ptr<Player>>& players);

public:
    static Board* getInstance(const GameConfig& config);
    static Board* getInstance();
    static void destroyInstance();
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    /**
     * @brief Initialize the board and tiles with given config and players.
     */
    void init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players, std::shared_ptr<MiniGameManager> miniGameManager);
    /**
     * @return Total number of tiles on the board.
     */
    int getSize() const;
    /**
     * @brief Get the Tile at the specified index on the board.
     * This function retrieves the tile at the given position on the game board.
     * @param index The tile index (��m).
     * @return Shared pointer to the Tile at that position.
     * @throws std::out_of_range if the index is invalid.
     */
    std::shared_ptr<Tile> getTile(int index);
    std::vector<std::shared_ptr<Tile>> getTileList();
    /**
     * @brief Draw the game board in ASCII art to console.
     */
    void drawBoard();
    void movePlayerStepByStep(std::shared_ptr<Player> player, int steps);
    void drawMonopolyAscii();
    void printTile(int index);

    std::vector<std::shared_ptr<PropertyTile>> getPlayerProperty(const std::shared_ptr<Player>& player);
    static void clearScreen();
};

#endif // BOARD_HPP