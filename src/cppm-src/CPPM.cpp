/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#include "CPPM.hpp"

CPPM::CPPM(std::vector<std::string> &args) : PM(args)
{
    this->_className = std::string("cppm");

    #ifdef _DEBUG_
    Debug<CPPM> Debug(*this);
    #endif

    Usage<CPPM, std::vector<std::string>> _usage_(*this, args);
    if (_usage_.isValidCmd()) {
        this->_cmds[args.at(0)](args);
    }
}

CPPM::~CPPM()
{
}
