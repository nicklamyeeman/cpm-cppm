/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Dir
*/

#ifndef DIR_HPP_
#define DIR_HPP_

#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

class Dir {
    public:
        Dir();
        ~Dir();

        static void scan(std::vector<std::string> &dest, std::string const &path);
        static void getCurrentDirName(std::string &projectName);

    protected:
    private:
};

#endif /* !DIR_HPP_ */
