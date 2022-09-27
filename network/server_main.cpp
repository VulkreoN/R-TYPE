
#include "Server.hpp"

int main()
{
    Server server(5005);

    server.connect();
    while(true) {
        sleep(10);
        server.broadcast("10 seconds have passed\n");
        server.update();
    }
}
