/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** CommandLine
*/

#include "CommandLine.hpp"

CommandLine::CommandLine(std::vector<std::string> &args)
{
    std::cout << typeid(this).name() << " constructor" << std::endl; 

    std::for_each(std::begin(args), std::end(args), [](std::string const &value) {
        std::cout << value << std::endl;
    });
}

CommandLine::~CommandLine()
{
}
