#ifndef SEC_MANAGER_H
#define SEC_MANAGER_H

#include "CardPool.h"
#include <vector>
#include <string>
#include <utility>

using SECCommand = std::vector<std::string>;

enum class SECState {
    IDLE,
    BUSY,
    WAITING_CONFIRMATION,
};

struct BanishCandidate {
    int xyzLevel;
    int fusionLevel;

    BanishCandidate() :
    xyzLevel(0), fusionLevel(0) {}

    BanishCandidate(int xyzLevel, int fusionLevel) :
    xyzLevel(xyzLevel), fusionLevel(fusionLevel) {}
};

class SECManager {
public:
    SECManager();
    ~SECManager() = default;

    inline SECState getCurrentState() const { return _currentState; }
    inline bool isBusy() const { return _currentState == SECState::BUSY; }

    bool processCommand(const SECCommand& command);

private:
    bool canActivateSEC(int totalCard);
    bool canApplySECEffect(const std::vector<int>& monsterLevels);
    void setStateIdle();
    void resetCardPools();
    void displayCardPools() const;

    CardPool _xyzPool;
    CardPool _fusionPool;
    CardPool _banishedXyzPool;
    CardPool _banishedFusionPool;
    SECState _currentState;
    std::vector<SECCommand> _pendingCommands;
    std::vector<BanishCandidate> _banishCandidates;
    BanishCandidate _banishCandidate;
    BanishCandidate _returnCandidate;
};

#endif // SEC_MANAGER_H