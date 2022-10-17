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
            if (PRINT_READ_MSG) {
                protocol::Header header = (protocol::Header)_buffer[0];
                std::cout << _edp_buff << " : " << header << std::endl;
                if (header == protocol::Header::PLAYER_ACTION) {
                    protocol::Action action = (protocol::Action)_buffer[sizeof(protocol::Header)];
                    std::cout << action << std::endl;
                    if (action == protocol::Action::BOTH || action == protocol::Action::MOVE) {
                        std::cout << "Moving to " << (size_t)_buffer[sizeof(protocol::Header) + sizeof(protocol::Action)] << ", " << (size_t)_buffer[sizeof(protocol::Header) + sizeof(protocol::Action) + sizeof(size_t)] << std::endl;
                    }
                }
            }
            handle_incomming_message();
            read_setup();
        });
}

}
