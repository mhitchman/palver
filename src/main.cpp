#include "palv.h"

int main()
{
    auto configDir = palverlib::findConfigDir();
    auto templateDir = palverlib::findTemplateDir(configDir);
    palverlib::copyTemplateProjectToCurrentDir(templateDir);
}
