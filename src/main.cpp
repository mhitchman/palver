#include <clara.hpp>
#include <iostream>
#include <palv.h>
#include <string>
#include <tuple>

struct cliArguments
{
    std::string templateName = "app";
    std::string projectName;
};

cliArguments setCLI(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    auto [templateName, projectName] = setCLI(argc, argv);

    try
    {
	auto homeDir = palverlib::findHomeDir();
	auto configDir = palverlib::findConfigDir(homeDir);
	auto templateDir = palverlib::findTemplateDir(configDir, templateName);
	palverlib::copyTemplateProjectToCWD(templateDir, projectName);
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

cliArguments setCLI(int argc, char* argv[])
{
    cliArguments args;
    auto cli
	= clara::Opt(args.templateName, "Template name")
	["-n"]["--new"]
	("Type of project to create")
	| clara::Arg(args.projectName, "Project name")
	("Name of the created project");
    cli.parse(clara::Args(argc, argv));
    return args;
}
