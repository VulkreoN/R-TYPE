/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#include "Position.hpp"
#include "Player.hpp"
#include "ServerSystem.hpp"
#include "EventSystem.hpp"
#include "Projectiles.hpp"
#include "GameSystem.hpp"
#include "Ennemy.hpp"
#include "network/protocol.hpp"
#include "Nono.hpp"

namespace R_TYPE {

ServerSystem::ServerSystem(size_t port) : NetworkSystem(port)
{
    std::cout << "Server Network System created" << std::endl;
    _broadcast_cooldown = 0;
    eventSystem = std::make_unique<EventSystem>(std::unique_ptr<NetworkSystem>(this));
}

ServerSystem::~ServerSystem()
{
}

void ServerSystem::init(SceneManager &manager)
{
    std::cout << "Server Network System initiating" << std::endl;
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
    eventSystem->init(manager);
}

void ServerSystem::update(SceneManager &manager, uint64_t deltaTime)
{
    _broadcast_cooldown += deltaTime;
    if (_broadcast_cooldown >= NETWORK_BROADCAST_FREQUENCY) {
        _broadcast_cooldown = 0;
        broadcast(manager);
    }
    if (_player_id_add_queue.size() > 0) {
        for (size_t id : _player_id_add_queue) {
            manager.getScene(SceneManager::SceneType::LEVEL1).addEntity(GameSystem::createPlayer(id, 53, 50, 40 + 20 * id));
        }
        _player_id_add_queue.clear();
    }
    if (_event_queue.size() != 0) {
        for (auto &i : _event_queue) {
            for (auto &e : manager.getCurrentScene().get_by_id(i.first)) {
                auto listener = Component::castComponent<Event>((*e)[IComponent::Type::EVENT]);
                if (listener) {
                    auto call = listener->getKeyboardMap()[static_cast<sf::Keyboard::Key>(i.second.first)];
                    switch (i.second.second) {
                        case NetworkSystem::ButtonState::PRESSED:
                            if (call.pressed)
                                call.pressed(manager);
                            break;
                        case NetworkSystem::ButtonState::DOWN:
                            if (call.down)
                                call.down(manager);
                            break;
                        case NetworkSystem::ButtonState::UP:
                            if (call.up)
                                call.up(manager);
                            break;
                        case NetworkSystem::ButtonState::RELEASED:
                            if (call.released)
                                call.released(manager);
                            break;
                    }
                }
            }
        }
        _event_queue.clear();
    }
    eventSystem->update(manager, deltaTime);
}

void ServerSystem::destroy()
{
    std::cout << "Network System destroyed" << std::endl;
}

void ServerSystem::handle_incomming_message()
{
    bool new_client = true;
    bool isKey = false;
    size_t c = 0;
    size_t id = 0;

    for (size_t i = 0; i < _connections.size(); i++)
        if (_connections[i]->get_endpoint() == _edp_buff) {
            new_client = false;
            id = _connections[i]->get_id();
            if ((protocol::Header)_buffer[0] == protocol::Header::GAME_INFO) {
                std::cout << "Recieving info for player : " << _connections[i]->get_id() << ", new crds : x = " << (float)_buffer[sizeof(protocol::Header)]
                    << ", y = " << (float)_buffer[sizeof(protocol::Header) + sizeof(float)] << std::endl;
            }
        }
    if (new_client && _connections.size() < MAX_NUMBER_OF_CONNECTIONS) {
        _connections.push_back(std::make_unique<Connection> (_edp_buff, _connections.size() + 1));
        _player_id_add_queue.push_back(_connections.back()->get_id());
        id = _connections.back()->get_id();
    }
    if ((protocol::Header)_buffer[c] == protocol::Header::EVENT && id != 0) {
        c += sizeof(uint8_t);
        isKey = (bool)_buffer[c];
        c += sizeof(bool);
        if (isKey) {
            _event_queue.push_back(std::make_pair(id,
            std::make_pair(readInt(_buffer, c), static_cast<NetworkSystem::ButtonState>(_buffer[c + sizeof(int)]))));
            //_keys.push_back(std::make_pair(readInt(_buffer, c), static_cast<NetworkSystem::ButtonState>(_buffer[c + sizeof(int)])));
        } else {
            _mouseButtons.push_back(std::make_pair(readInt(_buffer, c), static_cast<NetworkSystem::ButtonState>(_buffer[c + sizeof(int)])));
            c += sizeof(int);
            c += sizeof(uint8_t);
            _mousePositions.push_back(std::make_pair(readInt(_buffer, c), readInt(_buffer, c + sizeof(int))));
        }
    }
}

void ServerSystem::broadcast(SceneManager &manager)
{
    uint8_t buff[MAX_MSG_LENGTH];

    for (int i = 0; i < MAX_MSG_LENGTH; buff[i] = '\0', i++);
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

void ServerSystem::create_start_game_msg(uint8_t *buff, std::unique_ptr<Connection> &connection)
{
    buff[0] = protocol::Header::START_GAME;
    buff[sizeof(protocol::Header)] = (size_t)connection->get_id();
    buff[sizeof(protocol::Header) + sizeof(size_t)] = (size_t)_connections.size();
    buff[sizeof(protocol::Header) + 2 * sizeof(size_t)] = '\0';
}

void ServerSystem::create_game_info_msg(uint8_t *buff, SceneManager &manager)
{
    size_t c = 0;

    buff[c] = protocol::Header::GAME_INFO;
    c += sizeof(protocol::Header);
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
        auto comp = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
        if (c + sizeof(size_t) + sizeof(float) * 4 + sizeof(uint8_t)) {
            putInt((int)IEntity::Tags::PLAYER, buff, c);
            c += sizeof(float);
            putInt(Component::castComponent<Position>((*e)[IComponent::Type::POSITION])->getPosition().x, buff, c); // entity's X crd
            c += sizeof(float);
            putInt(Component::castComponent<Position>((*e)[IComponent::Type::POSITION])->getPosition().y, buff, c); // entity's Y crd
            c += sizeof(float);
            putInt((int)Component::castComponent<Player>((*e)[IComponent::Type::PLAYER])->getState(), buff, c); // entity's status
            c += sizeof(float);
            putInt(e->get_id(), buff, c); // entity's ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)Component::castComponent<Player>((*e)[IComponent::Type::PLAYER])->isAlive(); // entity's status
            c += sizeof(uint8_t);
        }
    }
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
        if (c + sizeof(size_t) + sizeof(float) * 4 + sizeof(uint8_t)) {
            putInt((int)IEntity::Tags::PROJECTILES, buff, c);
            c += sizeof(float);
            putInt(Component::castComponent<Position>((*e)[IComponent::Type::POSITION])->getPosition().x, buff, c); // entity's X crd
            c += sizeof(float);
             putInt(Component::castComponent<Position>((*e)[IComponent::Type::POSITION])->getPosition().y, buff, c); // entity's Y crd
            c += sizeof(float);
            buff[c] = 0;
            c += sizeof(float);
            putInt(e->get_id(), buff, c); // entity's ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES])->getIsActive(); // entity's status
            c += sizeof(uint8_t);
            if (Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES])->getIsActive() == false)
                Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES])->nextTimeSend();
        }
    }
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
        auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
        if (pos->getPosition().x < GameSystem::getRectWindow().left - 50 || pos->getPosition().x > GameSystem::getRectWindow().left + 300)
            continue;
        if (c + sizeof(size_t) + sizeof(float) * 4 + sizeof(uint8_t)) {
            putInt((int)IEntity::Tags::ENNEMY, buff, c);
            c += sizeof(float);
            putInt(pos->getPosition().x, buff, c); // entity's X crd
            c += sizeof(float);
            putInt(pos->getPosition().y, buff, c); // entity's Y crd
            c += sizeof(float);
            putInt((int)Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY])->getState(), buff, c); // entity's status
            c += sizeof(float);
            putInt(e->get_id(), buff, c); // entity's ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY])->IsAlive(); // to change, entity's status
            c += sizeof(uint8_t);
            if (Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY])->IsAlive() == false)
                Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY])->nextTimeSend();
        }
    }
    for (auto &e : manager.getCurrentScene()[IEntity::Tags::BONUS]) {
        auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
        if (pos->getPosition().x < GameSystem::getRectWindow().left - 50 || pos->getPosition().x > GameSystem::getRectWindow().left + 300)
            continue;
        if (c + sizeof(size_t) + sizeof(float) * 4 + sizeof(uint8_t)) {
            putInt((int)IEntity::Tags::BONUS, buff, c);
            c += sizeof(float);
            putInt(pos->getPosition().x, buff, c); // entity's X crd
            c += sizeof(float);
            putInt(pos->getPosition().y, buff, c); // entity's Y crd
            c += sizeof(float);
            putInt((int)Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS])->getType(), buff, c); // entity's status
            c += sizeof(float);
            putInt(e->get_id(), buff, c); // entity's ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS])->getActive(); // to change, entity's status
            c += sizeof(uint8_t);
            if (Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS])->getActive() == false)
                Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS])->nextTimeSend();
        }
    }

    for (auto &e : manager.getCurrentScene()[IEntity::Tags::NONO]) {
        auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
        if (pos->getPosition().x < GameSystem::getRectWindow().left - 50 || pos->getPosition().x > GameSystem::getRectWindow().left + 300)
            continue;
        if (c + sizeof(size_t) + sizeof(float) * 4 + sizeof(uint8_t)) {
            putInt((int)IEntity::Tags::NONO, buff, c);
            c += sizeof(float);
            putInt(pos->getPosition().x, buff, c); // entity's X crd
            c += sizeof(float);
            putInt(pos->getPosition().y, buff, c); // entity's Y crd
            c += sizeof(float);
            putInt((int)Component::castComponent<Nono>((*e)[IComponent::Type::NONO])->getState(), buff, c); // entity's status
            c += sizeof(float);
            putInt(e->get_id(), buff, c); // entity's ID
            c += sizeof(size_t);
            buff[c] = (uint8_t)Component::castComponent<Nono>((*e)[IComponent::Type::NONO])->isAlive; // to change, entity's status
            c += sizeof(uint8_t);
            if (Component::castComponent<Nono>((*e)[IComponent::Type::NONO])->isAlive == false)
                Component::castComponent<Nono>((*e)[IComponent::Type::NONO])->nextTimeSend();
        }
    }
    putInt((int)IEntity::Tags::CAMERA, buff, c);
    c += sizeof(float);
    // a remettre a 25
    putInt(75, buff, c);
    c += sizeof(float);
}

std::list<std::pair<int, NetworkSystem::ButtonState>> ServerSystem::getKeys() const
{
    return _keys;
}

std::list<std::pair<int, NetworkSystem::ButtonState>> ServerSystem::getMouseButtons() const
{
    return _mouseButtons;
}

std::list<std::pair<int, int>> ServerSystem::getMousePositions() const
{
    return _mousePositions;
}

void ServerSystem::removeKey()
{
    _keys.pop_front();
}

void ServerSystem::removeMouse()
{
    _mouseButtons.pop_front();
    _mousePositions.pop_front();
}

}
