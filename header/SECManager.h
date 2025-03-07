#ifndef SEC_MANAGER_H
#define SEC_MANAGER_H

#include "CardPool.h"
#include <vector>
#include <string>

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

    void processCommand(const std::vector<std::string>& command);

private:
    void setCurrentState(SECState newState);

    CardPool _xyzPool;
    CardPool _fusionPool;
    CardPool _banishPool;
    SECState _currentState;
};

#endif // SEC_MANAGER_H