/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#include "ClientSystem.hpp"

namespace R_TYPE {

ClientSystem::ClientSystem(std::string ip, size_t port) : _server_endpoint(asio::ip::make_address(ip), port)
{
    std::cout << "Client Network System created" << std::endl;
    _id = 0;
}

ClientSystem::~ClientSystem()
{
}

void ClientSystem::init(SceneManager &/*manager*/)
{
    std::cout << "Client Network System initiating" << std::endl;
    _socket.open(asio::ip::udp::v4());
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
}

void ClientSystem::update(SceneManager &manager, uint64_t deltaTime)
{
    _ping_cooldown += deltaTime;
    if (_ping_cooldown >= NETWORK_PING_FREQUENCY) {
        _ping_cooldown = 0;
        broadcast(manager);
    }
}

void ClientSystem::destroy()
{
    std::cout << "Network System destroyed" << std::endl;
}

void ClientSystem::handle_incomming_message()
{
    // here, handle the recienved message stored in _buffer
    if ((protocol::Header)_buffer[0] == protocol::Header::START_GAME) {
        std::cout << "Starting game, ID: " << (size_t)_buffer[sizeof(protocol::Header)] << " and there are : " << (size_t)_buffer[sizeof(protocol::Header) + sizeof(size_t)] << " players." << std::endl;
        _id = (size_t)_buffer[sizeof(protocol::Header)];
    }
    if ((protocol::Header)_buffer[0] == protocol::Header::GAME_INFO) {
        std::cout << "Game Info is being sent, here are the entities to display :" << std::endl;
        for (size_t i = sizeof(protocol::Header); (uint8_t)_buffer[i]; i += sizeof(size_t) + sizeof(float) * 2 + sizeof(uint8_t)) {
            i += sizeof(uint8_t);
            std::cout << "Entity x: " << (float)_buffer[i] << ", y: " << (float)_buffer[i + sizeof(float)] <<
                ", ID: " << (size_t)_buffer[i + sizeof(float) * 2] << ", status" << (size_t)_buffer[i + sizeof(size_t) + sizeof(float) * 2] << std::endl;
        }
    }
}

void ClientSystem::broadcast(SceneManager &manager)
{
    char buff[1024];

    for (int i = 0; i < 1024; buff[i] = '\0', i++);
    switch (manager.getCurrentSceneType()) {
        case SceneManager::SceneType::GAME:
            create_event_msg(buff);
            break;
        default :
            buff[0] = protocol::Header::PING;
            break;
    }
    _socket.send_to(asio::buffer(buff), _server_endpoint);
}

void ClientSystem::create_event_msg(char *buff)
{
    int c = 0;

    buff[c] = protocol::Header::GAME_INFO;
    c += sizeof(protocol::Header);
    buff[c] = (float) 25; // x crds of player
    c += sizeof(float);
    buff[c] = (float) 50; // y crds of player
    c += sizeof(float);
    /*
    for (player_projectile in player_projectiles)
        send : x crds, y crds, id, type... etc.
    */
}

}
