#ifndef CARDPOOL_H
#define CARDPOOL_H

#include <unordered_map>
#include <iostream>

class CardPool {
public:
    CardPool();
    CardPool(const std::unordered_map<int, int>& initialCards);
    ~CardPool();
    
    void resetPool();
    bool updatePool(int level, int change);
    void displayPool() const;

private:
std::unordered_map<int, int> cards;    // Key: Level, Value: Count
std::unordered_map<int, int> initialCards; // Key: Level, Value: Count
};

#endif // CARDPOOL_H