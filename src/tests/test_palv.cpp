#include <catch2/catch.hpp>
#include <filesystem>
#include <iostream>
#include <palv.h>

TEST_CASE ( "Filesystem tests ")
{
    auto cwd = std::filesystem::current_path();
    auto testDir = cwd / "testConf";
    REQUIRE ( std::filesystem::exists(testDir) );

    auto expectedTarget = cwd / "testApp";

    SECTION ( "findTemplateDir" )
    {
	auto testConfDir = palverlib::findConfigDir(testDir);
    	REQUIRE ( std::filesystem::exists(testConfDir) );

	SECTION ( "Finds template folders correctly" )
	{
	    auto actualPath = testConfDir / "app";
	    auto tempPath = palverlib::findTemplateDir(testConfDir, "app");
	    REQUIRE ( tempPath.string() == actualPath.string() );

	    actualPath = testConfDir / "app2";
	    tempPath = palverlib::findTemplateDir(testConfDir, "app2");
	    REQUIRE ( tempPath.string() == actualPath.string() );
	}

	SECTION ( "Failure cases" )
	{
	    SECTION ( "Nonexistent template folder" )
	    {
		REQUIRE_THROWS( palverlib::findTemplateDir(testConfDir, "nonexistenttemplatefolder"));
	    }

	    SECTION ( "Name provided is a file" )
	    {
		REQUIRE_THROWS( palverlib::findTemplateDir(testConfDir, "testFile.txt"));
	    }

	    SECTION ( "Called with empty file name string" )
	    {
		REQUIRE_THROWS( palverlib::findTemplateDir(testConfDir, ""));
	    }
	}
    }

    SECTION ( "findConfigDir")
    {
    	auto testConfDir = palverlib::findConfigDir(testDir);
    	REQUIRE ( std::filesystem::exists(testConfDir) );

    	auto testTemplateDir = palverlib::findTemplateDir(testConfDir, "app");
    	REQUIRE ( std::filesystem::exists(testTemplateDir) );

    	palverlib::copyTemplateProjectToCWD(testTemplateDir, "testApp");
    	REQUIRE ( std::filesystem::exists(expectedTarget) );
    }

    // TEARDOWN
    std::filesystem::remove_all(expectedTarget);
}

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

