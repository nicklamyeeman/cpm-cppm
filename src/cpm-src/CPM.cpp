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

    if ((args.size() == 0) || 
        (args.size() > 0 && (args.at(0).compare("-h") == 0 || args.at(0).compare("--help") == 0)))
        Usage<CPM, std::vector<std::string>> Usage(*this, args);
}

CPM::~CPM()
{
}
