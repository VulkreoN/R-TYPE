/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Connection
*/

#include "Connection.hpp"

Connection::Connection(std::unique_ptr<asio::ip::tcp::socket> socket) : _socket(std::move(socket))
{
    _write_queue = std::make_unique<Queue> ();
    _read_queue = std::make_unique<Queue> ();
}

Connection::~Connection()
{
}

void Connection::add_to_write_queue(std::string str)
{
    _write_queue->add_to_queue(str);
}

std::string Connection::get_from_read_queue()
{
    return (_read_queue->get_from_queue());
}

void Connection::connect_to_server(const asio::ip::tcp::resolver::results_type& endpoint)
{
    asio::async_connect(*_socket, endpoint,
        [this] (std::error_code ec, asio::ip::tcp::endpoint endpt)
        {
            if (!ec)
                std::cout << "Connected successfully" << std::endl;
        });
}

const std::unique_ptr<asio::ip::tcp::socket> &Connection::get_socket() const
{
    return (_socket);
}
