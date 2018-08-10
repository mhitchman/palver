#include <catch2/catch.hpp>
#include "../palv.h"

TEST_CASE ( "Command Line Parsing: project name " )
{
    SECTION( "Not enough variables" )
    {
	const int argc = 1;
	char arg1[] = "executable";
	char* argv[argc];
	argv[0] = arg1;

	REQUIRE( palverlib::parseCommandLineArg(argc, argv) == "" );
    }

    SECTION( "Too many variables" )
    {
	const int argc = 3;
	char arg1[] = "executable";
	char arg2[] = "projectName";
	char arg3[] = "additional value";
	char* argv[argc];
	argv[0] = arg1;
	argv[1] = arg2;
	argv[2] = arg3;

	REQUIRE( palverlib::parseCommandLineArg(argc, argv) == "projectName" );
    }

    SECTION( "Empty name value" )
    {
	const int argc = 2;
	char arg1[] = "executable";
	char arg2[] = "";
	char* argv[argc];
	argv[0] = arg1;
	argv[1] = arg2;

	REQUIRE( palverlib::parseCommandLineArg(argc, argv) == "" );
    }
}

