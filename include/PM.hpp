/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
*/


#ifndef PM_HPP_
#define PM_HPP_

#include <thread>

#include "Replace.hpp"
#include "Usage.hpp"
#include "Regex.hpp"
#include "Debug.hpp"
#include "Dir.hpp"

class PM {
    public:
        PM(std::vector<std::string> &args);
        ~PM();

        void start(std::vector<std::string> &args);
        void install(std::vector<std::string> &args);

        std::string getCmdsStr(void) const;
        std::string getClassName(void) const;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> getCmds(void) const;

    protected:
        void loading(void);

        void importProject(void);
        void importPackage(std::string &pack);

        bool _cmdDone;
        std::string _className;
        std::string _projectName;
        std::vector<std::string> _files;
        std::map<std::string, std::function<void(std::vector<std::string> &)>> _cmds;
    private:
};

#endif /* !PM_HPP_ */
