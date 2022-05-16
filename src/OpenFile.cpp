/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#include "OpenFile.hpp"

void OpenFile::readFile()
{
    std::string tmp;
    _ifile.open(_filepath.c_str());

 	if (!_ifile.is_open())
        throw;
    while (std::getline(_ifile, tmp))
        _data.push_back(tmp);
    _ifile.close();
}

void OpenFile::overwriteFile(std::vector<std::string> &content)
{
    _ofile.open(_filepath.c_str());

    if (!_ofile.is_open())
        throw;
    for (int i = 0; i != (int)content.size(); i++)
        _ofile << content.at(i) << std::endl;
    _ofile.close();
}

OpenFile::OpenFile(const std::string &filepath)
{
    _filepath = filepath;
    readFile();
}

OpenFile::~OpenFile()
{
}
