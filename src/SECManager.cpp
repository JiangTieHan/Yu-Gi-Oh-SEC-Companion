#include "SECManager.h"
#include "utils.h"
#include <unordered_map>
#include <set>

const static std::string xyz = "XYZ";
const static std::string fusion = "Fusion";
const static std::string banishedXyz = "BanishedXyz";
const static std::string banishedFusion = "BanishedFusion";

SECManager::SECManager() :
_currentState(SECState::IDLE),
_xyzPool(xyz),
_fusionPool(fusion),
_banishedXyzPool(banishedXyz),
_banishedFusionPool(banishedFusion),
_pendingCommands(),
_banishCandidates()
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
        _banishedXyzPool.resetPool();
        _banishedFusionPool.resetPool();
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
            else if (commandType == SECCommandType::MODIFICATION_BANISHED_XYZ) {
                _currentState = SECState::BUSY;
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _banishedXyzPool.updatePool(level, change);
                canProcess = true;
                setStateIdle();
            }
            else if (commandType == SECCommandType::MODIFICATION_BANISHED_FUSION) {
                _currentState = SECState::BUSY;
                int level = std::stoi(command[1]);
                int change = std::stoi(command[2]);
                poolUpdated = _banishedFusionPool.updatePool(level, change);
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
        _banishedXyzPool.displayPool();
    }
    return canProcess;
}

// Return ture when player can activate SEC (totalCard = 2(xyzLevel) + fusionLevel)
bool SECManager::canActivateSEC(int totalCard)
{
    bool canActivate = false;
    if (totalCard <=0 || _xyzPool.isPoolEmpty() || _fusionPool.isPoolEmpty()) {
        return false;
    }
    for (int xyzLevel : _xyzPool.getLevelsWithMultipleCopies()) {
        int targetFusionLevel = totalCard - 2 * xyzLevel;
        auto it = _fusionPool.getAllLevels().find(targetFusionLevel);
        if (it != _fusionPool.getAllLevels().end()) {
            _banishCandidates.insert(std::make_pair(2 * xyzLevel, targetFusionLevel));
            canActivate = true;
        }
    }
    return canActivate;
}

bool SECManager::canApplySECEffect(const std::vector<int> &monsterLevels) const
{
    return false;
}

void SECManager::setStateIdle()
{
    _pendingCommands.clear();
    _banishCandidates.clear();
    _currentState = SECState::IDLE;
}
