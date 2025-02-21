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
    void displayPool() const;
    bool updatePool(int level, int change);
    inline bool isPoolEmpty() const { return cards.empty(); }


private:
std::map<int, int> cards;    // Key: Level, Value: Count
std::map<int, int> startingPool; // Key: Level, Value: Count
};

#endif // CARDPOOL_H