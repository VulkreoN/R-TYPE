/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#include "GameSystem.hpp"
#include "Scene.hpp"
#include "Event.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "CollideSystem.hpp"
#include "Text.hpp"
#include "Projectiles.hpp"
#include "Nono.hpp"
#include "Core.hpp"

namespace R_TYPE {

    sf::FloatRect GameSystem::rectWindow;
    int GameSystem::nbrBasicShoot;
    int GameSystem::nbrTurretShoot;
    int GameSystem::nbrRocketShoot;
    int GameSystem::nbrLaserShoot;
    int GameSystem::nbrLaserBoucleShoot;

    GameSystem::GameSystem()
    {
        std::cout << "Game System create" << std::endl;
    }

    GameSystem::~GameSystem()
    {
    }

    void GameSystem::init(SceneManager &sceneManager)
    {
        std::cout << "Game System init" << std::endl;
        sceneManager.addScene(createSceneTest(), SceneManager::SceneType::GAME);
        sceneManager.addScene(createMainMenu(), SceneManager::SceneType::MAIN_MENU);
        sceneManager.addScene(createOptionMenu(), SceneManager::SceneType::OPTION);
        sceneManager.addScene(createPauseMenu(), SceneManager::SceneType::PAUSE);
        sceneManager.addScene(createFirstLevel(), SceneManager::SceneType::LEVEL1);
        sceneManager.addScene(createSceneLose(), SceneManager::SceneType::LOSE);
        sceneManager.addScene(createSceneWin(), SceneManager::SceneType::WIN);
        sceneManager.setCurrentScene(SceneManager::SceneType::MAIN_MENU);
        nbrBasicShoot = 0;
        nbrTurretShoot = 0;
        nbrRocketShoot = 0;
    }

    void GameSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (Core::getIsServeur() == false)
            updateClient(sceneManager, deltaTime);
        else
           updateServeur(sceneManager, deltaTime);
    }

    void GameSystem::updateServeur(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            updateRectWindow();
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                auto projectile = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);

                if (pos->getPosition().y + velocity->getVelocity().y * deltaTime < 0)
                    projectile->setIsActive(false);
                else {
                    pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                    pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
                }
                if (projectile->getType() == Projectiles::Type::PRE_ROCKET && pos->getPosition().y < 100) {
                    velocity->setX(Ennemy::getVelocityTarget(Ennemy::getDistance(sceneManager, pos->getPosition())).getVelocity().x); 
                    velocity->setY(Ennemy::getVelocityTarget(Ennemy::getDistance(sceneManager, pos->getPosition())).getVelocity().y);
                    projectile->setSpriteAngle(Ennemy::getDistance(sceneManager, pos->getPosition()), e);
                    projectile->setType(Projectiles::Type::ROCKET);
                }
                if (pos->getPosition().x < rectWindow.left || pos->getPosition().x > rectWindow.left + 270) {
                    projectile->setIsActive(false);
                }
                if (projectile->getTimeSend() > 4) {
                    if (projectile->getType() == Projectiles::Type::BASIC && projectile->shootByPlayer()) {
                        setNbrBasicShoot(getNbrBasicShoot() - 1);
                    } else if (projectile->getType() == Projectiles::Type::TURRET) {
                        setNbrTurretShoot(getNbrTurretShoot() - 1);
                    } else if (projectile->getType() == Projectiles::Type::ROCKET) {
                        setNbrRocketShoot(getNbrRocketShoot() - 1);
                    } else if (projectile->getType() == Projectiles::Type::LASER) {
                        setNbrLaserShoot(getNbrLaserShoot() - 1);
                    } else if (projectile->getType() == Projectiles::Type::LASER_BOUCLE)
                        GameSystem::setNbrLaserBoucleShoot(GameSystem::getNbrLaserBoucleShoot() - 1);
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }

            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
                auto position = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                if (player->isAlive() == false) {
                    sceneManager.setCurrentScene(SceneManager::SceneType::LOSE);
                }

                Position moved(0,0);
                moved.setX(position->getPosition().x + velocity->getVelocity().x * deltaTime);
                moved.setY(position->getPosition().y + velocity->getVelocity().y * deltaTime);

                if (CollideSystem::canMove(moved, sceneManager, velocity->getVelocity())) {
                    position->setX(moved.getPosition().x);
                    position->setY(moved.getPosition().y);
                }
                if (player->getNono() == true) {
                    updateNono(sceneManager, deltaTime);
                }
                if (player->hasBonus(Bonus::BonusType::NONO_LE_ROBOT) && player->getNono() == false) {
                    player->setBonus(Bonus::BonusType::NONO_LE_ROBOT, false);
                    player->setNono(true);
                    std::shared_ptr<Entity> entity = createNono(2, *position);
                    sceneManager.getCurrentScene().addEntity(entity);
                }
            }
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);

                if (pos->getPosition().x > rectWindow.left - 30 && pos->getPosition().x < rectWindow.left + 300) {
                    ennemy->launchScript(sceneManager, e, rectWindow.left);
                    pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                    pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
                }

                if (ennemy->getTimeSend() > 4) {
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::BONUS]) {
                auto bonus = Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]);

                if (bonus->getTimeSend() > 4 && bonus->getActive() == false) {
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
                auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);

                if (nono->getTimeSend() > 4 && nono->isAlive == false) {
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }
        }
    }

    void GameSystem::updateClient(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
                auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
                if (player->isAlive() == false)
                    sceneManager.setCurrentScene(SceneManager::SceneType::LOSE);
            }

            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                auto proj = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);

                if (proj->getIsActive() == false) {
                    if (proj->getType() == Projectiles::Type::BASIC && proj->shootByPlayer()) {
                        GameSystem::setNbrBasicShoot(GameSystem::getNbrBasicShoot() - 1);
                    } else if (proj->getType() == Projectiles::Type::TURRET) {
                        GameSystem::setNbrTurretShoot(GameSystem::getNbrTurretShoot() - 1);
                    } else if (proj->getType() == Projectiles::Type::ROCKET)
                        GameSystem::setNbrRocketShoot(GameSystem::getNbrRocketShoot() - 1);
                    else if (proj->getType() == Projectiles::Type::LASER)
                        GameSystem::setNbrLaserShoot(GameSystem::getNbrLaserShoot() - 1);
                    else if (proj->getType() == Projectiles::Type::LASER_BOUCLE)
                        GameSystem::setNbrLaserBoucleShoot(GameSystem::getNbrLaserBoucleShoot() - 1);
                    else if (proj->getType() == Projectiles::Type::BOSS)
                        GameSystem::setNbrBossShoot(GameSystem::getNbrBossShoot() - 1);
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::BONUS]) {
                auto bonus = Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]);

                if (bonus->getActive() == false) {
                    sceneManager.getCurrentScene().removeEntity(e);
                    break;
                }
            }
        }
    }

    void GameSystem::updateNono(SceneManager &sceneManager, uint64_t deltaTime)
    {
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
            if (nono->isSnap == false) {
                velocity->setX(nono->getVelocityTarget(nono->getDistance(sceneManager, pos->getPosition())).getVelocity().x);
                velocity->setY(nono->getVelocityTarget(nono->getDistance(sceneManager, pos->getPosition())).getVelocity().y);
                pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
            } else if (nono->isSnap == true) {
                pos->setX(nono->getPosPlayer()->getPosition().x + 33);
                if (nono->getUpgrade() == 0)
                    pos->setY(nono->getPosPlayer()->getPosition().y + 5);
                else if (nono->getUpgrade() == 1)
                    pos->setY(nono->getPosPlayer()->getPosition().y + 2);
                else if (nono->getUpgrade() == 2)
                    pos->setY(nono->getPosPlayer()->getPosition().y - 2);
            }
        }
    }
 
    void GameSystem::destroy()
    {
        std::cout << "Game System destroyed" << std::endl;
    }

    std::shared_ptr<Entity> GameSystem::createNono(int name, Position pos)
    {
        int posX = pos.getPosition().x;
        int posY = pos.getPosition().y;
        std::shared_ptr<Entity> entity = createSprite(800, name, posX - 100, posY, sf::IntRect(276, 35, 24, 18));
        auto sprite = Component::castComponent<Sprite>((*entity)[IComponent::Type::SPRITE]);
        sprite->getSprite().setScale(0.7, 0.7);
        std::shared_ptr<Nono> comp = std::make_shared<Nono>();
        comp->setState(Animation::State::LV1);
        std::shared_ptr<Animation> anim_lv1 = std::make_shared<Animation>(Animation::State::LV1, sprite->getRect(), 0, 0, 6, true, 276, 35);
        std::shared_ptr<Animation> anim_lv2 = std::make_shared<Animation>(Animation::State::LV2, sprite->getRect(), 0, 0, 6, true, 120, 69);
        std::shared_ptr<Animation> anim_lv3 = std::make_shared<Animation>(Animation::State::LV3, sprite->getRect(), 0, 0, 4, true, 170, 342);

        std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>(0, 0);

        entity->addComponent(velocity)
            .addComponent(comp)
            .addComponent(anim_lv1)
            .addComponent(anim_lv2)
            .addComponent(anim_lv3);

        return entity;
    }

    std::shared_ptr<Entity> GameSystem::createSprite(int id, int name, int posX, int posY, sf::IntRect rect)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(name, *component2, 0, rect);

        entity->addComponent(component)
                .addComponent(component2);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createBonus(int id, int name, Position pos, Bonus::BonusType type, sf::IntRect rect)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
        std::shared_ptr<Position> component2 = std::make_shared<Position>(pos);
        std::shared_ptr<Sprite> component;
        std::shared_ptr<Bonus> component3 = std::make_shared<Bonus>(type);

        if (type == Bonus::BonusType::UPGRADE)
            rect.left = 60;
        else if (type == Bonus::BonusType::NONO_LE_ROBOT)
            rect.left = 89;
        component = std::make_shared<Sprite>(name, *component2, 0, rect);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createText(int id, std::string text, int posX, int posY, int size)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Text> component = std::make_shared<Text>("font.ttf", text, size, sf::Color::White);

        entity->addComponent(component)
                .addComponent(component2);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createEnnemy(int id, int name, int posX, int posY, float angle, Ennemy::Type type, Bonus::BonusType bonusType)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component;

        std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>(0, 0);
        std::shared_ptr<Ennemy> component3 = std::make_shared<Ennemy>(type);

        if (type == Ennemy::Type::TURRET) {
            if (angle == 0)
                component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(1, 2, 15, 14));
            else
                component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(87, 2, 15, 14));
        } else if (type == Ennemy::Type::JORYDE_ALIEN) {
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(0, 0, 55, 56));
            component->getSprite().setScale(0.8, 0.8);
            std::shared_ptr<Animation> anim_left = std::make_shared<Animation>(Animation::State::LEFT, component->getRect(), 0, 1, 0, false);
            std::shared_ptr<Animation> anim_right = std::make_shared<Animation>(Animation::State::RIGHT, component->getRect(), 0, 2, 0, false);
            std::shared_ptr<Animation> anim_idle = std::make_shared<Animation>(Animation::State::IDLE, component->getRect(), 0, 0, 0, false);
            entity->addComponent(anim_idle)
                    .addComponent(anim_left)
                    .addComponent(anim_right);
        } else if (type == Ennemy::Type::ROBOT_DINO) {
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(0, 0, 33, 26));
            component->getSprite().setScale(0.7, 0.7);
            std::shared_ptr<Animation> anim_left = std::make_shared<Animation>(Animation::State::LEFT, component->getRect(), 0, 0, 5, true);
            std::shared_ptr<Animation> anim_right = std::make_shared<Animation>(Animation::State::RIGHT, component->getRect(), 0, 6, 11, true);
            std::shared_ptr<Animation> anim_idle = std::make_shared<Animation>(Animation::State::IDLE, component->getRect(), 1, 5, 0, false);
            velocity = std::make_shared<Velocity>(-0.03f, 0);
            entity->addComponent(anim_idle)
                    .addComponent(anim_left)
                    .addComponent(anim_right);
        } else if (type == Ennemy::Type::SPATIAL) {
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(0, 0, 33, 36));
            velocity = std::make_shared<Velocity>(0, 0);
            std::shared_ptr<Animation> anim_move = std::make_shared<Animation>(Animation::State::MOVE, component->getRect(), 0, 0, 7, true);
            component3->setState(Animation::State::MOVE);
            entity->addComponent(anim_move);
            component->getSprite().setScale(0.7, 0.7);
        } else if (type == Ennemy::Type::BOSS) {
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(24, 0, 161, 213));
            component3->setState(Animation::State::BORN1);
            std::shared_ptr<Animation> anim_born1 = std::make_shared<Animation>(Animation::State::BORN1, component->getRect(), 1, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born2 = std::make_shared<Animation>(Animation::State::BORN2, component->getRect(), 2, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born3 = std::make_shared<Animation>(Animation::State::BORN3, component->getRect(), 3, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born4 = std::make_shared<Animation>(Animation::State::BORN4, component->getRect(), 4, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born5 = std::make_shared<Animation>(Animation::State::BORN5, component->getRect(), 5, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born6 = std::make_shared<Animation>(Animation::State::BORN6, component->getRect(), 6, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born7 = std::make_shared<Animation>(Animation::State::BORN6, component->getRect(), 7, 0, 0, false, 24);
            std::shared_ptr<Animation> anim_born8 = std::make_shared<Animation>(Animation::State::BORN6, component->getRect(), 8, 0, 0, false, 24);
            component3->setPv(100);

            component->getSprite().setScale(0.9, 0.9);
            entity->addComponent(anim_born1)
                    .addComponent(anim_born2)
                    .addComponent(anim_born3)
                    .addComponent(anim_born4)
                    .addComponent(anim_born5)
                    .addComponent(anim_born6)
                    .addComponent(anim_born7)
                    .addComponent(anim_born8);
        }
        component3->setLoot(bonusType);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3)
                .addComponent(velocity);
        return(entity);
    }

    std::vector<std::shared_ptr<IEntity>> GameSystem::createWavesEnnemy(int first_id, int name, int posX, int posY, float angle, Ennemy::Type type)
    {
        std::vector<std::shared_ptr<IEntity>> entities;
        for (int i = 0; i < 5; i++) {
            entities.push_back(createEnnemy(first_id + i, name, posX, posY, angle, type));
            posX += 10;
        }
        return(entities);
    }

    std::shared_ptr<Entity> GameSystem::createProjectiles(int id, int name, Position pos, Velocity velocity, bool byPlayer, sf::IntRect rect)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
        std::shared_ptr<Position> component2 = std::make_shared<Position>(pos);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(name, *component2, 0, rect);
        std::shared_ptr<Projectiles> component3 = std::make_shared<Projectiles>(byPlayer);
        std::shared_ptr<Velocity> component4 = std::make_shared<Velocity>(velocity);

        if (rect.left == 37)
            component3->setType(Projectiles::Type::LASER_BOUCLE);
        if (name == 10) 
            component3->setType(Projectiles::Type::PRE_ROCKET);
        else if (id == 6010)
            component3->setType(Projectiles::Type::CHARGED);
        else if (id >= 6011 && id <= 6019)
            component3->setType(Projectiles::Type::BASIC);
        else if (id >= 6021 && id <= 6029)
            component3->setType(Projectiles::Type::TURRET);
        else if (id >= 6046 && id <= 6055)
            component3->setType(Projectiles::Type::LASER);
        else if (id >= 6056 && id <= 6065)
            component3->setType(Projectiles::Type::LASER_BOUCLE);
        else if (id >= 6066 && id <= 6076)
            component3->setType(Projectiles::Type::BOSS); 
        
        component->getSprite().setScale(0.7, 0.7);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3)
                .addComponent(component4);
        return (entity);
    }

    std::shared_ptr<Entity> GameSystem::createPlayer(int id, int name, int posX, int posY)
    {
        std::shared_ptr<Entity> player_e = std::make_shared<Entity>(id);
        std::shared_ptr<Position> player_pos = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Player> player = std::make_shared<Player>(*player_pos);
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(name, *player_pos, 0, sf::IntRect(67, 3 + (17 * (id - 1)), 33, 15));
        std::shared_ptr<Event> event_p = std::make_shared<Event>();
        std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>(0,0);
        std::shared_ptr<Animation> anim_idle = std::make_shared<Animation>(Animation::State::IDLE, sprite->getRect(), 0, 2, 0, false);
        std::shared_ptr<Animation> anim_up_pressed = std::make_shared<Animation>(Animation::State::UP_PRESS, sprite->getRect(), 0, 3, 0, false);
        std::shared_ptr<Animation> anim_down_down = std::make_shared<Animation>(Animation::State::DOWN_DOWN, sprite->getRect(), 0, 0, 0, false);
        std::shared_ptr<Animation> anim_up_down = std::make_shared<Animation>(Animation::State::DOWN_PRESS, sprite->getRect(), 0, 1, 0, false);
        std::shared_ptr<Animation> anim_down_pressed = std::make_shared<Animation>(Animation::State::UP_DOWN, sprite->getRect(), 0, 4, 0, false);


        player_e->addComponent(player)
            .addComponent(velocity)
            .addComponent(sprite)
            .addComponent(player_pos)
            .addComponent(anim_idle)
            .addComponent(anim_up_pressed)
            .addComponent(anim_down_down)
            .addComponent(anim_up_down)
            .addComponent(anim_down_pressed);

        ButtonCallbacks pause (
            [](SceneManager &sceneManager) {
                sceneManager.setCurrentScene(SceneManager::SceneType::PAUSE);
            },
            [](SceneManager &) {},
            [](SceneManager &) {},
            [](SceneManager &) {}
        );

        ButtonCallbacks up (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);
                player->setState(Animation::State::UP_PRESS);
                velocity->setY(-0.05f);
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp_p);
                player->setState(Animation::State::IDLE);
                velocity->setY(0);
            },
            [player_e](SceneManager &) {
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp_p);
                player->setState(Animation::State::UP_DOWN);
            },
            [](SceneManager &) {});

        ButtonCallbacks left (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);

                velocity->setX(-0.05f - (0.01 * player->getSpeed()));
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                velocity->setX(0);
            },
            [](SceneManager &) {},
            [](SceneManager &) {});

        ButtonCallbacks down (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);
                player->setState(Animation::State::DOWN_PRESS);
                velocity->setY(0.05f);
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp_p);

                player->setState(Animation::State::IDLE);
                velocity->setY(0);
            },
            [player_e](SceneManager &) {
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp_p);
                player->setState(Animation::State::DOWN_DOWN); 
            },
            [](SceneManager &) {});

        ButtonCallbacks right (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);

                velocity->setX(0.05f + (0.01 * player->getSpeed()));
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                velocity->setX(0);
            },
            [](SceneManager &) {},
            [](SceneManager &) {});

        ButtonCallbacks shoot (
            [](SceneManager &) {},
            [player_e](SceneManager &scene) {
                auto comp = (*player_e)[IComponent::Type::POSITION];
                auto compo = (*player_e)[IComponent::Type::PLAYER];
                auto pos = Component::castComponent<Position>(comp);
                auto player = Component::castComponent<Player>(compo);

                if (player->clock.getElapsedTime().asSeconds() > 1) {
                    std::shared_ptr<Entity> shoot = GameSystem::createProjectiles
                        (6010, 1, Position(pos->getPosition().x + 32, pos->getPosition().y + 5), 
                        Velocity(0.5f, 0), true, sf::IntRect(233, 120, 31, 11));
                    auto comp = (*shoot)[IComponent::Type::PROJECTILES];
                    auto projectiles = Component::castComponent<Projectiles>(comp);
                    projectiles->setType(Projectiles::Type::CHARGED);
                    scene.getCurrentScene().addEntity(shoot);
                } else {
                    if (player->getLevelNono() >= 1 && player->getNono()) {
                        std::shared_ptr<Entity> shoot2 = GameSystem::createProjectiles
                            (6046 + nbrLaserShoot, 2, Position(pos->getPosition().x + 32, pos->getPosition().y - 5), 
                            Velocity(0.25f, -0.25f), true, sf::IntRect(208, 183, 15, 17));
                        nbrLaserShoot++;
                        std::shared_ptr<Entity> shoot3 = GameSystem::createProjectiles
                            (6046 + nbrLaserShoot, 2, Position(pos->getPosition().x + 32, pos->getPosition().y + 5), 
                            Velocity(0.25f, 0.25f), true, sf::IntRect(242, 183, 15, 17));
                        scene.getCurrentScene().addEntity(shoot2);
                        scene.getCurrentScene().addEntity(shoot3);
                        nbrLaserShoot++;
                    }
                    if (player->getLevelNono() == 2 && player->getNono()) {
                        std::shared_ptr<Entity> shoot2 = GameSystem::createProjectiles
                            (6056 + nbrLaserBoucleShoot, 2, Position(pos->getPosition().x + 32, pos->getPosition().y - 5), 
                            Velocity(0.3f, 0), true, sf::IntRect(37, 470, 63, 31));
                        nbrLaserBoucleShoot++;
                        scene.getCurrentScene().addEntity(shoot2);
                        return;
                    } else {
                        std::shared_ptr<Entity> shoot = GameSystem::createProjectiles
                        (6011 + GameSystem::getNbrBasicShoot(), 1, Position(pos->getPosition().x + 32, pos->getPosition().y + 5), 
                        Velocity(0.5f, 0), true, sf::IntRect(249, 90, 15, 3));
                        GameSystem::setNbrBasicShoot(GameSystem::getNbrBasicShoot() + 1);
                        scene.getCurrentScene().addEntity(shoot);
                    }
                }
            },
            [](SceneManager &) {
                // here animation of charging
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp);

                player->clock.restart();
            });

        event_p->addKeyboardEvent(sf::Keyboard::Z, up);
        event_p->addKeyboardEvent(sf::Keyboard::Q, left);
        event_p->addKeyboardEvent(sf::Keyboard::S, down);
        event_p->addKeyboardEvent(sf::Keyboard::D, right);
        event_p->addKeyboardEvent(sf::Keyboard::Space, shoot);
        event_p->addKeyboardEvent(sf::Keyboard::Escape, pause);

        player_e->addComponent(event_p);
        return (player_e);
    }

    void GameSystem::createButtonEvent(std::shared_ptr<Entity> &entity, SceneManager::SceneType goTo, sf::Vector2i click)
    {
        MouseCallback mouseCallbacks(
            [entity, goTo, click](SceneManager &sceneManager, sf::Vector2i mousePosition) {
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);

                if (mousePosition.x > pos->getPosition().x && mousePosition.x < pos->getPosition().x + click.x &&
                    mousePosition.y > pos->getPosition().y && mousePosition.y < pos->getPosition().y + click.y) {
                        if (goTo != SceneManager::SceneType::NONE)
                            sceneManager.setCurrentScene(goTo);
                        else
                            sceneManager.setShouldClose(true);
                }
            },
            [](SceneManager &, sf::Vector2i) {});

        std::shared_ptr<Event> eventListener = std::make_shared<Event>();

        eventListener->addMouseEvent(sf::Mouse::Button::Left, mouseCallbacks);
        entity->addComponent(eventListener);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createMainMenu()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createMainMenu, this));
        std::shared_ptr<Entity> entity = createSprite(410, 45, 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite(411, 50, 350, 350);
        std::shared_ptr<Entity> entity3 = createSprite(412, 51, 350, 410);
        std::shared_ptr<Entity> entity4 = createSprite(413, 52, 120, 289);

        createButtonEvent(entity4, SceneManager::SceneType::LEVEL1, sf::Vector2i(230, 240));
        createButtonEvent(entity3, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::OPTION, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity4)
              .addEntity(entity3)
              .addEntity(entity2);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createOptionMenu()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createOptionMenu, this));
        std::shared_ptr<Entity> entity = createSprite(415, 45, 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite(416, 46, 230, 500);
        std::shared_ptr<Entity> entity3 = createText(417, "OPTION", 350, 250, 50);

        createButtonEvent(entity2, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity2)
              .addEntity(entity3);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createPauseMenu()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createOptionMenu, this));
        std::shared_ptr<Entity> entity = createSprite(420, 47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(421, 46, 230, 400);
        std::shared_ptr<Entity> entity3 = createText(422, "PAUSE", 350, 25, 50);

        createButtonEvent(entity, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::LEVEL1, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity2)
              .addEntity(entity3);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneTest()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneTest, this));
        std::shared_ptr<Entity> player = createPlayer(1, 42, 50, 100);
        std::shared_ptr<Entity> tower2 = createEnnemy(120, 10, 53, 150, 0.f, Ennemy::Type::ROBOT_DINO);
        std::shared_ptr<Entity> tower3 = createEnnemy(121, 5, 183, 50, 0.f, Ennemy::Type::SPATIAL);

        scene->addEntity(player)
              .addEntity(tower3)
              .addEntity(tower2);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createFirstLevel()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createFirstLevel, this));
        std::shared_ptr<Entity> top_wall = createSprite(400, 48, 100, 0);
        std::shared_ptr<Entity> bottom_wall = createSprite(401, 49, 100, 127);
        std::shared_ptr<Entity> tower1 = createEnnemy(50, 12, 333, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower2 = createEnnemy(51, 12, 385, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower3 = createEnnemy(52, 12, 428, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower4 = createEnnemy(53, 12, 529, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower5 = createEnnemy(54, 12, 573, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower6 = createEnnemy(55, 12, 720, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower7 = createEnnemy(56, 12, 772, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower8 = createEnnemy(57, 12, 823, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower9 = createEnnemy(58, 12, 702, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower10 = createEnnemy(59, 12, 754, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower11 = createEnnemy(60, 12, 806, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower12 = createEnnemy(61, 12, 145, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower13 = createEnnemy(62, 12, 957, 17, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower14 = createEnnemy(63, 12, 1400, 17, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower15 = createEnnemy(64, 12, 1380, 186, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower16 = createEnnemy(65, 12, 1555, 155, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower17 = createEnnemy(66, 12, 1573, 50, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower18 = createEnnemy(67, 12, 1635, 50, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower19 = createEnnemy(68, 12, 1618, 155, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower20 = createEnnemy(69, 12, 1681, 155, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower21 = createEnnemy(70, 12, 1700, 50, 180.f, Ennemy::Type::TURRET);


        std::shared_ptr<Entity> joryde1 = createEnnemy(71, 9, 183, 50, 0.f, Ennemy::Type::JORYDE_ALIEN, Bonus::BonusType::NONO_LE_ROBOT);
        std::shared_ptr<Entity> joryde2 = createEnnemy(72, 9, 900, 50, 0.f, Ennemy::Type::JORYDE_ALIEN);
        std::shared_ptr<Entity> joryde3 = createEnnemy(73, 9, 600, 50, 0.f, Ennemy::Type::JORYDE_ALIEN, Bonus::BonusType::NONO_LE_ROBOT);
        std::shared_ptr<Entity> joryde4 = createEnnemy(74, 9, 1450, 90, 0.f, Ennemy::Type::JORYDE_ALIEN);
        std::shared_ptr<Entity> joryde5 = createEnnemy(75, 9, 1780, 90, 0.f, Ennemy::Type::JORYDE_ALIEN);

        std::shared_ptr<Entity> dino1 = createEnnemy(76, 10, 345, 179, 0.f, Ennemy::Type::ROBOT_DINO, Bonus::BonusType::NONO_LE_ROBOT);
        std::shared_ptr<Entity> dino2 = createEnnemy(77, 10, 560, 179, 0.f, Ennemy::Type::ROBOT_DINO);
        std::shared_ptr<Entity> dino3 = createEnnemy(78, 10, 900, 180, 0.f, Ennemy::Type::ROBOT_DINO);
        std::shared_ptr<Entity> dino4 = createEnnemy(79, 10, 1158, 180, 0.f, Ennemy::Type::ROBOT_DINO);

        std::vector<std::shared_ptr<IEntity>> spatial1 = createWavesEnnemy(80, 5, 300, 102, 0.f, Ennemy::Type::SPATIAL);
        std::vector<std::shared_ptr<IEntity>> spatial2 = createWavesEnnemy(85, 5, 700, 102, 0.f, Ennemy::Type::SPATIAL);
        std::vector<std::shared_ptr<IEntity>> spatial3 = createWavesEnnemy(90, 5, 1200, 122, 0.f, Ennemy::Type::SPATIAL);
        std::vector<std::shared_ptr<IEntity>> spatial4 = createWavesEnnemy(95, 5, 1200, 102, 0.f, Ennemy::Type::SPATIAL);

        std::shared_ptr<Entity> boss = createEnnemy(101, 30, 2022, 6, 0.f, Ennemy::Type::BOSS);

        scene->addEntity(top_wall)
                .addEntity(bottom_wall)
                .addEntity(tower1)
                .addEntity(tower2)
                .addEntity(tower3)
                .addEntity(tower4)
                .addEntity(tower5)
                .addEntity(tower6)
                .addEntity(tower7)
                .addEntity(tower8)
                .addEntity(tower9)
                .addEntity(tower10)
                .addEntity(tower11)
                .addEntity(tower12)
                .addEntity(tower13)
                .addEntity(tower14)
                .addEntity(tower15)
                .addEntity(tower16)
                .addEntity(tower17)
                .addEntity(tower18)
                .addEntity(tower19)
                .addEntity(tower20)
                .addEntity(tower21)
                .addEntity(dino1)
                .addEntity(dino2)
                .addEntity(dino3)
                .addEntity(dino4)
                .addEntity(joryde1)
                .addEntity(joryde2)
                .addEntity(joryde3)
                .addEntity(joryde4)
                .addEntity(joryde5)
                .addEntities(spatial1)
                .addEntities(spatial2)
                .addEntities(spatial3)
                .addEntities(spatial4)
                .addEntity(boss);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneLose()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneLose, this));
        std::shared_ptr<Entity> background = createSprite(429, 57, 0, 0);
        std::shared_ptr<Entity> entity = createText(430, "You Lose", 350, 25, 50);
        std::shared_ptr<Entity> entity1 = createSprite(431, 47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(432, 51, 230, 400);

        createButtonEvent(entity1, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));

        scene->addEntity(background)
                .addEntity(entity)
                .addEntity(entity1)
                .addEntity(entity2);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneWin()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneWin, this));
        std::shared_ptr<Entity> background = createSprite(439, 57, 0, 0);
        std::shared_ptr<Entity> entity = createText(440, "You Win", 350, 25, 50);
        std::shared_ptr<Entity> entity1 = createSprite(441, 47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(442, 51, 230, 400);

        createButtonEvent(entity1, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));

        scene->addEntity(background)
              .addEntity(entity)
              .addEntity(entity1)
              .addEntity(entity2);
        return (scene);
    }

    void GameSystem::updateRectWindow()
    {
        // a remettre a 0.25f
        if (rectWindow.left < 1925)
            rectWindow.left += 0.75f;
    }
}
