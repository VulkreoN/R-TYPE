/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string ip, const size_t port)
{
	asio::ip::tcp::resolver resolver(_context);
	_endpoint = resolver.resolve(ip, std::to_string(port));
    _connection = nullptr;
}

Client::~Client()
{
}

void Client::connect()
{
    if (_connection == nullptr) {
        _connection = std::make_unique<Connection> (std::make_unique<asio::ip::tcp::socket>(_context));
        _connection->connect_to_server(_endpoint);
    }
}
