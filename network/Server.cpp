/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(size_t port) : _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}

Server::~Server()
{
}

void Server::connect()
{
    try {
        accept_client();
        _threadContext = std::thread([this]() { _context.run(); }); // make context run fake tasks to keep it busy
        std::cout << "Server online!" << std::endl; 
    } catch (std::exception& e) {
        std::cout << "SERVER ERROR: " << e.what() << std::endl;
    }
}

void Server::accept_client()
{
    _connections.push_back(std::make_unique<Connection>(std::make_unique<asio::ip::tcp::socket>(_context)));
    _acceptor.async_accept(*(_connections.back()->get_socket()), [this](std::error_code ec)
        {
            if (ec) {
                std::cout << "SERVER ERROR: " << ec.message() << std::endl;
            } else {
                std::cout << "Connected" << std::endl;
                _connections.back()->set_connection(true);
            }
            accept_client(); // recursive to accept another client
        });
}

void Server::broadcast(std::string msg)
{
    for (std::unique_ptr<Connection>& connection : _connections)
        if (connection->check_if_connected())
            connection->add_to_write_queue(msg);
}

void Server::update()
{
    for (std::unique_ptr<Connection>& connection : _connections)
        connection->check_for_writing();
}
