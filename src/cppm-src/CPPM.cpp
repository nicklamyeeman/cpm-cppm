/*
** EPITECH PROJECT, 2022
** cpm
** File description:
** CPPM
*/

#include "CPPM.hpp"

CPPM::CPPM(std::vector<std::string> &args) : PM(args)
{
    this->_name = std::string("cppm");

    #ifdef _DEBUG_
    Debug<CPPM> Debug(*this);
    #endif

    if ((args.size() == 0) || 
        (args.size() > 0 && (args.at(0).compare("-h") == 0 || args.at(0).compare("--help") == 0)))
        Usage<CPPM, std::vector<std::string>> Usage(*this, args);
}

CPPM::~CPPM()
{
}
