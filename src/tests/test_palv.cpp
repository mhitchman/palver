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
