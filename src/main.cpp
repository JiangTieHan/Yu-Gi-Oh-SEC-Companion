#include "utils.h"
#include <iostream>

int main() {
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        std::vector<std::string> tokens = parse(input);

        for (const auto& token : tokens) {
            if (!isValidCommand(tokens)) {
                std::cout << "invalid input" << "\n";
            }
            else {
                std::cout << "[" << token << "]\n";
            }
        }
    }

    return 0;
}