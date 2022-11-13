/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#include "Position.hpp"
#include "Player.hpp"
#include "GraphicSystem.hpp"
#include "ClientSystem.hpp"
#include "GameSystem.hpp"
#include "Projectiles.hpp"

namespace R_TYPE {

ClientSystem::ClientSystem(std::string ip, size_t port) : _server_endpoint(asio::ip::make_address(ip), port)
{
    std::cout << "Client Network System created" << std::endl;
    _id = 0;
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
    size_t i = 0;
    _ping_cooldown += deltaTime;
    if (_ping_cooldown >= NETWORK_PING_FREQUENCY) {
        _ping_cooldown = 0;
        broadcast(manager);
    }
    if (_message_queue.size() != 0) {
        for (auto msg : _message_queue) {
            if ((protocol::Header)msg[0] == protocol::Header::GAME_INFO) {
                for (i = sizeof(protocol::Header); readInt(msg, i); i += sizeof(size_t) + sizeof(float) * 3 + sizeof(uint8_t)) {
                    float tags = readInt(msg, i);
                    i += sizeof(float);
                    int id = readInt(msg, i + sizeof(float) * 3);
                    if (id >= 6010 && manager.getCurrentScene().get_by_id(id).size() == 0 && (bool)msg[i + sizeof(float) * 3 + sizeof(size_t)] == true) {
                        createProjectile(manager, id, readFloat(msg, i), readFloat(msg, i + sizeof(float)));
                    }
                    if (manager.getCurrentScene().get_by_id(id).size() == 0 && id > 0 && id < 5) {
                        std::shared_ptr<Entity> player = GameSystem::createPlayer(id, 42, 50, 40 + 20 * id);
                        manager.getCurrentScene().addEntity(player);
                        EventSystem::putCallback(manager, player);
                    } else if (manager.getCurrentScene().get_by_id(id).size() == 0 && id == 800) {
                        std::shared_ptr<Entity> nono = GameSystem::createNono(2, Position(readFloat(msg, i), readFloat(msg, i + sizeof(float))));
                        manager.getCurrentScene().addEntity(nono);
                    } else if (manager.getCurrentScene().get_by_id(id).size() == 0 && id == 300 && (bool)msg[i + sizeof(float) * 3 + sizeof(size_t)] == true) {
                        std::shared_ptr<Entity> bonus = GameSystem::createBonus(id, 56, Position(readFloat(msg, i), readFloat(msg, i + sizeof(float))), 
                        (Bonus::BonusType)readInt(msg, i + sizeof(float) * 2));
                        manager.getCurrentScene().addEntity(bonus);
                    }

                    if ((int)tags == (int)IEntity::Tags::PLAYER) {
                        for (auto &e : manager.getCurrentScene().get_by_id(id)) {
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setX(readFloat(msg, i));
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setY(readFloat(msg, i + sizeof(float)));
                            (Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]))->setState((Animation::State)readInt(msg, i + sizeof(float) * 2));
                            (Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]))->setAlive((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)]);
                        }
                    }
                    if (tags == (int)IEntity::Tags::PROJECTILES) {
                        for (auto &e : manager.getCurrentScene().get_by_id(id)) {
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setX(readFloat(msg, i));
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setY(readFloat(msg, i + sizeof(float)));
                            (Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]))->setIsActive((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)]);
                        }
                    }
                    if (tags == (int)IEntity::Tags::ENNEMY) {
                        for (auto &e : manager.getCurrentScene().get_by_id(id)) {
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setX(readFloat(msg, i));
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setY(readFloat(msg, i + sizeof(float)));
                            (Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]))->setState((Animation::State)readInt(msg, i + sizeof(float) * 2));
                            (Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]))->setIsAlive((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)]);
                            //if ((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)] == false)
                            //    manager.getCurrentScene().removeEntity(e);
                        }
                    }
                    if (tags == (int)IEntity::Tags::BONUS) {
                        for (auto &e : manager.getCurrentScene().get_by_id(id)) {
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setX(readFloat(msg, i));
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setY(readFloat(msg, i + sizeof(float)));
                            (Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]))->setType((Bonus::BonusType)msg[i + sizeof(float) * 2]);
                            (Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]))->setActive((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)]);
                        }
                    }
                    if (tags == (int)IEntity::Tags::NONO) {
                        for (auto &e : manager.getCurrentScene().get_by_id(id)) {
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setX(readFloat(msg, i));
                            (Component::castComponent<Position>((*e)[IComponent::Type::POSITION]))->setY(readFloat(msg, i + sizeof(float)));
                            updateNono((Animation::State)readInt(msg, i + sizeof(float) * 2), e);
                            (Component::castComponent<Nono>((*e)[IComponent::Type::NONO]))->setState((Animation::State)readInt(msg, i + sizeof(float) * 2));
                            (Component::castComponent<Nono>((*e)[IComponent::Type::NONO]))->isAlive = ((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)]);
                            if ((bool)msg[i + sizeof(float) * 3 + sizeof(size_t)] == false) {
                                manager.getCurrentScene().removeEntity(e);
                            }
                        }
                    }
                    if (tags == (int)IEntity::Tags::CAMERA) {
                        GraphicSystem::updateCamera(readFloat(msg, i) / 100);
                        if (manager.getCurrentSceneType() != (SceneManager::SceneType)readInt(msg, i + sizeof(float))) {
                            manager.setCurrentScene((SceneManager::SceneType)readInt(msg, i + sizeof(float)));
                        }
                    }
                }
            }
        }
        _message_queue.clear();
    }
    graphicSystem->update(manager, deltaTime);
}

void ClientSystem::updateNono(Animation::State state, std::shared_ptr<IEntity> nono)
{
    auto nonoComponent = Component::castComponent<Nono>((*nono)[IComponent::Type::NONO]);
    auto sprite = Component::castComponent<Sprite>((*nono)[IComponent::Type::SPRITE]);
    auto anims = nono->getFilteredComponents(IComponent::Type::ANIMATION);

    if (state != nonoComponent->getState()) {
        if (state == Animation::State::LV2) {
            sprite->setRect(sf::IntRect(120, 69, 30, 21));
            for (int i = 0; i < anims.size(); i++) {
                auto anim_cast = Component::castComponent<Animation>(anims[i]);
                if (anim_cast->getState() == state) {
                    anim_cast->setRect(sf::IntRect(120, 69, 30, 21));
                }
            }
        } else if (state == Animation::State::LV3) {
            sprite->setRect(sf::IntRect(170, 342, 32, 31));
            for (int i = 0; i < anims.size(); i++) {
                auto anim_cast = Component::castComponent<Animation>(anims[i]);
                if (anim_cast->getState() == state) {
                    anim_cast->setRect(sf::IntRect(170, 342, 32, 31));
                }
            }
        }
    }
}

void ClientSystem::createProjectile(SceneManager &manager, int id, float x, float y)
{
    std::shared_ptr<Entity> proj = std::make_shared<Entity>();

    if (id == 6010)
        proj = GameSystem::createProjectiles(id, 1, Position(x, y), Velocity(0.5f, 0), true, sf::IntRect(233, 120, 31, 11));
    if (id >= 6011 && id <= 6019)
        proj = GameSystem::createProjectiles(id, 1, Position(x, y), Velocity(0.5f, 0), true, sf::IntRect(249, 90, 15, 3));
    else if (id == 6020)
        proj = GameSystem::createProjectiles(id, 9, Position(x, y), Velocity(-0.1f, 0), false, sf::IntRect(18, 59, 15, 15));
    else if (id >= 6021 && id <= 6029) {
        proj = GameSystem::createProjectiles(id, 54, Position(x, y), Velocity(0, 0), 2, sf::IntRect(0, 0, 14, 12));
        GameSystem::setNbrTurretShoot(GameSystem::getNbrTurretShoot() + 1);
    } else if (id >= 6030 && id <= 6045)
        proj = GameSystem::createProjectiles(id, 10, Position(x, y), Velocity(0, 0), false, sf::IntRect(191, 63, 6, 12));
    else if (id >= 6046 && id <= 6055) {
        if (firstLaser) {
            proj = GameSystem::createProjectiles(id, 2, Position(x, y), Velocity(0, 0), false, sf::IntRect(242, 183, 15, 17));
            firstLaser = false;
        } else {
            proj = GameSystem::createProjectiles(id, 2, Position(x, y), Velocity(0, 0), false, sf::IntRect(208, 183, 15, 17));
            firstLaser = true;
        }
        GameSystem::setNbrLaserShoot(GameSystem::getNbrLaserShoot() + 1);
    } else if (id >= 6056 && id <= 6065)
        proj = GameSystem::createProjectiles(id, 2, Position(x, y), Velocity(0, 0), false, sf::IntRect(37, 470, 63, 31));
    manager.getCurrentScene().addEntity(proj);
}

void ClientSystem::destroy()
{
    uint8_t buff[1] = {0};

    buff[0] = protocol::Header::DECONNECT;
    _socket.send_to(asio::buffer(buff), _server_endpoint);
    std::cout << "Network System destroyed" << std::endl;
}

void ClientSystem::handle_incomming_message()
{
    _message_queue.push_back(_buffer);
    // here, handle the recienved message stored in _buffer
    if ((protocol::Header)_buffer[0] == protocol::Header::START_GAME) {
        std::cout << "Starting game, ID: " << (size_t)_buffer[sizeof(protocol::Header)] << " and there are : " << (size_t)_buffer[sizeof(protocol::Header) + sizeof(size_t)] << " players." << std::endl;
        _id = (size_t)_buffer[sizeof(protocol::Header)];
    }
    //if ((protocol::Header)_buffer[0] == protocol::Header::GAME_INFO) {
    //    // std::cout << "Game Info is being sent, here are the entities to display :" << std::endl;
    //    for (size_t i = sizeof(protocol::Header); (uint8_t)_buffer[i]; i += sizeof(size_t) + sizeof(float) * 2 + sizeof(uint8_t)) {
    //        i += sizeof(uint8_t);
    //        // std::cout << "Entity x: " << (float)_buffer[i] << ", y: " << (float)_buffer[i + sizeof(float)] <<
    //        //     ", ID: " << (size_t)_buffer[i + sizeof(float) * 2] << ", status" << (size_t)_buffer[i + sizeof(size_t) + sizeof(float) * 2] << std::endl;
    //    }
    //}
}

void ClientSystem::broadcast(SceneManager &manager)
{
    std::vector<uint8_t> buff;

    buff.assign(MAX_MSG_LENGTH, 0);
    for (int i = 0; i < MAX_MSG_LENGTH; buff[i] = '\0', i++);
    switch (manager.getCurrentSceneType()) {
        case SceneManager::SceneType::GAME:
            create_event_msg(buff);
        case SceneManager::SceneType::LEVEL1:
            buff[0] = protocol::Header::PLAYER_ACTION;
            break;
        default :
            buff[0] = protocol::Header::PING;
            break;
    }
    _socket.send_to(asio::buffer(buff), _server_endpoint);
}

void ClientSystem::create_event_msg(std::vector<uint8_t> &buff)
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

void ClientSystem::sendEvent(int button, NetworkSystem::ButtonState state, bool isKey, int x, int y)
{
    std::vector<uint8_t> buff;
    size_t c = 0;

    buff.assign(16, 0);
    buff[c] = (uint8_t)protocol::Header::EVENT;
    c += sizeof(uint8_t);
    buff[c] = isKey;
    c += sizeof(bool);
    putInt(button, buff, c);
    c += sizeof(int);
    buff[c] = static_cast<uint8_t>(state);
    if (!isKey) {
        c += sizeof(uint8_t);
        putInt(x, buff, c);
        c += sizeof(int);
        putInt(y, buff, c);
    }
    _socket.send_to(asio::buffer(buff, 16), _server_endpoint);
}

}
