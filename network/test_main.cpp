
#include "ANetwork.hpp"

int main()
{
    ANetwork network(asio::ip::udp::endpoint(asio::ip::udp::v4(), 5006));

    for (;;) {
        //network.write("Hello", asio::ip::udp::endpoint(asio::ip::udp::v4(), 5006));
    }
}
