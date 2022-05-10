/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#include "PM.hpp"

/**
 * CONSTRUCTOR & DESTRUCTOR
 */

PM::PM(std::vector<std::string> &args)
{
    std::map<std::string, std::function<void(std::vector<std::string> &)>> cmds {
        { "install", std::bind(&PM::install, this, std::placeholders::_1) },
        { "start", std::bind(&PM::start, this, std::placeholders::_1) }
    };
    this->_cmds = cmds;
}

PM::~PM()
{
}

/**
 * GETTERS & SETTERS
 */

std::string PM::getClassName(void) const
{
    return this->_className;
}

std::map<std::string, std::function<void(std::vector<std::string> &)>> PM::getCmds(void) const
{
    return this->_cmds;
}

std::string PM::getCmdsStr(void) const
{
    std::string cmds_str("");
    std::for_each(this->_cmds.begin(), this->_cmds.end(), [&cmds_str](const std::pair<std::string, std::function<void(std::vector<std::string> &)>> &cmd) mutable {
        cmds_str.append(cmd.first);
        cmds_str.append(", ");
    });
    cmds_str.resize(cmds_str.size() - 2);
    return cmds_str;
}

/**
 * TOOLS
 */

void PM::loading(void)
{
    std::chrono::seconds s(1);

    while (!this->_cmdDone) {
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
}

void PM::importProject(void)
{
    if (!std::filesystem::is_directory(this->_projectName)) {
        std::filesystem::create_directory(this->_projectName);
        std::filesystem::copy(std::string(_LIB_).append("/start"), this->_projectName, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);

        Dir::scan(this->_files, this->_projectName);
        
        Regex::changeFilesNames(this->_files, this->_projectName);
        Regex::changeFilesContent(this->_files, this->_projectName);

    } else {
        std::cerr << std::endl << this->_projectName << ": directory already exist." << std::endl;
    }
}

void PM::importPackage(std::string &pack)
{
    Dir::getCurrentDirName(this->_projectName);
    std::string libPath = std::string(_LIB_).append("/install/").append(pack);

    if (!std::filesystem::is_directory(libPath)) {
        std::cout << "No package " << pack << " found." << std::endl;
    } else {
        std::filesystem::copy(libPath, ".", std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
        Dir::scan(this->_files, libPath);
        Regex::updateFiles(".c", this->_className, this->_files);
        Regex::updateMakefile(this->_files);
        
        Dir::scan(this->_files, libPath);
        Regex::updateFiles(".h", this->_className, this->_files);
        Regex::updateHeader(this->_className, this->_projectName, this->_files);
    }
}

/**
 * COMMANDS
 */

void PM::install(std::vector<std::string> &args)
{
    this->_cmdDone = false;

    std::string pack;
    if (args.size() == 1) {
        std::cout << "Please write package name:" << std::endl << "> ";
        std::cin >> pack;
    } else {
        pack = args.at(1);
    }
    std::cout << "Importing package " << pack << std::endl; 
    std::thread load(&PM::loading, this);

    this->importPackage(pack);

    this->_cmdDone = true;
    load.join();
    std::cout << std::endl;
}

void PM::start(std::vector<std::string> &args)
{
    this->_cmdDone = false;

    if (args.size() == 1) {
        std::cout << "Starting new project. Choose a name:" << std::endl << "> ";
        std::cin >> this->_projectName;
    } else {
        this->_projectName = args.at(1);
    }
    std::cout << "Creating project: '" << this->_projectName << "'" << std::flush;
    std::thread load(&PM::loading, this);

    this->importProject();

    this->_cmdDone = true;
    load.join();
    std::cout << std::endl;
}