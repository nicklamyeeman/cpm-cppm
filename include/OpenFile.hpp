/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef OPENFILE_HPP_
#define OPENFILE_HPP_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

class OpenFile {
    public:
        OpenFile(const std::string &filepath);
        ~OpenFile();
    
        const std::vector<std::string> getData() const { return (_data); };
        void readFile();
        void overwriteFile(std::vector<std::string> &content);

    protected:
    private:
        std::string _filepath;
        std::ifstream _ifile;
        std::ofstream _ofile;
        std::vector<std::string> _data;
};

#endif /* !FILE_HPP_ */
