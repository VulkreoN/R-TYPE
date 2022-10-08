/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ANetwork
*/

#include "ANetwork.hpp"

ANetwork::ANetwork() : _socket(_context)
{
    _socket.open(asio::ip::udp::v4());
}

ANetwork::ANetwork(asio::ip::udp::endpoint endpoint) : _socket(_context, endpoint)
{
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); }); // make context run fake tasks to keep it busy
}

ANetwork::~ANetwork()
{
}

void ANetwork::write(std::string msg, asio::ip::udp::endpoint endpoint)
{
    _socket.send_to(asio::buffer(msg), endpoint);
}

void ANetwork::read_setup()
{
    _socket.async_receive_from(asio::buffer(_buffer), _edp_buff,
        [this](asio::error_code ec, size_t size) {
            if (ec) {
                std::cout << "ERROR READING: " << ec.message() << std::endl;
                return;
            }
            _buffer[size] = '\0';
            std::cout << _edp_buff << " : " << _buffer << std::endl;
            read_setup();
        });
}
