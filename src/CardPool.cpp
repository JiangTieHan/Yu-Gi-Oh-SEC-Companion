#include "CardPool.h"
#include <iostream>

CardPool::CardPool(): _cards(), _startingPool() {
}

CardPool::CardPool(const std::map<int, int> &cardPool): _cards(cardPool), _startingPool(cardPool)
{
}

void CardPool::resetPool() noexcept
{
    _cards = _startingPool;
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
            return true;
        }
        return false;
    }

    if (change < 0 && it->second < -change) { // Not enough _cards to remove
        return false;
    }

    it->second += change;
    if (it->second == 0) {
        _cards.erase(it);
    }

    return true;
}

void CardPool::displayPool() const
{
    if (_cards.empty()) {
        std::cout << "Card pool is empty.";
        return;
    }
    
    for (const auto& entry : _cards) {
        std::cout << "(" << entry.first << " * " << entry.second << ") ";
    }

    std::cout << std::endl;
}