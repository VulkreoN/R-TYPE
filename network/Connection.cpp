/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Connection
*/

#include "Connection.hpp"

Connection::Connection(asio::ip::udp::endpoint endpoint, size_t id)
{
    _endpoint = endpoint;
    _id = id;
    std::cout << "New connection, id = " << _id << ", connected to " << _endpoint << std::endl;
}

Connection::~Connection()
{
}

asio::ip::udp::endpoint Connection::get_endpoint()
{
    return (_endpoint);
}

size_t Connection::get_id()
{
    return (_id);
}
