#include <catch2/catch.hpp>

// temporary test to check it's working

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE ( "Stand in test" )
{
    REQUIRE( Factorial(1) == 1 );
}

