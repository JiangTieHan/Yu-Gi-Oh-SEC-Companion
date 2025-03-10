#include "CardPool.h"
#include <iostream>

CardPool::CardPool(const std::string& name)
: _cards()
, _startingPool()
, _allLevels()
, _levelsWithMultipleCopies()
, _poolName(name) 
{}

CardPool::CardPool(const std::string& name, const std::map<int, int> &cardPool)
: _cards(cardPool)
, _startingPool(cardPool)
, _allLevels()
, _levelsWithMultipleCopies()
, _poolName(name)
{
    initializeLevels();
}

void CardPool::resetPool() noexcept
{
    _cards = _startingPool;
    initializeLevels();
}

bool CardPool::updatePool(int level, int change)
{
    if (change == 0) {
        return true;
    }

    auto it = _cards.find(level);
    if (it == _cards.end()) {
        if (change > 0) {
            _cards[level] = change;
            _allLevels.insert(level);
            if (change >= 2) {
                _levelsWithMultipleCopies.insert(level);
            }
            return true;
        }
        return false;
    }

    if (change < 0 && it->second < -change) { // Not enough _cards to remove
        return false;
    }

    it->second += change;
    if (it->second < 2) {
        _levelsWithMultipleCopies.erase(level);
    }
    if (it->second == 0) {
        _cards.erase(it);
        _allLevels.erase(level);
    }

    return true;
}

void CardPool::initializeLevels()
{
    _allLevels.clear();
    _levelsWithMultipleCopies.clear();
    for(auto it = _cards.cbegin(); it != _cards.cend(); it++) {
        _allLevels.insert(it->first);
        if (it->second >= 2) {
            _levelsWithMultipleCopies.insert(it->first);
        }
    }
}

void CardPool::displayPool() const
{
    if (_cards.empty()) {
        std::cout << _poolName << ": Card pool is empty.\n";
        return;
    }
    
    std::cout << _poolName << ": ";
    for (const auto& entry : _cards) {
        std::cout << "(" << entry.first << " * " << entry.second << ") ";
    }

    std::cout << std::endl;
}