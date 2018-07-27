#include <filesystem>
#include <iostream>
#include <string>
#include <exception>

std::filesystem::path findConfigDir()
{
    // Returns the path to the existing config directory ~/.palver
    
    const std::string configDirName = ".palver";
    if (auto homeDir = std::getenv("HOME"); homeDir)
    {
	std::filesystem::path homeDirPath = std::filesystem::path(homeDir);
	return homeDirPath.append(configDirName);
    }
    else
    {
	throw std::runtime_error("HOME environment variable not set");
    }
}

std::filesystem::path findTemplateDir(std::filesystem::path configDir)
{
    const std::string templateDirName = "app";
    configDir.append(templateDirName);

    if (!std::filesystem::exists(configDir))
    {
	std::string error = configDir.string() + " doesn't exist";
	throw std::invalid_argument(error);
    }

    return configDir;
}

void copyTemplateProjectToCurrentDir(const std::filesystem::path& templateDir)
{
    std::filesystem::path destination = std::filesystem::current_path() / templateDir.stem().string(); // append won't work if second argument is path
    std::filesystem::copy(templateDir, destination, std::filesystem::copy_options::recursive);
}

int main()
{
    auto configDir = findConfigDir();
    auto templateDir = findTemplateDir(configDir);
    copyTemplateProjectToCurrentDir(templateDir);
}
