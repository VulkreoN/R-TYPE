/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NetworkSystem
*/

#include <bitset>
#include "NetworkSystem.hpp"

namespace R_TYPE {

NetworkSystem::NetworkSystem() : _socket(_context)
{
    _buffer.assign(MAX_MSG_LENGTH, 0);
}

NetworkSystem::NetworkSystem(size_t port) : _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    _buffer.assign(MAX_MSG_LENGTH, 0);
}

void NetworkSystem::read_setup()
{
    _socket.async_receive_from(asio::buffer(_buffer), _edp_buff,
        [this](asio::error_code ec, size_t size) {
            if (ec) {
                std::cout << "ERROR READING: " << ec.message() << std::endl;
                return;
            }
            _buffer[size - 1] = 0;
            if (PRINT_READ_MSG) {
                protocol::Header header = (protocol::Header)_buffer[0];
                // std::cout << _edp_buff << " : " << header << std::endl;
            }
            handle_incomming_message();
            read_setup();
        });
}

void NetworkSystem::putInt(int value, std::vector<uint8_t> &buff, size_t c)
{
    buff[c] |= value >> 8*3;
    buff[c + 1] |= value >> 8*2;
    buff[c + 2] |= value >> 8;
    buff[c + 3] |= value;
}

int NetworkSystem::readInt(const std::vector<uint8_t> &buff, size_t c)
{
    return (buff[c] << 8*3) | (buff[c + 1] << 8*2) | (buff[c + 2] << 8) | (buff[c + 3]);
}

float NetworkSystem::readFloat(const std::vector<uint8_t> &buff, size_t c)
{
    return (buff[c] << 8*3) | (buff[c + 1] << 8*2) | (buff[c + 2] << 8) | (buff[c + 3]);
}

}
