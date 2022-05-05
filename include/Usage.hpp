/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Usage
*/

#ifndef USAGE_HPP_
#define USAGE_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>

template <typename T, typename V>
class Usage {
    public:
        Usage(T pm, V &args)
        {
            this->_validCmd = false;
            this->_usage = "$name <command>\n\nUsage:\n\n$cmds\n\nAll commands:\n\n\t$listcmds";
            std::map<std::string, std::string> cmds {
                {"install", "install the dependency in your project"},
                {"start", "create the project with some parameters"}
            };
            this->_cmds = cmds;
            this->whichUsage(pm, args);
        }

        bool isValidCmd()
        {
            return this->_validCmd;
        }

        std::string getCmdsStr(std::string const &found)
        {
            std::string cmds_str("");
            if (found.empty()) {
                std::for_each(this->_cmds.begin(), this->_cmds.end(), [&cmds_str](const std::pair<std::string, std::string> cmd) mutable {
                    cmds_str.append(cmd.first);
                    cmds_str.append("\t\t");
                    cmds_str.append(cmd.second);
                    cmds_str.append("\n");
                });
                cmds_str.resize(cmds_str.size() - 1);
            } else {
                std::for_each(this->_cmds.begin(), this->_cmds.end(), [&](const std::pair<std::string, std::string> cmd) mutable {
                    if (found.compare(cmd.first) == 0) {
                        cmds_str.append(cmd.first);
                        cmds_str.append("\t\t");
                        cmds_str.append(cmd.second);
                    }
                });
            }
            return cmds_str;
        }

    protected:
        void whichUsage(T pm, V args)
        {
            if (args.size() == 0) {
                this->usageInterpreter(pm, args, "");
            } else if (args.size() == 1) {
                if (args.at(0).compare("-h") == 0 || args.at(0).compare("--help") == 0) {
                    this->usageInterpreter(pm, args, "");
                } else if (pm.getCmds().count(args.at(0)) > 0) {
                    this->_validCmd = true;
                } else {
                    std::cerr << args.at(0) << ": invalid command." << std::endl;
                    this->usageInterpreter(pm, args, "");
                }
            } else {
                if (args.at(0).compare("-h") == 0 || args.at(0).compare("--help") == 0) {
                    if (pm.getCmds().count(args.at(1)) > 0) {
                        this->usageInterpreter(pm, args, args.at(1));
                    } else {
                        std::cerr << args.at(1) << ": invalid command. Try:" << std::endl;
                        this->usageInterpreter(pm, args, "");
                    }
                } else {
                    if (pm.getCmds().count(args.at(0)) > 0) {
                        this->_validCmd = true;
                    } else {
                        std::cerr << args.at(1) << ": invalid command" << std::endl;
                        this->usageInterpreter(pm, args, "");
                    }
                }
            }
        }

        void usageInterpreter(T pm, V args, std::string const &found)
        {
            std::regex interpret("\\$\\w+");

            for (std::sregex_iterator i = std::sregex_iterator(this->_usage.begin(), this->_usage.end(), interpret); i != std::sregex_iterator(); i++) {
                std::smatch match = *i;
                std::string match_str = match.str();
                if (match_str.compare("$name") == 0)
                    this->replaceAll(this->_usage, match_str, pm.getName());
                if (match_str.compare("$cmds") == 0)
                    this->replaceAll(this->_usage, match_str, this->getCmdsStr(found));
                if (match_str.compare("$listcmds") == 0)
                    this->replaceAll(this->_usage, match_str, pm.getCmdsStr());
            }
            std::cerr << this->_usage << std::endl;
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
        bool _validCmd;
        std::string _usage;
        std::map<std::string, std::string> _cmds;
};

#endif /* !USAGE_HPP_ */
