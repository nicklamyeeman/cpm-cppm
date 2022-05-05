#include "$name.h"

int main(int ac, char **av)
{
    if (ac == 1)
        return ($name(av));
    return 0;
}