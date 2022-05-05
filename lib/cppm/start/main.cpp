#include "$Name.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args(av + 1, av + ac);

    if (ac == 1)
        new $Name(args);
    return 0;
}