
#include "Client.hpp"

int main(int ac, char **av)
{
    Client cli("127.0.0.1", 5006);

    for (;;) {
        sleep(3);
        cli.broadcast("Hello");
    }
}
