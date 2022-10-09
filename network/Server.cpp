/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(size_t port) : Network(asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

Server::~Server()
{
}

void Server::handle_incomming_message()
{
    for (int i = 0; i < _connections.size(); i++)
        if (_connections[i]->get_endpoint() == _edp_buff)
            return;
    _connections.push_back(std::make_unique<Connection> (_edp_buff, _connections.size() + 1));
}
