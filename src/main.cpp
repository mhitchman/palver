#include "palv.h"
#include <iostream>

int main()
{
    try
    {
	auto configDir = palverlib::findConfigDir();
	auto templateDir = palverlib::findTemplateDir(configDir);
	palverlib::copyTemplateProjectToCurrentDir(templateDir);
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
