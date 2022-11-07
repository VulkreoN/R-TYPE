/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#include "GraphicSystem.hpp"
#include "ClientSystem.hpp"

namespace R_TYPE {

ClientSystem::ClientSystem(std::string ip, size_t port) : _server_endpoint(asio::ip::make_address(ip), port)
{
    std::cout << "Client Network System created" << std::endl;
    graphicSystem = std::make_unique<GraphicSystem>(std::unique_ptr<ClientSystem>(this));
}

ClientSystem::~ClientSystem()
{
}

void ClientSystem::init(SceneManager &manager)
{
    std::cout << "Client Network System initiating" << std::endl;
    _socket.open(asio::ip::udp::v4());
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
    graphicSystem->init(manager);
}

void ClientSystem::update(SceneManager &manager, uint64_t deltaTime)
{
    _ping_cooldown += deltaTime;
    if (_ping_cooldown >= NETWORK_PING_FREQUENCY) {
        _ping_cooldown = 0;
        broadcast(manager);
    }
    graphicSystem->update(manager, deltaTime);
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
        case SceneManager::SceneType::LEVEL1:
            buff[0] = protocol::Header::PLAYER_ACTION;
            break;
        default :
            buff[0] = protocol::Header::PING;
            break;
    }
    _socket.send_to(asio::buffer(buff), _server_endpoint);
}

void ClientSystem::sendEvent(int button, NetworkSystem::ButtonState state, bool isKey)
{
    char buff[1024];
    size_t c = 0;

    buff[c] = protocol::Header::EVENT;
    c += sizeof(protocol::Header);
    buff[c] = isKey;
    c += sizeof(bool);
    buff[c] = button;
    c += sizeof(int);
    buff[c] = static_cast<uint8_t>(state);
    _socket.send_to(asio::buffer(buff), _server_endpoint);
}

}
