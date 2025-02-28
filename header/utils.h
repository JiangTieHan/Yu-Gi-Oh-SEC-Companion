#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

enum class SECCommandType {
    INVALID,
    RESET,
    MODIFICATION,
    CALCULATION,
    CONFIRMATION_YES,
    CONFIRMATION_NO,
    QUIT,
};

std::vector<std::string> parse(const std::string& input);

SECCommandType getSECCommandType(const std::vector<std::string>& tokens);

bool isValidCommand(const std::vector<std::string>& tokens);

#endif // UTILS_H
