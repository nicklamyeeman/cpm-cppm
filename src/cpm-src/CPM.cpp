/*
** EPITECH PROJECT, 2022
** cpm
** File description:
** CPM
*/

#include "CPM.hpp"
#include "CommandLine.hpp"

CPM::CPM(std::vector<std::string> &args)
{
    std::cout << typeid(this).name() << " constructor" << std::endl; 

    new CommandLine(args);
}

CPM::~CPM()
{
}
