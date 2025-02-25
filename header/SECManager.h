#ifndef SEC_MANAGER_H
#define SEC_MANAGER_H

#include "CardPool.h"

class SECManager {
public:
    SECManager();
    ~SECManager() = default;

private:
    CardPool xyzPool;
    CardPool fusionPool;
};

#endif // SEC_MANAGER_H