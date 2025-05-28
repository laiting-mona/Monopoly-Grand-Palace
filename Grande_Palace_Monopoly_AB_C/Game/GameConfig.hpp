/**
 * @file GameConfig.hpp
 * @brief GameConfig ���O�A�޲z�C���]�w��������O�C
 */
#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include "Error.hpp"
#include <map>
#include <string>
#include <vector>

 /** @brief Enumeration of game modes. */
enum class GameMode { DEBUG, DUEL, RELEASE, CUSTOM };

/** @brief Configuration data for a board tile. */
struct TileConfig {
    std::size_t id;
    std::string type;
    std::string name;
    int cost;
    int rent;
};

/** @brief Configuration data for a card. */
struct CardConfig {
    std::string name;
    std::string icon;
    int price;
    std::string effect;
};

/**
 * @brief Singleton configuration class for the game settings.
 */
class GameConfig {
private:
    static GameConfig instance;
    GameMode mode = GameMode::DEBUG;
    int playersNum = 2;
    int startMoney = 0;
    int winMoney = 0;
    int passingStartBonus = 0;
    int mapSize = 8;
    size_t tileWidth = 14;
    long long animationTime = 0;
    bool animation = true;
    std::vector<std::string> playersName;
    std::vector<std::string> playerIcons;
    std::vector<std::string> playerColors;
    std::vector<TileConfig> boardTiles;
    std::vector<CardConfig> cards;
    std::vector<std::string> propertyLevelIcons;
    std::map<int, std::string> locationMap;
    std::map<std::string, std::pair<int, int>> eventValueRange;

    /** @brief Private constructor for singleton pattern. */
    GameConfig() = default;

public:
    /**
     * @brief Get the GameConfig singleton instance.
     * @return Reference to the GameConfig instance.
     */
    static GameConfig& getInstance();

    /** @brief Set the game mode. */
    void setMode(GameMode newMode);
    /** @brief Get the current game mode. */
    GameMode getMode() const;

    /** @brief Set the number of players. */
    void setPlayersNum(int num);
    /** @brief Get the number of players. */
    int getPlayersNum() const;

    /** @brief Set player names. */
    void setPlayersName(const std::vector<std::string>& names);
    /** @brief Get the list of player names. */
    std::vector<std::string> getPlayerNames() const;

    /** @brief Set player icon identifiers. */
    void setPlayerIcons(const std::vector<std::string>& icons);
    /** @brief Get the list of player icon identifiers. */
    std::vector<std::string> getPlayerIcons() const;

    /** @brief Set player color identifiers. */
    void setPlayerColors(const std::vector<std::string>& colors);
    /** @brief Get the list of player color identifiers. */
    std::vector<std::string> getPlayerColors() const;

    /** @brief Set the icons used for property level display. */
    void setPropertyLevelIcons(const std::vector<std::string>& icons);
    /** @brief Get the list of property level icons. */
    std::vector<std::string> getPropertyLevelIcons() const;

    /** @brief Get the mapping of board location indices to names. */
    std::map<int, std::string> getLocationMap() const;

    /** @brief Set the starting money for each player. */
    void setStartMoney(int amount);
    /** @brief Get the starting money amount. */
    int getStartMoney() const;

    /** @brief Set the winning money threshold. */
    void setWinMoney(int amount);
    /** @brief Get the money amount needed to win. */
    int getWinMoney() const;

    /** @brief Set the bonus given for passing the Start tile. */
    void setPassingStartBonus(int amount);
    /** @brief Get the bonus amount for passing Start. */
    int getPassingStartBonus() const;

    /** @brief Set the configuration of board tiles. */
    void setBoardTiles(const std::vector<TileConfig>& tiles);
    /** @brief Get the configuration list of board tiles. */
    std::vector<TileConfig> getBoardTiles() const;

    /** @brief Set the configuration of cards available in game. */
    void setCards(const std::vector<CardConfig>& cards);
    /** @brief Get the configuration list of cards. */
    std::vector<CardConfig> getCards() const;

    /** @brief Set the min/max value range for special event outcomes. */
    void setEventValueRange(const std::map<std::string, std::pair<int, int>>& range);
    /** @brief Get the configured event value ranges. */
    std::map<std::string, std::pair<int, int>> getEventValueRange() const;

    /** @brief Enable or disable animations in the game. */
    void setAnimation(bool status);
    /** @brief Check if animations are enabled. */
    bool getAnimation() const;

    /** @brief Get the size of the board (number of tiles). */
    int getMapSize() const;

    /** @brief Get the display width of each tile (for UI layout). */
    int getTileWidth() const;

    /** @brief Get the configured animation delay time. */
    long long getAnimationTime() const;

    /** @brief Load configuration from external source (file, etc.). */
    void loadConfig();
};

#endif // GAMECONFIG_HPP