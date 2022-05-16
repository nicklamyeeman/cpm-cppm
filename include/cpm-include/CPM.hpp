/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef CPM_HPP_
#define CPM_HPP_

#include "PM.hpp"

class CPM : public PM {
    public:
        CPM(std::vector<std::string> &args);
        ~CPM();

    protected:
    private:
};

#endif /* !CPM_HPP_ */
