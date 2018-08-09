#pragma once

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

    std::filesystem::path findConfigDir();
    std::filesystem::path findTemplateDir(std::filesystem::path configDir);
    void copyTemplateProjectToCurrentDir(const std::filesystem::path& templateDir);
}
