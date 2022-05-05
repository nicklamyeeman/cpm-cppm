/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** CPM
*/

#include "CPM.hpp"

CPM::CPM(std::vector<std::string> &args) : PM(args)
{
    this->_name = std::string("cpm");

    #ifdef _DEBUG_
    Debug<CPM> debug(*this);
    #endif

    Usage<CPM, std::vector<std::string>> _usage_(*this, args);
    if (_usage_.isValidCmd()) {
        this->_cmds[args.at(0)](args);
    }
}

CPM::~CPM()
{
}
