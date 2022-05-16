/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/

#include <iostream>
#include <vector>

#ifdef _CPPM_
    #include "CPPM.hpp"
#endif

#ifdef _CPM_
    #include "CPM.hpp"
#endif

int main(int ac, char **av)
{
    std::vector<std::string> args(av + 1, av + ac);

    #ifdef _CPPM_
        new CPPM(args);
    #endif

    #ifdef _CPM_
        new CPM(args);
    #endif
    return 0;
}