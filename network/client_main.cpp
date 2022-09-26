
#include "Client.hpp"

int main()
{
    Client client("127.0.0.1", 5005);

    client.connect();
    while (1) {}
}
