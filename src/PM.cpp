/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#include "PM.hpp"

PM::PM(std::vector<std::string> &args)
{
    std::vector<std::string> cmds {"start", "install"};
    this->_cmds = cmds;
}

PM::~PM()
{
}

std::string PM::getName(void)
{
    return this->_name;
}

std::vector<std::string> PM::getCmds(void)
{
    return this->_cmds;
}

std::string PM::getCmdsStr(void)
{
    std::string cmds_str("");
    std::for_each(std::begin(_cmds), std::end(_cmds) - 1, [&cmds_str](std::string const &cmd) mutable {
        cmds_str.append(cmd);
        cmds_str.append(", ");
    });
    cmds_str.append(_cmds.back());
    return cmds_str;
}
