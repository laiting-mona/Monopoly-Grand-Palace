/**
 * @file SingletonManager.cpp
 * @brief SingletonManager 類別的實作檔案。
 */

#include "SingletonManager.hpp"

using namespace std;

vector<function<void()>> SingletonManager::destructors;

void SingletonManager::registerDestructor(function<void()> destructor) {
    destructors.push_back(destructor);
}

void SingletonManager::destroyAll() {
    for (auto& destructor : destructors) {
        destructor();
    }
    destructors.clear();
}