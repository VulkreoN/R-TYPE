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
        asio::async_connect(*_connection->get_socket(), _endpoint,
            [this] (std::error_code ec, asio::ip::tcp::endpoint endpt)
            {
                if (ec) {
                    std::cout << "ERROR CONNECTING: " << ec.message() << std::endl;
                } else {
                    std::cout << "Connected successfully" << std::endl;
                    _connection->set_connection(true);
                    _connection->setup_read();
                }
            });
        _threadContext = std::thread([this]() { _context.run(); }); // make context run fake tasks to keep it busy
    }
}

void Client::broadcast(std::string msg)
{
    if (_connection->check_if_connected())
        _connection->add_to_write_queue(msg);
}

void Client::update()
{
    _connection->check_for_writing();
}
