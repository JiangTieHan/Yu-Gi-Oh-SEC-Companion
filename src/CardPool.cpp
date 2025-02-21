#include "CardPool.h"
#include <iostream>

CardPool::CardPool(): cards(), startingPool() {
}

CardPool::CardPool(const std::map<int, int> &cardPool): cards(cardPool), startingPool(cardPool)
{
}

void CardPool::resetPool() noexcept
{
    cards = startingPool;
}

bool CardPool::updatePool(int level, int change)
{
    if (change == 0) {
        return true;
    }

    auto it = cards.find(level);
    if (it == cards.end()) {
        if (change > 0) {
            cards[level] = change;
            return true;
        }
        return false;
    }

    if (change < 0 && it->second < -change) { // Not enough cards to remove
        return false;
    }

    it->second += change;
    if (it->second == 0) {
        cards.erase(it);
    }

    return true;
}

void CardPool::displayPool() const
{
    if (cards.empty()) {
        std::cout << "Card pool is empty.";
        return;
    }
    
    for (const auto& entry : cards) {
        std::cout << "(" << entry.first << " * " << entry.second << ") ";
    }

    std::cout << std::endl;
}