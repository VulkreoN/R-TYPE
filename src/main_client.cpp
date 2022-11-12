#include <ostream>
#include <iostream>
#include <string>
#include "Core.hpp"

static std::string checkFlags(int ac, char **av)
{
    std::string ip = "";
    std::string port = "";
    std::string ret = "";

    for (int i = 1; i < ac; i++) {
        if (std::string(av[i]) == "-h" || std::string(av[i]) == "--help") {
            std::cout << "USAGE: ./r-type_client -i ip -p port." << std::endl;
            return "";
        }
        if (std::string(av[i]) == "-i" || std::string(av[i]) == "--ip") {
            if (i + 1 < ac)
                ip = av[i + 1];
            else
                std::cout << "Error: -i or --ip flag needs an argument." << std::endl;
        }
        if (std::string(av[i]) == "-p" || std::string(av[i]) == "--port") {
            if (i + 1 < ac)
                port += av[i + 1];
            else
                std::cout << "Error: -p or --port flag needs an argument." << std::endl;
        }
    }
    ret = ip + ":" + port;
    return ret;
}

int main(int ac, char **av)
{
    std::string ip_port = checkFlags(ac, av);
    if (ip_port.length() <= 5)
        ip_port = std::string("127.0.0.1:5005");

    std::string ip = ip_port.substr(0, ip_port.find(":"));
    size_t port = std::stoi(ip_port.substr(ip_port.find(":") + 1, ip_port.size()));

    R_TYPE::Core core(ip, port);

    try {
        core.mainLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
