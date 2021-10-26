/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++11 -o TestNumber Number.cpp TestNumber.cpp -lgtest
 * ./TestNumber
 */

#include <exception>
#include <sstream>
#include <utility>

#include <gtest/gtest.h>
#include "Number.hpp"

TEST(TestNumber, TestNumber0)
{
    Number n{0};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestNumber, TestNumber12345678)
{
    Number n{12345678};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "12345678");
}

TEST(TestNumber, TestNumberBig)
{
    Number n{12345123451234512345UL};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "12345123451234512345");
}

TEST(TestNumber, TestAffect)
{
    Number n{12345678};
    Number n_affect{10};
    n_affect = n;
    std::ostringstream os;
    os << n_affect;
    EXPECT_EQ(os.str(), "12345678");
}

TEST(TestNumber, TestCopy)
{
    Number n{12345678};
    Number n_copied = n;
    std::ostringstream os;
    os << n_copied;
    EXPECT_EQ(os.str(), "12345678");
}

TEST(TestNumber, TestAdd)
{
    Number n{1234};
    n.add(2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "1236");
}

TEST(TestNumber, TestMultiply)
{
    Number n{1234};
    n.multiply(2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "2468");
}

TEST(TestNumber, TestFactorial123)
{
    std::ostringstream os;
    os << factorial(123);
    ;
    EXPECT_EQ(os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                        "358923621676688311569606126402021707358352212940477825910915704116514"
                        "72186029519906261646730733907419814952960000000000000000000000000000");
}

TEST(TestNumber, TestStrConstruc)
{
    Number n{"123"};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "123");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
