#include "CardPool.h"

CardPool::CardPool(): cards(), initialCards() {
}

CardPool::CardPool(const std::unordered_map<int, int> &initialCards): cards(initialCards), initialCards(initialCards)
{
}

CardPool::~CardPool()
{
}

void CardPool::resetPool()
{
    cards = initialCards;
}

bool CardPool::updatePool(int level, int change)
{
    if (change == 0) {
        return true;
      }
  
    // If level does not exist, create an entry (optional)
    if (cards.find(level) == cards.end() && change > 0) {
        cards[level] = change;
        return true;
    }
    else if (cards.find(level) == cards.end() && change < 0) {
        return false;
    }

    if (change < 0 && cards[level] < -change) {
        return false;
    }
    else {
        cards[level] += change;
    }

    if (cards[level] == 0) {
        cards.erase(level);
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
        std::cout << entry.first << " * " << entry.second;
    }
}