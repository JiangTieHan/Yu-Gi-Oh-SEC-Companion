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
_banishCandidates(),
_returnCandidate(),
_banishCandidate()
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
        resetCardPools();
        return true;
    }

    bool poolUpdated = false;
    bool hsaReturnCandidate = false;
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

                if (canActivateSEC(total)) {
                    hsaReturnCandidate = canApplySECEffect(monsterLevels);
                }

                if (hsaReturnCandidate) {
                    _currentState = SECState::WAITING_CONFIRMATION;
                }
                else {
                    setStateIdle();
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

    if (poolUpdated) {
        displayCardPools();
    }

    // if (hsaReturnCandidate) {
    //     std::cout << "" << std::endl;
    // }
    return canProcess;
}

// Return true when player can activate SEC (totalCard = 2(xyzLevel) + fusionLevel)
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
            BanishCandidate banishCandidate(xyzLevel, targetFusionLevel);
            _banishCandidates.push_back(banishCandidate);
            canActivate = true;
        }
    }
    return canActivate;
}

bool SECManager::canApplySECEffect(const std::vector<int> &monsterLevels)
{
    bool canApply = false;
    if (monsterLevels.empty() || 
       (_banishCandidates.empty() || (_banishedXyzPool.isPoolEmpty() && _banishedFusionPool.isPoolEmpty()))) {
        return false;    
    }

    CardPool tempXyzPool = _banishedXyzPool;
    CardPool tempFusionPool = _banishedFusionPool;
    for(const auto& banishCandidate : _banishCandidates ) {
        tempXyzPool.updatePool(banishCandidate.xyzLevel, 2);
        tempFusionPool.updatePool(banishCandidate.fusionLevel, 1);
    }
    _banishCandidates.clear();

    for(int monsterLevel : monsterLevels) {
        for (int xyzLevel : tempXyzPool.getAllLevels()) {
            int targetFusionLevel = monsterLevel - xyzLevel;
            auto it = tempFusionPool.getAllLevels().find(targetFusionLevel);
            if (it != tempFusionPool.getAllLevels().end()) {
                _returnCandidate.xyzLevel = xyzLevel;
                _returnCandidate.fusionLevel = targetFusionLevel;
                canApply = true;
            }
        }
    }

    return canApply;
}

void SECManager::setStateIdle()
{
    _pendingCommands.clear();
    _banishCandidates.clear();
    _returnCandidate.xyzLevel = 0; _returnCandidate.fusionLevel = 0;
    _currentState = SECState::IDLE;
}

void SECManager::resetCardPools()
{
    _xyzPool.resetPool();
    _fusionPool.resetPool();
    _banishedXyzPool.resetPool();
    _banishedFusionPool.resetPool();
}

void SECManager::displayCardPools() const
{
    _xyzPool.displayPool();
    _fusionPool.displayPool();
    _banishedXyzPool.displayPool();
    _banishedFusionPool.displayPool();
}
