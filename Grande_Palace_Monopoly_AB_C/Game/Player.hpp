#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <string>
#include <vector>

class Card;
class MiniGameManager;
class PropertyTile;

class Player : public std::enable_shared_from_this<Player> {
private:
    std::string name;
    std::string icon;
    std::string color;
    int position;
    long long money;
    std::vector<std::shared_ptr<Card>> cards; // Cards held by the player
    bool bankrupt;                            // Whether the player is bankrupt
    bool inHospital;                          // Whether the player is in the hospital
    bool isMyTurn;                            // Whether it is the player's turn
    int hospitalRoundLeft;                    // Number of rounds left in the hospital
    int diceControl;
    int hospitalReturnPos;               // Position to return to after hospital
    std::vector<std::shared_ptr<PropertyTile>> properties;

public:
    Player(const std::string& n, const std::string& i, const std::string& c, long long m);
    virtual ~Player() = default;


    // Accessors
    /**
     * @return Current money the player holds.
     */
    std::string getName() const;
    std::string getIcon() const;
    std::string getColor() const;
    std::string getIconWithColor() const;
    std::string getDisplayName() const;
    void displayInfo() const;

    long long getMoney() const;
    int getPosition() const;
    /**
     * @brief Get the predetermined dice value for the next roll (if set).
     * @return The dice value to use for the next roll, or 0 if no control is set.
     */
    int getDiceControl() const;
    bool isBankrupt() const;
    bool isInHospital() const;
    bool checkIsMyTurn() const;

    // Update Player status
    void setPosition(int pos);
    void setMyTurn(bool b);
    /**
     * @brief Increase player's money.
     * @param amount Amount to add.
     * @return true if operation succeeded.
     */
    bool addMoney(long long amount);
    /**
     * @brief Decrease player's money (for payments).
     * @param amount Amount to deduct.
     * @return true if player had enough money, false if went bankrupt.
     */
    bool deductMoney(long long amount);
    void setBankrupt(bool b);
    void addCard(std::shared_ptr<Card> card); // ---------------A---------------
    /**
     * @brief Set a predetermined dice roll value for the player's next turn.
     * @param step The desired dice outcome (1-6).
     */
    void setDiceControl(int step);
    /**
     * @brief Move the player to the start position.
     */
    void sendToStart();

    // Hospital related
    /**
     * @brief Send the player to hospital for given rounds.
     */
    void sendToHospital(int rounds);
    /**
     * @brief Recover the player from hospital (set status to not in hospital).
     */
    void recoverFromHospital();
    /**
     * @brief Update hospital status at end of turn (decrease remaining rounds).
     */
    void updateHospitalStatus();
    int getHospitalRoundLeft() const { return hospitalRoundLeft; }

    /**
     * @brief Get a list of all Cards currently held by the player.
     * @return A vector of shared pointers to Card objects.
     */
    std::vector<std::shared_ptr<Card>> getCards();
    /**
     * @brief Display all cards the player holds, with details.
     * @param players Reference to all players (for context if needed).
     */
    void displayCards(std::vector<std::shared_ptr<Player>>& players);
    /**
     * @brief Use a card from the player's inventory by index.
     * @param index Index of the card in the inventory to use.
     * @param players Reference to all players (to provide context to the card effect).
     */
    void useCard(int index, std::vector<std::shared_ptr<Player>>& players);
    int rollDice();

    void addProperty(std::shared_ptr<PropertyTile> property);
    void removeProperty(std::shared_ptr<PropertyTile> property);
    std::vector<std::shared_ptr<PropertyTile>> getProperties() const;
};

#endif // PLAYER_HPP