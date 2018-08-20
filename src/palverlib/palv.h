#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>

namespace palverlib
{
    class file_not_found_error : public std::runtime_error
    {
    public:
	explicit file_not_found_error(const std::filesystem::path& missingFile)
	    :std::runtime_error{missingFile.string()}
	    {}
    };

    std::filesystem::path findHomeDir();
    std::filesystem::path findConfigDir(std::filesystem::path homeDir);
    std::filesystem::path findTemplateDir(std::filesystem::path configDir, const std::string& templateName);
    std::filesystem::path copyTemplateProjectToCWD(const std::filesystem::path& templateDir, const std::string& projectName);
    bool runTemplateActions(const std::filesystem::path& destination, const std::string& projectName);
}
