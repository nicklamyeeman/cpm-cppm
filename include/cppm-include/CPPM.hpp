/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef CPPM_HPP_
#define CPPM_HPP_

#include "PM.hpp"

class CPPM : public PM {
    public:
        CPPM(std::vector<std::string> &args);
        ~CPPM();

    protected:
    private:
};

#endif /* !CPPM_HPP_ */
