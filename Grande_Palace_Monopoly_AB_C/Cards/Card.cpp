/**
 * @file Card.cpp
 * @brief Card 類別的實作檔案。
 */

#include "Card.hpp"

using namespace std;

Card::Card(const string& n, const string& i, int p, const string& e)
    : name(n), icon(i), price(p), effect(e) {
}

Card::~Card() = default;

string Card::getName() const {
    return name;
}

string Card::getIcon() const {
    return icon;
}

int Card::getPrice() const {
    return price;
}

string Card::getEffect() const {
    return effect;
}