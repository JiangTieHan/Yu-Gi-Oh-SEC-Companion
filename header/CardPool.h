#ifndef CARDPOOL_H
#define CARDPOOL_H

#include <map>
#include <set>
#include <string>

class CardPool {
public:
    CardPool(const std::string& name);
    CardPool(const std::string& name, const std::map<int, int>& cardPool);
    ~CardPool() = default;
    
    void resetPool() noexcept;
    void displayPool() const;
    bool updatePool(int level, int change);
    inline bool isPoolEmpty() const { return _cards.empty(); }
    inline const std::set<int>& getAllLevels() const { return _allLevels; }
    inline const std::set<int>& getLevelsWithMultipleCopies() const { return _levelsWithMultipleCopies; }

private:
    void initializeLevels();

    std::map<int, int> _cards;    // Key: Level, Value: Count
    std::map<int, int> _startingPool; // Key: Level, Value: Count
    std::set<int> _allLevels; // All levels stored in the cardPool
    std::set<int> _levelsWithMultipleCopies; // levels with multiple copies stored in the cardPool;
    std::string _poolName;
};

#endif // CARDPOOL_H