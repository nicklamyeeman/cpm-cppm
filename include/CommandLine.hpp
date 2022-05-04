/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** CommandLine
*/

#ifndef COMMANDLINE_HPP_
#define COMMANDLINE_HPP_

#include <iostream>
#include <vector>

class CommandLine {
    public:
        CommandLine(std::vector<std::string> &args);
        ~CommandLine();

    protected:
    private:
        static const std::vector<std::string> cmds;
};


#endif /* !COMMANDLINE_HPP_ */
