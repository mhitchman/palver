#include <filesystem>
#include <iostream>
#include <string>
#include <palv.h>

namespace palverlib
{

    std::string parseCommandLineArg(int argc, char* argv[])
    {
	if (argc < 2)		// less than 2 means no argument was supplied
	{
	    return std::string();
	}

	return std::string(argv[1]);
    }

    std::filesystem::path findHomeDir()
    {
	auto homeDir = std::getenv("HOME");
	if (!homeDir)
	{
	    throw std::runtime_error("HOME environment variable not set");
	}

	std::filesystem::path homeDirPath(homeDir);
	if (!std::filesystem::exists(homeDirPath))
	{
	    throw file_not_found_error(homeDirPath);
	}

	return homeDirPath;
    }

    std::filesystem::path findConfigDir(std::filesystem::path homeDir)
    {
	// Returns the path to the existing config directory ~/.palver
	const std::string configDirName = ".palver";

	auto configDirPath = homeDir.append(configDirName);

	if (!std::filesystem::exists(configDirPath))
	{
	    throw file_not_found_error(configDirPath);
	}

	return configDirPath;
    }


    std::filesystem::path findTemplateDir(std::filesystem::path configDir, std::string templateName)
    {
	if (templateName.empty())
	{
	    throw std::invalid_argument("No template name provided");
	}
	configDir.append(templateName);

	if (!std::filesystem::exists(configDir))
	{
	    throw file_not_found_error(configDir);
	}
	if (!std::filesystem::is_directory(configDir))
	{
	    throw std::invalid_argument(templateName + " does not specify a template directory");
	}

	return configDir;
    }

    void copyTemplateProjectToCWD(const std::filesystem::path& templateDir, const std::string& projectName)
    {
	std::filesystem::path destination;

	// If project name isn't provided just use the template name
	if (projectName.empty())
	{
	    // append won't work if second argument is filesystem::path
	    destination = std::filesystem::current_path() /
		templateDir.stem().string();
	}
	else
	{
	    destination = std::filesystem::current_path() /
		projectName;
	}

	std::filesystem::copy(templateDir, destination,
			      std::filesystem::copy_options::recursive);
    }
}
