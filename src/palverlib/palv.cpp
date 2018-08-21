#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <palv.h>
#include <string>

namespace palverlib
{
    void validateTemplateName(const std::string& templateName)
    {
	// verifies given template name only uses alphanumeric characters

	auto res = std::all_of(templateName.begin(),
			       templateName.end(),
			       [](char c){ return std::isalnum(c); });
	if (!res)
	{
	    throw std::invalid_argument("Invalid template name provided (only alphanumeric characters allowed)");
	}
    }

    std::filesystem::path findHomeDir()
    {
	auto homeDir = std::getenv("HOME");
	if (homeDir == nullptr)
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


    std::filesystem::path findTemplateDir(std::filesystem::path configDir, const std::string& templateName)
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

    std::filesystem::path copyTemplateProjectToCWD(const std::filesystem::path& templateDir, const std::string& projectName)
    {
	std::filesystem::path destination;

	destination = std::filesystem::current_path() /
	    projectName;

	std::filesystem::copy(templateDir, destination,
			      std::filesystem::copy_options::recursive);

	return destination;
    }

    bool runTemplateActions(const std::filesystem::path& destination, const std::string& projectName)
    {
	// Run the created template's action.palver shell script if it exists
	// and returns true if successful (false if unsuccessful)

	namespace fs = std::filesystem;
	const std::string actionScriptName = "actions.palver";

	auto scriptLocation = destination / actionScriptName;
	if (!fs::exists(scriptLocation))
	{
	    return true;
	}

	if (auto scriptPermissions = fs::status(scriptLocation).permissions();
	    (scriptPermissions & fs::perms::owner_exec) == fs::perms::none)
	{
	    std::cerr << scriptLocation.string() << " not executable\n";
	    return false;
	}

	std::string command = "cd " + destination.string() + " && " +
	    "./" + actionScriptName + ' ' + projectName;

	int returnValue = std::system(command.c_str());
	return fs::remove(scriptLocation) && (returnValue == 0);
    }
} // namespace palverlib
