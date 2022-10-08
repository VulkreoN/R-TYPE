
#include "ANetwork.hpp"

int main()
{
    ANetwork network(asio::ip::udp::endpoint(asio::ip::udp::v4(), 5008));

    for (;;) {
        sleep(3);
        network.write("Hello", asio::ip::udp::endpoint(asio::ip::udp::v4(), 5006));
    }
}
