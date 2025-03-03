#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

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

std::vector<std::string> parse(const std::string& input);

SECCommandType getSECCommandType(const std::vector<std::string>& tokens);

bool isValidCommand(const std::vector<std::string>& tokens);

bool isNumber(const std::string& num);

#endif // UTILS_H
