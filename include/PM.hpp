/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#ifndef PM_HPP_
#define PM_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Debug.hpp"
#include "Usage.hpp"

class PM {
    public:
        PM(std::vector<std::string> &args);
        ~PM();

        void start(void);
        void install(void);

        std::string getName(void);
        std::vector<std::string> getCmds(void);
        std::string getCmdsStr(void);

    protected:
        std::string _name;
        std::vector<std::string> _cmds;
    private:
};

#endif /* !PM_HPP_ */
