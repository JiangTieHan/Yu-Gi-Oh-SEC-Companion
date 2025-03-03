#include "utils.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

const std::string INVALID_CMD = "invalid";

const std::string RESET_CMD = "reset";
const std::string RESET_CMD_ALIAS = "r";

const std::string QUIT_CMD = "quit";
const std::string QUIT_CMD_ALIAS = "q";

const std::string YES_CMD = "yes";
const std::string YES_CMD_ALIAS = "y";

const std::string NO_CMD = "no";
const std::string NO_CMD_ALIAS = "n";

const std::string MODIFY_XYZ_CMD = "xyz";
const std::string MODIFY_FUSION_CMD = "fusion";

std::vector<std::string> parse(const std::string& input) {
    std::vector<std::string> tokens{"invalid"};
    std::istringstream iss(input);
    std::string word;

    // Trim leading/trailing spaces (simple check)
    if (input.empty() || input.find_first_not_of(" \t") == std::string::npos) {
        std::cout << "Error: Empty input. Please enter a command.\n";
        return tokens;
    }

    // Read the first word (command)
    if (iss >> word) {
        static const std::unordered_map<std::string, std::string> commandAliases = {
            {RESET_CMD_ALIAS, RESET_CMD},
            {YES_CMD_ALIAS, YES_CMD},
            {NO_CMD_ALIAS, NO_CMD},
            {QUIT_CMD_ALIAS, QUIT_CMD},
        };
        static const std::unordered_set<std::string> commandSet = {
            RESET_CMD,
            MODIFY_XYZ_CMD,
            MODIFY_FUSION_CMD,
            YES_CMD,
            NO_CMD,
            QUIT_CMD,
        };

        for(char& c : word) {
            c = tolower(c);
        }

        // Replace shortcut commands with full names
        auto it = commandAliases.find((word));
        if (it != commandAliases.end()) {
            word = it->second;
        }
        
        auto jt = commandSet.find(word);
        if (jt != commandSet.end()) {
            tokens[0] = word;
        }
        else {
            return tokens;
        }
    }

    // Read the remaining words (arguments)
    while (iss >> word) {
        for(char& c : word) {
            c = tolower(c);
        }
        tokens.push_back(word);
    }

    return tokens;
}


SECCommandType getSECCommandType(const std::vector<std::string> &tokens)
{
    if (tokens.empty()) {
        return SECCommandType::INVALID;
    }

    const std::string& command = tokens[0];

    if (RESET_CMD == command) {
        return SECCommandType::RESET;
    }
    else if (MODIFY_XYZ_CMD == command) {
        return SECCommandType::MODIFICATION_XYZ;
    }
    else if (MODIFY_FUSION_CMD == command) {
        return SECCommandType::MODIFICATION_FUSION;
    }
    else if (YES_CMD == command) {
        return SECCommandType::CONFIRMATION_YES;
    }
    else if (NO_CMD == command) {
        return SECCommandType::CONFIRMATION_NO;
    }
    else if (QUIT_CMD == command) {
        return SECCommandType::QUIT;
    }
    else {
        return SECCommandType::INVALID;
    }
}

bool isValidCommand(const std::vector<std::string>& tokens) {
    if (tokens.empty() || tokens[0] == INVALID_CMD) {
        return false;
    }

    const std::string& command = tokens[0];

    if (command == RESET_CMD || command == QUIT_CMD || command == YES_CMD || command == NO_CMD) {
        return tokens.size() == 1;
    }

    if ((command == MODIFY_XYZ_CMD || command == MODIFY_FUSION_CMD) && tokens.size() == 3) {
        return isNumber(tokens[1]) && isNumber(tokens[2]);
    }

    return false;
}

bool isNumber(const std::string& num) {
    if (num.empty()) return false;

    size_t start = 0;
    if (num[0] == '-') {
        if (num.size() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < num.size(); ++i) {
        if (!isdigit(num[i])) return false;
    }

    return true;
}