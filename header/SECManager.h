#ifndef SEC_MANAGER_H
#define SEC_MANAGER_H

#include "CardPool.h"
#include <vector>
#include <string>

using SECCommand = std::vector<std::string>;

enum class SECState {
    IDLE,
    BUSY,
    WAITING_CONFIRMATION,
};

class SECManager {
public:
    SECManager();
    ~SECManager() = default;

    inline SECState getCurrentState() const { return _currentState; }
    inline bool isBusy() const { return _currentState == SECState::BUSY; }

    bool processCommand(const SECCommand& command);

private:
    bool canActivateSEC(int totalCard) const;
    bool canApplySECEffect(const std::vector<int>& monsterLevels) const;
    void setStateIdle();

    CardPool _xyzPool;
    CardPool _fusionPool;
    CardPool _banishPool;
    SECState _currentState;
    std::vector<SECCommand> _pendingCommands;
};

#endif // SEC_MANAGER_H