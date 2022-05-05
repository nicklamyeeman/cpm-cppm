/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** PM
*/

#include "PM.hpp"

PM::PM(std::vector<std::string> &args)
{
    std::map<std::string, std::function<void(std::vector<std::string> &)>> cmds {
        { "install", std::bind(&PM::install, this, std::placeholders::_1) },
        { "start", std::bind(&PM::start, this, std::placeholders::_1) }
    };
    this->_cmds = cmds;
}

PM::~PM()
{
}

void PM::loading(void)
{
    std::chrono::seconds s(1);

    while (!this->_cmdDone) {
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "." << std::flush;
        if (this->_cmdDone)
            break;
        std::this_thread::sleep_for(s);
        std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
}

void PM::scanDir(std::string path)
{
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_directory(entry.path()))
            this->scanDir(entry.path());
        else
            this->_files.push_back(entry.path());
    }
}

void PM::replaceAll(std::string &s, std::string const &toReplace, std::string const &replaceWith)
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

std::string PM::changeFormatter(std::string match, std::string dest)
{
    if (match.compare("$name") == 0) {
        std::transform(dest.begin(), dest.end(), dest.begin(), ::tolower);
        return dest;
    }
    if (match.compare("$Name") == 0) {
        std::transform(dest.begin(), dest.begin() + 1, dest.begin(), ::toupper);
        std::transform(dest.begin() + 1, dest.end(), dest.begin() + 1, ::tolower);
        return dest;
    }
    if (match.compare("$NAME") == 0) {
        std::transform(dest.begin(), dest.end(), dest.begin(), ::toupper);
        return dest;
    }
    return dest;
}

void PM::changeFilesNames(void)
{
    std::for_each(std::begin(this->_files), std::end(this->_files), [this](std::string &fileName) {
        std::string oldFileName = fileName;
        std::regex interpret("\\$[a-zA-Z]+");

        for (std::sregex_iterator i = std::sregex_iterator(fileName.begin(), fileName.end(), interpret); i != std::sregex_iterator(); i++) {
            std::smatch match = *i;
            std::string match_str = match.str();
            std::string newProjectName = this->changeFormatter(match_str, this->_projectName);

            this->replaceAll(fileName, match_str, newProjectName);
            std::rename(oldFileName.c_str(), fileName.c_str());
        }
    });
}

void PM::changeFilesContent(void)
{
    std::for_each(std::begin(this->_files), std::end(this->_files), [this](std::string &fileName) {
        std::string oldFileName = fileName;
        std::ifstream oldFile(fileName);
        std::ofstream newFile(fileName.append("-tmp"));

        if (!oldFile.is_open() || !newFile.is_open())
            std::cerr << "Error while creating files." << std::endl;
        else {
            std::string line;
            while (getline(oldFile, line)) {
                std::regex interpret("\\$[a-zA-Z]+");

                for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), interpret); i != std::sregex_iterator(); i++) {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    std::string newLine = this->changeFormatter(match_str, this->_projectName);

                    this->replaceAll(line, match_str, newLine);
                }
                newFile << line << std::endl;
            }
            oldFile.close();
            newFile.close();
            std::remove(oldFileName.c_str());
            std::rename(fileName.c_str(), oldFileName.c_str());
        }
    });
}

void PM::start(std::vector<std::string> &args)
{
    this->_cmdDone = false;
    if (args.size() == 1) {
        std::cout << "Starting new project. Choose a name:" << std::endl << "> ";
        std::cin >> this->_projectName;
    } else {
        this->_projectName = args.at(1);
    }
    std::cout << "Creating project: '" << this->_projectName << "'" << std::flush;
    std::thread load(&PM::loading, this);

    if (!std::filesystem::is_directory(this->_projectName)) {
        std::filesystem::create_directory(this->_projectName);
        std::filesystem::copy(std::string(_LIB_).append("/start"), this->_projectName, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);

        this->scanDir(this->_projectName);
        this->changeFilesNames();
        this->changeFilesContent();
    } else {
        std::cerr << std::endl << this->_projectName << ": directory already exist." << std::endl;
    }

    this->_cmdDone = true;

    load.join();
    std::cout << std::endl;
}

void PM::install(std::vector<std::string> &args)
{
    std::cout << "install" << std::endl;
    std::cout << this->_className << std::endl;
}

std::string PM::getClassName(void) const
{
    return this->_className;
}

std::map<std::string, std::function<void(std::vector<std::string> &)>> PM::getCmds(void) const
{
    return this->_cmds;
}

std::string PM::getCmdsStr(void) const
{
    std::string cmds_str("");
    std::for_each(this->_cmds.begin(), this->_cmds.end(), [&cmds_str](const std::pair<std::string, std::function<void(std::vector<std::string> &)>> &cmd) mutable {
        cmds_str.append(cmd.first);
        cmds_str.append(", ");
    });
    cmds_str.resize(cmds_str.size() - 2);
    return cmds_str;
}
