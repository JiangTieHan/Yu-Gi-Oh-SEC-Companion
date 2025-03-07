#include "SECManager.h"
#include "utils.h"
#include <unordered_map>
#include <set>

enum class SECCommandType {
    INVALID,
    RESET,
    MODIFICATION_XYZ,
    MODIFICATION_FUSION,
    CALCULATION,
    CONFIRMATION_YES,
    CONFIRMATION_NO,
    QUIT,
};

const static std::unordered_map<SECState, std::set<SECCommandType>> stateToCommandTable = {
    { SECState::IDLE, { SECCommandType::RESET, SECCommandType::MODIFICATION_XYZ, SECCommandType::MODIFICATION_FUSION, SECCommandType::CALCULATION, SECCommandType::QUIT} },
};

SECManager::SECManager() :
_currentState(SECState::IDLE),
_xyzPool(),
_fusionPool(),
_banishPool()
{
}

void SECManager::processCommand(const std::vector<std::string> &command)
{
    // command is validated by the parser.
    if (command.empty()) {
        return;
    }

    SECCommandType commandType = getSECCommandType(command);
    switch (_currentState)
    {
        case SECState::IDLE:
            /* code */
            break;

        case SECState::BUSY:
            break;

        case SECState::WAITING_CONFIRMATION: 
        default:
            break;
    }
}

void SECManager::setCurrentState(SECState newState)
{
    _currentState = newState;
}
