#pragma once

#include <filesystem>
namespace palverlib
{
    std::filesystem::path findConfigDir();
    std::filesystem::path findTemplateDir(std::filesystem::path configDir);
    void copyTemplateProjectToCurrentDir(const std::filesystem::path& templateDir);
}
