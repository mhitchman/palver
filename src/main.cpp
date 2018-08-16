#include "palv.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string projectName = palverlib::parseCommandLineArg(argc, argv);
    try
    {
	auto homeDir = palverlib::findHomeDir();
	auto configDir = palverlib::findConfigDir(homeDir);
	auto templateDir = palverlib::findTemplateDir(configDir);
	palverlib::copyTemplateProjectToCWD(templateDir, projectName);
    }
    catch(palverlib::file_not_found_error& e)
    {
	std::cerr << e.what() << " doesn't exist\n";
    }
    catch(std::runtime_error& e)
    {
	std::cerr << e.what() << std::endl;
    }
}
