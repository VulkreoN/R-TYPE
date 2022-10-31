/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#include "Position.hpp"
#include "Player.hpp"
#include "ServerSystem.hpp"
#include "network/protocol.h"

namespace R_TYPE {

ServerSystem::ServerSystem(size_t port) : NetworkSystem(port)
{
    std::cout << "Server Network System created" << std::endl;
    _broadcast_cooldown = 0;
}

ServerSystem::~ServerSystem()
{
}

void ServerSystem::init(SceneManager &/*manager*/)
{
    std::cout << "Server Network System initiating" << std::endl;
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
}

void ServerSystem::update(SceneManager &manager, uint64_t deltaTime)
{
    _broadcast_cooldown += deltaTime;
    if (_broadcast_cooldown >= NETWORK_BROADCAST_FREQUENCY) {
        _broadcast_cooldown = 0;
        broadcast(manager);
    }
}

void ServerSystem::destroy()
{
    std::cout << "Network System destroyed" << std::endl;
}

void ServerSystem::handle_incomming_message()
{
    bool new_client = true;

    for (size_t i = 0; i < _connections.size(); i++)
        if (_connections[i]->get_endpoint() == _edp_buff)
            new_client = false;
    if (new_client)
        _connections.push_back(std::make_unique<Connection> (_edp_buff, _connections.size() + 1));
    // here, handle the recienved message stored in _buffer
    clientScene = static_cast<SceneManager::SceneType>((int)_buffer[sizeof(protocol::Header)]);
}

void ServerSystem::broadcast(SceneManager &manager)
{
    char buff[1024];

    manager.setCurrentScene(clientScene);
    for (int i = 0; i < 1024; buff[i] = '\0', i++);
    if (true /* not game start */) {
        switch (manager.getCurrentSceneType()) {
            case SceneManager::SceneType::LEVEL1:
                create_game_info_msg(buff, manager);
                break;
            default :
                buff[0] = protocol::Header::PING;
                break;
        }
        for (std::unique_ptr<Connection> &con : _connections) {
            _socket.send_to(asio::buffer(buff), con->get_endpoint());
        }
    } else {
        for (std::unique_ptr<Connection> &con : _connections) {
            create_start_game_msg(buff, con);
            _socket.send_to(asio::buffer(buff), con->get_endpoint());
        }
    }
}

void ServerSystem::create_start_game_msg(char *buff, std::unique_ptr<Connection> &connection)
{
    buff[0] = protocol::Header::START_GAME;
    buff[sizeof(protocol::Header)] = (size_t)connection->get_id();
    buff[sizeof(protocol::Header) + sizeof(size_t)] = (size_t)_connections.size();
    buff[sizeof(protocol::Header) + 2 * sizeof(size_t)] = '\0';
}

void ServerSystem::create_game_info_msg(char *buff, SceneManager &manager)
{
    size_t c = 0;

    buff[c] = protocol::Header::GAME_INFO;
    c += sizeof(protocol::Header);
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
        auto comp = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
        if (c + sizeof(size_t) + sizeof(float) * 2 + sizeof(uint8_t) * 2) {
            buff[c] = (uint8_t)1;
            c += sizeof(uint8_t);
            buff[c] = comp->getPosition().x;
            c += sizeof(float);
            buff[c] = comp->getPosition().y;
            c += sizeof(float);
            buff[c] = (size_t)1; // to change, this is the ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)1; // to change, this is status
            c += sizeof(uint8_t);
        }
    }
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
        if (c + sizeof(size_t) + sizeof(float) * 2 + sizeof(uint8_t) * 2) {
            buff[c] = (uint8_t)1;
            c += sizeof(uint8_t);
            buff[c] = (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->getPosition().x;
            c += sizeof(float);
            buff[c] = (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->getPosition().y;
            c += sizeof(float);
            buff[c] = (size_t)5; // to change, this is the ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)1; // to change, this is status
            c += sizeof(uint8_t);
        }
    }
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
        if (c + sizeof(size_t) + sizeof(float) * 2 + sizeof(uint8_t) * 2) {
            buff[c] = (uint8_t)1;
            c += sizeof(uint8_t);
            buff[c] = (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->getPosition().x;
            c += sizeof(float);
            buff[c] = (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->getPosition().y;
            c += sizeof(float);
            buff[c] = (size_t)7; // to change, this is the ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)1; // to change, this is status
            c += sizeof(uint8_t);
        }
    }
}

}
