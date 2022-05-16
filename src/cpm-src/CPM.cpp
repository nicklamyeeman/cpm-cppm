/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#include "CPM.hpp"

CPM::CPM(std::vector<std::string> &args) : PM(args)
{
    this->_className = std::string("cpm");

    #ifdef _DEBUG_
    Debug<CPM> debug(*this);
    #endif

    Usage<CPM, std::vector<std::string>> _usage_(*this, args);
    if (_usage_.isValidCmd()) {
        this->_cmds[args.at(0)](args);
    }
}

CPM::~CPM()
{
}
