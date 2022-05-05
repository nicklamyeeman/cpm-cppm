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

void PM::start(std::vector<std::string> &args)
{
    std::cout << _LIB_ << std::endl;
    std::cout << "start" << std::endl;
    std::cout << this->_name << std::endl;
}

void PM::install(std::vector<std::string> &args)
{
    std::cout << "install" << std::endl;
    std::cout << this->_name << std::endl;
}

std::string PM::getName(void) const
{
    return this->_name;
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
