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

    std::string parseCommandLineArg(int argc, char* argv[]);
    std::filesystem::path findConfigDir();
    std::filesystem::path findTemplateDir(std::filesystem::path configDir);
    void copyTemplateProjectToCWD(const std::filesystem::path& templateDir, const std::string& projectName);
}
