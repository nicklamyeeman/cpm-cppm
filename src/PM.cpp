/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#include "PM.hpp"

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

void PM::loading(void)
{
    std::chrono::seconds s(1);

    while (!this->_cmdDone) {
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(s);
        std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
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

    std::chrono::seconds s(10);
    std::this_thread::sleep_for(s);
    this->_cmdDone = true;

    load.join();
}

void PM::install(std::vector<std::string> &args)
{
    std::cout << "install" << std::endl;
    std::cout << this->_className << std::endl;
}

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
