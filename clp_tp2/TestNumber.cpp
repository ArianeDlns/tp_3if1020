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

TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestAssign )
{
    Number n{ 12345678 };
    Number n_assigned{ 0 };
    n_assigned = n;
    std::ostringstream os;
    os << n_assigned;   
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestAffectCopy )
{
    Number n{ 12345678 };
    Number n_copied = n;
    std::ostringstream os;
    os << n_copied;
    EXPECT_EQ( os.str(), "12345678" );
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

