#include "Explode.hpp"

std::vector<std::string> Explode::explode(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);) {
        if (token.size() > 0)
            result.push_back(std::move(token));
    }
    return result;
}
