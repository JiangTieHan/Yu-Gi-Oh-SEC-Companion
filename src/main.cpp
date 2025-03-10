#include "utils.h"
#include "SECManager.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::string input;
    SECManager secManager;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) {
            std::cerr << "Error: Unable to read input. Exiting...\n";
            break;  // Exit if input stream fails
        }

        if (input.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        std::vector<std::string> tokens = parse(input);
        if (getSECCommandType(tokens) == SECCommandType::QUIT) {
            break;
        }

        if (!isValidCommand(tokens)) {
            std::cout << "invalid input\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        else {
            secManager.processCommand(tokens);
        }

        // for (const auto& token : tokens) {
        //     std::cout << "[" << token << "]\n";
        // }
    }

    return 0;
}