/*
** EPITECH PROJECT, 2022
** cpm-cppm
** File description:
** Regex
*/

#include "Regex.hpp"

Regex::Regex()
{
}

Regex::~Regex()
{
}

void Regex::changeNameFormatter(std::string const &match, std::string &dest)
{
    if (match.compare("$name") == 0) {
        std::transform(dest.begin(), dest.end(), dest.begin(), ::tolower);
    }
    if (match.compare("$Name") == 0) {
        std::transform(dest.begin(), dest.begin() + 1, dest.begin(), ::toupper);
        std::transform(dest.begin() + 1, dest.end(), dest.begin() + 1, ::tolower);
    }
    if (match.compare("$NAME") == 0) {
        std::transform(dest.begin(), dest.end(), dest.begin(), ::toupper);
    }
}

void Regex::changeFilesNames(std::vector<std::string> &files, std::string &projectName)
{
    std::for_each(std::begin(files), std::end(files), [&](std::string &fileName) {
        std::string oldFileName = fileName;
        std::regex interpret("\\$[a-zA-Z]+");

        for (std::sregex_iterator i = std::sregex_iterator(fileName.begin(), fileName.end(), interpret); i != std::sregex_iterator(); i++) {
            std::smatch match = *i;
            std::string match_str = match.str();
            
            Regex::changeNameFormatter(match_str, projectName);
            Replace::all(fileName, match_str, projectName);
            std::rename(oldFileName.c_str(), fileName.c_str());
        }
    });
}

void Regex::changeFilesContent(std::vector<std::string> &files, std::string &projectName)
{
    std::for_each(std::begin(files), std::end(files), [&](std::string &fileName) {
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
                    
                    Regex::changeNameFormatter(match_str, projectName);
                    Replace::all(line, match_str, projectName);
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

std::vector<std::string> Regex::findFiles(std::string &ext, std::string const &className, std::vector<std::string> &files)
{
   if (className.compare("cppm") == 0)
        ext.append("pp");

    std::vector<std::string> foundFiles;
    std::copy_if(files.begin(), files.end(), std::back_inserter(foundFiles), [&](std::string file) {
        std::regex interpret("\\.\\w+$");        
        for (std::sregex_iterator i = std::sregex_iterator(file.begin(), file.end(), interpret); i != std::sregex_iterator(); i++) {
            std::smatch match = *i;
            if (match.str().compare(ext) == 0)
                return true;
        }
        return false;
    });
    std::for_each(foundFiles.begin(), foundFiles.end(), [&](std::string &file) {
        std::regex interpret("\\w+\\.\\w+$");
        for (std::sregex_iterator i = std::sregex_iterator(file.begin(), file.end(), interpret); i != std::sregex_iterator(); i++) {
            std::smatch match = *i;
            file = match.str();
        }
    });
    return foundFiles;
}

void Regex::updateFiles(std::string const &extension, std::string const &className, std::vector<std::string> &files)
{
    std::string ext(extension);
    std::vector<std::string> foundFiles = Regex::findFiles(ext, className, files);

    std::vector<std::string> newFiles;
    Dir::scan(newFiles, ".");
    files.clear();

    std::copy_if(newFiles.begin(), newFiles.end(), std::back_inserter(files), [&](std::string _file) {
        for (const std::string &file: foundFiles) {
            if (_file.find(file) != _file.npos)
                return true;
        }
        return false;
    });
}

void Regex::updateMakefile(std::vector<std::string> &files)
{
    std::string makefile("Makefile");
    std::string makefileTmp("Makefile-tmp");
    std::ifstream oldMakePath(makefile);

     if (!oldMakePath.is_open())
        std::cerr << "Warning! No Makefile found." << std::endl;
    else {
        std::ofstream newMakePath(makefileTmp);
        if (newMakePath.is_open()) {
            std::string line;
            while (getline(oldMakePath, line)) {
                std::regex interpret("^SRC\\s.=\\s.");

                for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), interpret); i != std::sregex_iterator(); i++) {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    Replace::all(line, match_str, "\t\t\t\t");
                    newMakePath << "SRC\t\t=\t\t" << files.at(0) << "\t\t\\" << std::endl;
                    std::for_each(std::begin(files) + 1, std::end(files), [&](std::string const &fileName) {
                        newMakePath << "\t\t\t\t" << fileName << "\t\t\\" << std::endl;
                    });
                }
                newMakePath << line << std::endl;
            }
            oldMakePath.close();
            newMakePath.close();
            std::remove(makefile.c_str());
            std::rename(makefileTmp.c_str(), makefile.c_str());
        }
    }
}

void Regex::updateHeader(std::string const &className, std::string &projectName, std::vector<std::string> &files)
{
    std::string ext(".h");
    std::string header("./include/");

    if (className.compare("cppm") == 0) {
        ext.append("pp");
        std::transform(projectName.begin(), projectName.begin() + 1, projectName.begin(), ::toupper);
        std::transform(projectName.begin() + 1, projectName.end(), projectName.begin() + 1, ::tolower);
    } else
        std::transform(projectName.begin(), projectName.end(), projectName.begin(), ::tolower);
    
    header.append(projectName);
    header.append(ext);

    std::string headerTmp(header);
    headerTmp.append("-tmp");

    std::ifstream oldHeadPath(header);

     if (!oldHeadPath.is_open())
        std::cerr << "Warning! No header ("<< header << ") found." << std::endl;
    else {
        std::ofstream newHeadPath(headerTmp);
        if (newHeadPath.is_open()) {
            std::vector<std::string> include;
            std::string line;
            while (getline(oldHeadPath, line)) {
                newHeadPath << line << std::endl;

                if (!include.empty()) {
                    std::for_each(std::begin(include), std::end(include), [&](std::string const &includeFile) {
                        newHeadPath << "#include \"" << includeFile << "\"" << std::endl;
                    });
                    include.clear();
                }

                std::regex interpret("^#define\\s(\\w+)_(\\w+)_$");
                for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), interpret); i != std::sregex_iterator(); i++) {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    std::for_each(std::begin(files), std::end(files), [&](std::string const &fileName) {
                        std::regex in("\\w+\\.\\w+$");
                        for (std::sregex_iterator i = std::sregex_iterator(fileName.begin(), fileName.end(), in); i != std::sregex_iterator(); i++) {
                            std::smatch m = *i;
                            include.push_back(m.str());
                        }
                    });
                }
            }
            oldHeadPath.close();
            newHeadPath.close();
            std::remove(header.c_str());
            std::rename(headerTmp.c_str(), header.c_str());
        }
    }
}