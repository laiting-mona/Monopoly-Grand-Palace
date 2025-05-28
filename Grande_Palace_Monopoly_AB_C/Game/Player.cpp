#include "Player.hpp"
#include "Cards/Card.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "Tiles/PropertyTile.hpp"
#include "Utils.hpp"
#include <iomanip>
#include <iostream>
#include <algorithm> // for std::remove>
#include <limits>

Player::Player(const std::string& n, const std::string& i, const std::string& c, long long m)
    : name(n)
    , icon(i)
    , color(c)
    , position(0)
    , money(m)
    , bankrupt(false)
    , inHospital(false)
    , isMyTurn(false)
    , hospitalRoundLeft(0)
    , diceControl(0) {
}

std::string Player::getName() const { return name; }
std::string Player::getIcon() const { return icon; }
std::string Player::getColor() const { return color; }

std::string Player::getIconWithColor() const {
    return color + icon + "\033[0m";
}

std::string Player::getDisplayName() const {
    return getIconWithColor() + " " + getName();
}

long long Player::getMoney() const { return money; }
int Player::getPosition() const { return position; }
bool Player::isBankrupt() const { return bankrupt; }
bool Player::isInHospital() const { return inHospital; }
bool Player::checkIsMyTurn() const { return isMyTurn; }

void Player::displayInfo() const {
    std::cout << "=== Player Info ===" << std::endl;
    std::cout << "Name: " << getDisplayName() << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Card Count: " << cards.size() << std::endl;
    if (!cards.empty()) {
        std::cout << "Card List: " << std::endl;
        for (size_t i = 0; i < cards.size(); ++i) {
            std::cout << "  [" << i + 1 << "] " << cards[i]->getName() 
                      << " - " << cards[i]->getEffect() << std::endl;
        }
    }

    std::cout << "Property Count: " << properties.size() << std::endl;
    if (!properties.empty()) {
        std::cout << "Property List: " << std::endl;
        for (const auto& prop : properties) {
            std::cout << "  - " << prop->getName() 
                      << " (Lv" << static_cast<int>(prop->getPropertyLevel()) << ")" << std::endl;
        }
    }

    std::cout << "=================" << std::endl;
    waitForKey();
}

void Player::setPosition(int pos) { position = pos; }
void Player::setMyTurn(bool b) { isMyTurn = b; }

bool Player::addMoney(long long amount) {
    if (amount < 0) return false;
    money += amount;
    return true;
}

bool Player::deductMoney(long long amount) {
    if (amount <= 0) return true;
    if (money < amount) {
        // Player cannot pay full amount -> bankrupt
        amount = money;
        money = 0;
        bankrupt = true;
        std::cout << getName() << " is bankrupt!" << std::endl;
        delayMilliseconds(1200);
        return false;
    }
    money -= amount;
    return true;
}

void Player::setBankrupt(bool b) {
    bankrupt = b;
}

void Player::sendToStart() {
    position = 0;
    std::cout << getDisplayName() << " has been sent to Start." << std::endl;
    delayMilliseconds(1200);
}

void Player::sendToHospital(int rounds) {
    inHospital = true;
    hospitalRoundLeft = rounds;
    hospitalReturnPos = position; // Save current position to return after hospital
    position = 15; // hospital is at position 15
    std::cout << getDisplayName() << " has been sent to Hospital for " << rounds << " turns." << std::endl;
    delayMilliseconds(1200);
}

void Player::recoverFromHospital() {
    inHospital = false;
    hospitalRoundLeft = 0;
    position = hospitalReturnPos; // Return to the position before going to hospital
    std::cout << getDisplayName() << " has recovered from Hospital." << std::endl;
    delayMilliseconds(1200);
}

void Player::updateHospitalStatus() {
    if (inHospital && hospitalRoundLeft > 0) {
        hospitalRoundLeft--;
        if (hospitalRoundLeft <= 0) {
            recoverFromHospital();
        }
    }
}

void Player::addCard(std::shared_ptr<Card> card) {
    if (card) {
        cards.push_back(card);
    }
}

std::vector<std::shared_ptr<Card>> Player::getCards() { return cards; }

void Player::displayCards(std::vector<std::shared_ptr<Player>>& players) {
    if (cards.empty()) {
        std::cout << getDisplayName() << " has no cards." << std::endl;
        delayMilliseconds(1200);
        return;
    }
    else {
        std::cout << getDisplayName() << " has the following cards:" << std::endl;
        for (size_t i = 0; i < cards.size(); ++i) {
            std::cout << i + 1 << ". [" << cards[i]->getName() << "] - Effect: "
                << cards[i]->getEffect() << std::endl;
        }
        delayMilliseconds(1200);
    }
}

void Player::useCard(int index, std::vector<std::shared_ptr<Player>>& players) {
    if (index < 0 || index >= (int)cards.size()) {
        std::cout << "Invalid card index." << std::endl;
        delayMilliseconds(1200);
        return;
    }
    // Use the selected card
    std::shared_ptr<Card> card = cards[index];
    card->useEffect(players, shared_from_this());
    // Remove the card after use
    cards.erase(cards.begin() + index);
}

void Player::setDiceControl(int step) {
    if (step >= 1 && step <= 12) { 
        diceControl = step;
    }
    else{
        std::cout << "Invalid dice control value. Must be between 1 and 12." << std::endl;
        diceControl = 0; // Reset to no control
    }
}

int Player::getDiceControl() const {
    return diceControl;
}

int Player::rollDice() {
    if (diceControl > 0) {
        int result = diceControl;
        diceControl = 0; 
        return result;
    }

    int dice1 = 1 + rand() % 6;
    int dice2 = 1 + rand() % 6;
    int total = dice1 + dice2;
    return total;
}

void Player::addProperty(std::shared_ptr<PropertyTile> property) {
    if (property) {
        properties.push_back(property);
    }
}

void Player::removeProperty(std::shared_ptr<PropertyTile> property) {
    if (property) {
        properties.erase(
            std::remove(properties.begin(), properties.end(), property),
            properties.end()
        );
    }
}

std::vector<std::shared_ptr<PropertyTile>> Player::getProperties() const {
    return properties;
}