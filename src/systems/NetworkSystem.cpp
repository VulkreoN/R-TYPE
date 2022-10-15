/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"

namespace R_TYPE {

NetworkSystem::NetworkSystem() : _socket(_context)
{
}

NetworkSystem::NetworkSystem(size_t port) : _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::read_setup()
{
    _socket.async_receive_from(asio::buffer(_buffer), _edp_buff,
        [this](asio::error_code ec, size_t size) {
            if (ec) {
                std::cout << "ERROR READING: " << ec.message() << std::endl;
                return;
            }
            _buffer[size] = '\0';
            if (PRINT_READ_MSG)
                std::cout << _edp_buff << " : " << _buffer << std::endl;
            handle_incomming_message();
            read_setup();
        });
}

}
