/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#ifndef PM_HPP_
#define PM_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Debug.hpp"
#include "Usage.hpp"

class PM {
    public:
        PM(std::vector<std::string> &args);
        ~PM();

        void start(std::vector<std::string> &args);
        void install(std::vector<std::string> &args);

        std::string getName(void) const;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> getCmds(void) const;
        std::string getCmdsStr(void) const;

    protected:
        std::string _name;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> _cmds;
    private:
};

#endif /* !PM_HPP_ */
