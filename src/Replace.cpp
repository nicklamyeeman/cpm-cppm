/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Replace
*/

#include "Replace.hpp"

Replace::Replace()
{
}

Replace::~Replace()
{
}

void Replace::all(std::string &s, std::string const &toReplace, std::string const &replaceWith)
{
    std::ostringstream oss;
    std::size_t pos = 0;
    std::size_t prevPos;

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        oss << s.substr(prevPos, pos - prevPos);
        oss << replaceWith;
        pos += toReplace.size();
    }
    oss << s.substr(prevPos);
    s = oss.str();
}