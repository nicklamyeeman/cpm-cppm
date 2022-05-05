/*
** EPITECH PROJECT, 2022
** cpm
** File description:
** CPPM
*/

#include "CPPM.hpp"

CPPM::CPPM(std::vector<std::string> &args) : PM(args)
{
    this->_className = std::string("cppm");

    #ifdef _DEBUG_
    Debug<CPPM> Debug(*this);
    #endif

    Usage<CPPM, std::vector<std::string>> _usage_(*this, args);
    if (_usage_.isValidCmd()) {
        this->_cmds[args.at(0)](args);
    }
}

CPPM::~CPPM()
{
}
