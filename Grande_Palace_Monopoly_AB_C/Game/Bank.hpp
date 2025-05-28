/**
 * @file Bank.hpp
 * @brief Bank 類別，模擬壟斷遊戲中的銀行單例。
 */
#ifndef BANK_HPP
#define BANK_HPP

#include "Game/Player.hpp"
#include <memory>

 /**
  * @brief Singleton Bank class that manages money transfers between players and the bank.
  */
class Bank {
private:
    long long totalMoneyInBank;    ///< Total money reserves in the bank
    static Bank* instance;         ///< Singleton instance of Bank

    /** @brief Private constructor initializes the bank with a large reserve. */
    Bank();

public:
    /**
     * @brief Get the singleton instance of the Bank.
     * @return Pointer to the Bank instance.
     */
    static Bank* getInstance();

    /**
     * @brief Destroy the Bank singleton instance.
     */
    static void destroyInstance();

    /**
     * @brief Pay a certain amount from the bank to a player.
     * @param player The player receiving money.
     * @param amount The amount to pay (must be positive and <= bank reserve).
     * @throws std::invalid_argument if amount <= 0.
     * @throws std::runtime_error if bank has insufficient funds.
     */
    void payToPlayer(std::shared_ptr<Player> player, long long amount);

    /**
     * @brief Receive a certain amount from a player to the bank.
     * @param player The player paying money to the bank.
     * @param amount The amount to receive (must be positive and <= player's money).
     * @throws std::invalid_argument if amount <= 0.
     * @throws std::runtime_error if player has insufficient funds.
     */
    void receiveFromPlayer(std::shared_ptr<Player> player, long long amount);

    /**
     * @brief Get the total money currently held by the bank.
     * @return The bank's current balance.
     */
    long long getTotalMoneyInBank() const;
};

#endif // BANK_HPP