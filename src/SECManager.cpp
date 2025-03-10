#include "SECManager.h"
#include "utils.h"
#include <unordered_map>
#include <set>

const static std::string xyz = "XYZ";
const static std::string fusion = "Fusion";
const static std::string banish = "Banish";

SECManager::SECManager() :
_currentState(SECState::IDLE),
_xyzPool(xyz),
_fusionPool(fusion),
_banishPool(banish),
_pendingCommands()
{
}

bool SECManager::processCommand(const SECCommand &command)
{
    bool canProcess = false;
    // command is validated by the parser.
    if (command.empty()) {
        return canProcess;
    }

    SECCommandType commandType = getSECCommandType(command);
    if (commandType == SECCommandType::RESET) {
        setStateIdle();
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
                _currentState = SECState::BUSY;
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _xyzPool.updatePool(level, change);
                canProcess = true;
                setStateIdle();
            }
            else if (commandType == SECCommandType::MODIFICATION_FUSION) {
                _currentState = SECState::BUSY;
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _fusionPool.updatePool(level, change);
                canProcess = true;
                setStateIdle();
            }
            else if (commandType == SECCommandType::MODIFICATION_BANISH) {
                _currentState = SECState::BUSY;
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _banishPool.updatePool(level, change);
                canProcess = true;
                setStateIdle();
            }
            else if (commandType == SECCommandType::CALCULATION) {
                _currentState = SECState::BUSY;
                int monsterSize = command.size() - 3;
                int total = std::stoi(command[1]);
                std::vector<int> monsterLevels;
                for(int i=0;i<monsterSize;i++) {
                    monsterLevels.push_back(std::stoi(command[command.size() - 1 - i]));
                }

                canProcess = true;
            }
            else {
                canProcess = false;
            }
            break;

        case SECState::BUSY:
            break;

        case SECState::WAITING_CONFIRMATION: 
            break;
        
        default:
            break;
    }

    if (canProcess && poolUpdated) {
        _xyzPool.displayPool();
        _fusionPool.displayPool();
        _banishPool.displayPool();
    }
    return canProcess;
}

bool SECManager::canActivateSEC(int totalCard) const
{
    return false;
}

bool SECManager::canApplySECEffect(const std::vector<int> &monsterLevels) const
{
    return false;
}

void SECManager::setStateIdle()
{
    _pendingCommands.clear();
    _currentState = SECState::IDLE;
}
