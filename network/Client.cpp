/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string ip, const size_t port) : Network()
{
    _connection = std::make_unique<Connection> (asio::ip::udp::endpoint(asio::ip::make_address(ip), port), 1);
}

Client::~Client()
{
}

void Client::handle_incomming_message()
{
    // handle messages here with _buffer
}

void Client::broadcast(std::string msg)
{
    write(msg, _connection->get_endpoint());
}
