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
    _connected = false;
    _writing = false;
}

Connection::~Connection()
{
}

void Connection::add_to_write_queue(std::string str)
{
    _write_queue->add_to_queue(str);
}

std::string Connection::get_read_queue()
{
    return (_read_queue->get_queue());
}

void Connection::connect_to_server(const asio::ip::tcp::resolver::results_type& endpoint)
{
    asio::async_connect(*_socket, endpoint,
        [this] (std::error_code ec, asio::ip::tcp::endpoint endpt)
        {
            if (!ec) {
                std::cout << "Connected successfully" << std::endl;
                }
        });
}

const std::unique_ptr<asio::ip::tcp::socket> &Connection::get_socket() const
{
    return (_socket);
}

bool Connection::check_if_connected()
{
    return (_connected);
}

void Connection::set_connection(bool status)
{
    _connected = status;
}

void Connection::check_for_writing()
{
    if (_connected && !_writing && _write_queue->get_queue().size() != 0) {
        _writing = true;
        _socket->async_write_some(asio::buffer(_write_queue->get_queue().data(), _write_queue->get_queue().size()),
        [this](asio::error_code ec, std::size_t size) {
            if (ec)
                std::cout << "ERROR WRITING : " << std::endl;
            else
                _write_queue->remove_from_queue(size);
            _writing = false;
        });
    }
}
