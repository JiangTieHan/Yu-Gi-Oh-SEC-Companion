#ifndef CARDPOOL_H
#define CARDPOOL_H

#include <map>
#include <iostream>

class CardPool {
public:
    CardPool();
    CardPool(const std::map<int, int>& cardPool);
    ~CardPool() = default;
    
    void resetPool() noexcept;
    bool updatePool(int level, int change);
    void displayPool() const;

private:
std::map<int, int> cards;    // Key: Level, Value: Count
std::map<int, int> startingPool; // Key: Level, Value: Count
};

#endif // CARDPOOL_H