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
    bool new_client = true;

    for (int i = 0; i < _connections.size(); i++)
        if (_connections[i]->get_endpoint() == _edp_buff)
            new_client = false;
    if (new_client)
        _connections.push_back(std::make_unique<Connection> (_edp_buff, _connections.size() + 1));
    // here, handle the recienved message stored in _buffer
}

void Server::broadcast(std::string msg)
{
    for (int i = 0; i < _connections.size(); i++)
        write(msg, _connections[i]->get_endpoint());
}
