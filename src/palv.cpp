#include <filesystem>
#include <iostream>
#include <string>
#include <stdexcept>

#include "palv.h"

namespace palverlib
{
    std::filesystem::path findConfigDir()
    {
	// Returns the path to the existing config directory ~/.palver

	const std::string configDirName = ".palver";
	auto homeDir = std::getenv("HOME");
	if (!homeDir)
	{
	    throw std::runtime_error("HOME environment variable not set");
	}

	std::filesystem::path homeDirPath = std::filesystem::path(homeDir);
	if (!std::filesystem::exists(homeDirPath))
	{
	    throw file_not_found_error(homeDirPath);
	}
	return homeDirPath.append(configDirName);
    }


    std::filesystem::path findTemplateDir(std::filesystem::path configDir)
    {
	const std::string templateDirName = "app";
	configDir.append(templateDirName);

	if (!std::filesystem::exists(configDir))
	{
	    throw file_not_found_error(configDir);
	}

	return configDir;
    }

    void copyTemplateProjectToCurrentDir(const std::filesystem::path& templateDir)
    {
	// append won't work if second argument is filesystem::path
	std::filesystem::path destination = std::filesystem::current_path() /
	    templateDir.stem().string();

	std::filesystem::copy(templateDir, destination,
			      std::filesystem::copy_options::recursive);
    }
}
