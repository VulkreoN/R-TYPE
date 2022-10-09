
#include "Server.hpp"

int main()
{
    Server server(5006);

    for (;;) {
        sleep(5);
        server.broadcast("EEeeeeeyyy!");
        //network.write("Hello", asio::ip::udp::endpoint(asio::ip::udp::v4(), 5006));
    }
}
