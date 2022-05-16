/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
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
