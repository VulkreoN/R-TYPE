#include <ostream>
#include <iostream>
#include "Core.hpp"

int main(void)
{
    R_TYPE::Core core("127.0.0.1", 5005);

    try {
        core.mainLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
