#include "CardPool.h"
#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <sstream>

#include <iostream>

const std::string initialPoolStr = "(3 * 2) (4 * 2) (5 * 2) \n";

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
std::string captureDisplay(CardPool& pool) 
{
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    pool.displayPool();
    std::cout.rdbuf(oldCout);
    return output.str();
}

TEST(CardPoolTestGroup, InitializationTest) 
{
    STRCMP_EQUAL(initialPoolStr.c_str(), captureDisplay(*pool).c_str());
    CHECK_FALSE(pool->isPoolEmpty());
}

TEST(CardPoolTestGroup, RemovalTest) 
{
    pool->updatePool(3, -1);
    STRCMP_EQUAL("(3 * 1) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, IncrementTest1)
{
    pool->updatePool(3, 1);
    STRCMP_EQUAL("(3 * 3) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, IncrementTest12)
{
    pool->updatePool(8, 1);
    STRCMP_EQUAL("(3 * 2) (4 * 2) (5 * 2) (8 * 1) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, ResetTest)
{
    pool->updatePool(3, 1);
    pool->resetPool();
    STRCMP_EQUAL(initialPoolStr.c_str(), captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, FailedToRemoveTest1)
{
    pool->updatePool(3, -3);
    STRCMP_EQUAL("(3 * 2) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, FailedToRemoveTest2)
{
    pool->updatePool(3, 0);
    STRCMP_EQUAL("(3 * 2) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, FailedToRemoveTest3)
{
    pool->updatePool(8, -1);
    STRCMP_EQUAL("(3 * 2) (4 * 2) (5 * 2) \n", captureDisplay(*pool).c_str());
}

TEST(CardPoolTestGroup, EmptyTest1)
{
    pool->updatePool(3, -2);
    pool->updatePool(4, -2);
    pool->updatePool(5, -2);
    CHECK_TRUE(pool->isPoolEmpty());
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}