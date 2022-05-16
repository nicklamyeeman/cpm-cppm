/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef DEBUG_HPP_
#define DEBUG_HPP_

template <class T>
class Debug {
    public:
    Debug(T pm) : _name(pm.getClassName())
    {
        std::string name = this->_name;
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);
        std::cout << name << " constructor" << std::endl;

        std::vector<std::string> cmds = pm.getCmds();
        std::for_each(std::begin(cmds), std::end(cmds), [](std::string const &value) {
            std::cout << value << std::endl;
        });
    }

    protected:
    private:
        std::string _name;
};

#endif /* !DEBUG_HPP_ */
