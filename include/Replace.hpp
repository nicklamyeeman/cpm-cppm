/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Replace
*/

#ifndef REPLACE_HPP_
#define REPLACE_HPP_

#include <iostream>
#include <sstream>

class Replace {
    public:
        Replace();
        ~Replace();

        static void all(std::string &s, std::string const &toReplace, std::string const &replaceWith);
    protected:
    private:
};

#endif /* !REPLACE_HPP_ */
