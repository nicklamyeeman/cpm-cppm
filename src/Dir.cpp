/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#include "Dir.hpp"

Dir::Dir()
{
}

Dir::~Dir()
{
}

void Dir::scan(std::vector<std::string> &dest, std::string const &path)
{
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_directory(entry.path()))
            Dir::scan(dest, entry.path());
        else
            dest.push_back(entry.path());
    }
}

void Dir::getCurrentDirName(std::string &projectName)
{
    std::vector<std::string> path;
    std::istringstream iss(std::filesystem::current_path());

    for (std::string token; std::getline(iss, token, '/');) {
        if (token.size() > 0)
            path.push_back(std::move(token));
    }
    projectName = path.back();
}