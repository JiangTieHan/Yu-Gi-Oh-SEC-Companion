#include "SECManager.h"
#include "utils.h"
#include <unordered_map>
#include <set>

// enum class SECCommandType {
//     INVALID,
//     RESET,
//     MODIFICATION_XYZ,
//     MODIFICATION_FUSION,
//     CALCULATION,
//     CONFIRMATION_YES,
//     CONFIRMATION_NO,
//     QUIT,
// };
const static std::string xyz = "XYZ";
const static std::string fusion = "Fusion";
const static std::string banish = "Banish";

SECManager::SECManager() :
_currentState(SECState::IDLE),
_xyzPool(xyz),
_fusionPool(fusion),
_banishPool(banish)
{
}

bool SECManager::processCommand(const std::vector<std::string> &command)
{
    bool result = false;
    // command is validated by the parser.
    if (command.empty()) {
        return result;
    }

    SECCommandType commandType = getSECCommandType(command);
    if (commandType == SECCommandType::RESET) {
        _currentState = SECState::IDLE;
        _xyzPool.resetPool();
        _fusionPool.resetPool();
        _banishPool.resetPool();
        return true;
    }

    bool poolUpdated = false;
    switch (_currentState)
    {
        case SECState::IDLE:
            if (commandType == SECCommandType::MODIFICATION_XYZ) {
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _xyzPool.updatePool(level, change);
                result = true;
            }
            else if (commandType == SECCommandType::MODIFICATION_FUSION) {
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _fusionPool.updatePool(level, change);
                result = true;
            }
            else if (commandType == SECCommandType::MODIFICATION_BANISH) {
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _banishPool.updatePool(level, change);
                result = true;
            }
            else if (commandType == SECCommandType::CALCULATION) {

            }
            else {
                result = false;
            }
            break;

        case SECState::BUSY:
            break;

        case SECState::WAITING_CONFIRMATION: 
            break;
        
        default:
            break;
    }

    if (poolUpdated) {
        _xyzPool.displayPool();
        _fusionPool.displayPool();
        _banishPool.displayPool();
    }
    return result;
}

void SECManager::setCurrentState(SECState newState)
{
    _currentState = newState;
}
