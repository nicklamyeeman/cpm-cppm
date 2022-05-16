/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef REPLACE_HPP_
#define REPLACE_HPP_

#include <iostream>
#include <sstream>

class Replace {
    public:
        Replace();
        ~Replace();

        static void all(std::string &s, std::string const &toReplace, std::string const &replaceWith);
    protected:
    private:
};

#endif /* !REPLACE_HPP_ */
