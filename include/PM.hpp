/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#ifndef PM_HPP_
#define PM_HPP_

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdio>
#include <thread>
#include <regex>
#include <map>

#include "Debug.hpp"
#include "Usage.hpp"

class PM {
    public:
        PM(std::vector<std::string> &args);
        ~PM();

        void start(std::vector<std::string> &args);
        void install(std::vector<std::string> &args);

        std::string getCmdsStr(void) const;
        std::string getClassName(void) const;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> getCmds(void) const;

    protected:
        void loading(void);
        void changeFilesNames(void);
        void changeFilesContent(void);
        void scanDir(std::string path);
        std::string changeFormatter(std::string match, std::string dest);
        void replaceAll(std::string &s, std::string const &toReplace, std::string const &replaceWith);

        bool _cmdDone;
        std::string _className;
        std::string _projectName;
        std::vector<std::string> _files;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> _cmds;
    private:
};

#endif /* !PM_HPP_ */
