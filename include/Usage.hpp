/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Usage
*/

#ifndef USAGE_HPP_
#define USAGE_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

template <typename T, typename V>
class Usage {
    public:
        Usage(T pm, V &args) {
            std::string usage_path = _USAGE_;
            usage_path.append("usage");
            if (args.size() > 1) {
                usage_path.append("-");
                usage_path.append(args.at(1));
            }
            openFile(pm, args, usage_path);
        }

    protected:
        void openFile(T pm, V args, std::string path)
        {
            std::string line;
            std::ifstream usage(path);
            if (usage.is_open()) {
                while (getline(usage, line))
                    lineInterpreter(pm, args, line);
                usage.close();
            } else {
                if (args.size() > 1) {
                    std::cerr << args.at(1) << ": invalid command. Try: " << std::endl;
                    std::string usage_path = _USAGE_;
                    openFile(pm, args, usage_path.append("usage"));
                } else {
                    std::cerr << pm.getName();
                    std::for_each(std::begin(args), std::end(args), [](std::string const &arg) {
                        std::cerr << " " << arg;
                    });
                    std::cerr << ": invalid command" << std::endl;
                }
            }
        }

        void lineInterpreter(T pm, V args, std::string line)
        {
            std::regex interpret("(?:\\$)(\\w+)");

            for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), interpret); i != std::sregex_iterator(); i++) {
                std::smatch match = *i;
                std::string match_str = match.str();
                if (match_str.compare("$name") == 0)
                    replaceAll(line, match_str, pm.getName());
                if (match_str.compare("$cmds") == 0)
                    replaceAll(line, match_str, pm.getCmdsStr());
            }
            std::cout << line << std::endl;
        }

        void replaceAll(std::string &s, std::string const &toReplace, std::string const &replaceWith)
        {
            std::ostringstream oss;
            std::size_t pos = 0;
            std::size_t prevPos;

            while (true) {
                prevPos = pos;
                pos = s.find(toReplace, pos);
                if (pos == std::string::npos)
                    break;
                oss << s.substr(prevPos, pos - prevPos);
                oss << replaceWith;
                pos += toReplace.size();
            }
            oss << s.substr(prevPos);
            s = oss.str();
        }
    private:
};

#endif /* !USAGE_HPP_ */
