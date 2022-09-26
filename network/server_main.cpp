
#include "Server.hpp"

int main()
{
    Server server(5005);

    server.connect();
    while(true) {}
}
