#include "utils.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
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
            {RESET_CMD_ALIAS, RESET_CMD}, {RESET_CMD, RESET_CMD},
            {YES_CMD_ALIAS, YES_CMD}, {YES_CMD, YES_CMD},
            {NO_CMD_ALIAS, NO_CMD}, {NO_CMD, NO_CMD},
            {QUIT_CMD_ALIAS, QUIT_CMD}, {QUIT_CMD, QUIT_CMD},
        };

        for(char& c : word) {
            c = tolower(c);
        }

        // Replace shortcut commands with full names
        auto it = commandAliases.find((word));
        if (it != commandAliases.end()) {
            tokens[0] = it->second;
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

    // Commands that must not have extra arguments
    if (command == RESET_CMD || command == QUIT_CMD || command == YES_CMD || command == NO_CMD) {
        return tokens.size() == 1;
    }

    return false;
}
