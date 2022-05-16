/*
** Copyright (c) 2022, Nick LAM YEE MAN
** All rights reserved.
**
** This source code is licensed under the BSD-style license found in the
** LICENSE file in the root directory of this source tree. 
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
        try {
            OpenFile file(fileName);

            std::vector<std::string> fileContent = file.getData();
            std::for_each(std::begin(fileContent), std::end(fileContent), [&](std::string &line) {
                std::regex interpret("\\$[a-zA-Z]+");

                for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), interpret); i != std::sregex_iterator(); i++) {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    
                    Regex::changeNameFormatter(match_str, projectName);
                    Replace::all(line, match_str, projectName);
                }
            });
            file.overwriteFile(fileContent);
        } catch (std::exception &e) {
            std::cerr << "Error while creating files." << std::endl;
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
    try {
        int k = 0;
        OpenFile file("Makefile");

        std::vector<std::string> fileContent = file.getData();

        std::for_each(std::begin(fileContent), std::end(fileContent), [&](std::string &line) {
            std::regex interpret("^SRC\\s.=\\s.");

            for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), interpret); it != std::sregex_iterator(); it++) {
                std::smatch match = *it;
                std::string match_str = match.str();

                Replace::all(line, match_str, "\t\t\t\t");

                std::string newLine("SRC\t\t=\t\t");
                fileContent.insert(fileContent.begin() + k, newLine.append(files.at(0).append("\t\t\\")));
                std::for_each(std::begin(files) + 1, std::end(files), [&](std::string const &fileName) {
                    newLine = "";
                    fileContent.insert(fileContent.begin() + k + 1, newLine.append("\t\t\t\t").append(fileName).append("\t\t\\"));
                });
            }
            k += 1;
        });
        file.overwriteFile(fileContent);
    } catch (std::exception &e) {
        std::cerr << "Warning! No Makefile found." << std::endl;
    }
}

void Regex::updateHeader(std::string const &className, std::string &projectName, std::vector<std::string> &files)
{
    std::string header("./include/");
    header.append(projectName).append((className.compare("cpm") == 0) ? ".h" : ".hpp");

    try {
        int k = 0;
        int pos = 0;
        OpenFile file(header);

        std::vector<std::string> fileContent = file.getData();
        std::vector<std::string> include;

        std::for_each(std::begin(fileContent), std::end(fileContent), [&](std::string &line) {
            std::regex interpret("^#define\\s(\\w+)_(\\w+)_$");
            
            for (std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), interpret); it != std::sregex_iterator(); it++) {
                std::smatch match = *it;
                std::string match_str = match.str();

                std::for_each(std::begin(files), std::end(files), [&](std::string const &fileName) {
                    std::regex in("\\w+\\.\\w+$");
                    for (std::sregex_iterator i = std::sregex_iterator(fileName.begin(), fileName.end(), in); i != std::sregex_iterator(); i++) {
                        std::smatch m = *i;
                        include.push_back(m.str());
                    }
                });
                pos = k + 1;
            }
            k += 1;
        });
        std::for_each(std::begin(include), std::end(include), [&](std::string const &includeFile) {
            std::string newLine = "";
            fileContent.insert(fileContent.begin() + pos + 1, newLine.append("#include \"").append(includeFile).append("\""));
        });
        file.overwriteFile(fileContent);
    } catch (std::exception &e) {
        std::cerr << "Warning! No header ("<< header << ") found." << std::endl;
    }
}