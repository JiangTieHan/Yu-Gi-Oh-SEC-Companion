#include "CardPool.h"
#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <sstream>

TEST_GROUP(CardPoolTestGroup)
{
    CardPool* pool = nullptr;

    void setup()
    {
        const std::map<int, int> initialPool = {{3, 2}, {4, 2}, {5, 2}};
        pool = new CardPool(initialPool);
    }

    void teardown()
    {
        delete pool;
    }
};

/** @brief Captures the output of displayPool() for testing */
std::string captureDisplay(CardPool& pool) {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    pool.displayPool();
    std::cout.rdbuf(oldCout);
    return output.str();
}

TEST(CardPoolTestGroup, ConstructorInitializesCorrectly)
{
    STRCMP_EQUAL("(3 * 2) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}