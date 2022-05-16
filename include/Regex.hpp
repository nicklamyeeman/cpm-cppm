/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef REGEX_HPP_
#define REGEX_HPP_

#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <regex>

#include "OpenFile.hpp"
#include "Replace.hpp"
#include "Dir.hpp"

class Regex {
    public:
        Regex();
        ~Regex();

        static void updateMakefile(std::vector<std::string> &files);
        static void changeNameFormatter(std::string const &match, std::string &dest);
        static void changeFilesNames(std::vector<std::string> &files, std::string &projectName);
        static void changeFilesContent(std::vector<std::string> &files, std::string &projectName);
        static void updateHeader(std::string const &className, std::string &projectName, std::vector<std::string> &files);
        static void updateFiles(std::string const &extension, std::string const &className, std::vector<std::string> &files);
        static std::vector<std::string> findFiles(std::string &ext, std::string const &className, std::vector<std::string> &files);

    protected:
    private:
};

#endif /* !REGEX_HPP_ */
