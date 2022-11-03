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
#include "Core.hpp"

namespace R_TYPE {
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
        sceneManager.setCurrentScene(SceneManager::SceneType::LEVEL1);
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
        std::cout << "updateServeur GameSystem" << std::endl;
    }

    void GameSystem::updateClient(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                auto projectile = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);

                pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
                if (projectile->getType() == Projectiles::Type::ROCKET && pos->getPosition().y < 100) {
                    velocity->setX(Ennemy::getVelocityTarget(Ennemy::getDistance(sceneManager, pos->getPosition())).getVelocity().x); 
                    velocity->setY(Ennemy::getVelocityTarget(Ennemy::getDistance(sceneManager, pos->getPosition())).getVelocity().y);
                    projectile->setType(Projectiles::Type::BASIC);
                }
            }

            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                // float windowPosX = GraphicSystem::getWindow()->getView().getCenter().x - 135;

                // if (pos->getPosition().x < windowPosX + 270) {
                    pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                    pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
                // }
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
            }

            // delete all projectiles if they are out of the screen
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
                auto proj = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);

                int min = GraphicSystem::getWindow()->getView().getCenter().x - 135;
                int max = GraphicSystem::getWindow()->getView().getCenter().x + 135;

                if (pos->getPosition().x < min || pos->getPosition().x > max) {
                    proj->setIsActive(false);
                }
            }
        }
    }

    void GameSystem::destroy()
    {
        std::cout << "Game System destroyed" << std::endl;
    }

    std::shared_ptr<Entity> GameSystem::createSprite(int name, int posX, int posY)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(name, *component2);

        entity->addComponent(component)
                .addComponent(component2);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createBonus(int name, Position pos, Bonus::BonusType type, sf::IntRect rect)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(pos);
        std::shared_ptr<Sprite> component;
        std::shared_ptr<Bonus> component3 = std::make_shared<Bonus>(type);

        if (type == Bonus::BonusType::DOUBLE)
            rect.left = 32;
        else if (type == Bonus::BonusType::LASER_DIAG)
            rect.left = 60;
        else if (type == Bonus::BonusType::LASER)
            rect.left = 89;
        component = std::make_shared<Sprite>(name, *component2, 0, rect);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createText(std::string text, int posX, int posY, int size)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Text> component = std::make_shared<Text>("font.ttf", text, size, sf::Color::White);

        entity->addComponent(component)
                .addComponent(component2);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createEnnemy(int name, int posX, int posY, float angle, Ennemy::Type type)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component;

        std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>(0, 0);
        std::shared_ptr<Ennemy> component3 = std::make_shared<Ennemy>(type);

        if (type == Ennemy::Type::TURRET) {
            component = std::make_shared<Sprite>(name, *component2, angle);
        } else if (type == Ennemy::Type::JORYDE_ALIEN) {
            component3->setLoot(Bonus::BonusType::SPEED);
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(1, 14, 47, 42));
            component->getSprite().setScale(0.5, 0.5);
        } else if (type == Ennemy::Type::ROBOT_DINO) {
            component3->setLoot(Bonus::BonusType::LASER_DIAG);
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(1, 2, 29, 24));
            component->getSprite().setScale(0.7, 0.7);
            velocity = std::make_shared<Velocity>(-0.03f, 0);
        } else if (type == Ennemy::Type::SPATIAL) {
            component = std::make_shared<Sprite>(name, *component2, angle, sf::IntRect(5, 6, 20, 23));
            velocity = std::make_shared<Velocity>(-0.05f, -0.05f);
            component->getSprite().setScale(0.7, 0.7);
        }

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3)
                .addComponent(velocity);
        return(entity);
    }

    std::vector<std::shared_ptr<IEntity>> GameSystem::createWavesEnnemy(int name, int posX, int posY, float angle, Ennemy::Type type)
    {
        std::vector<std::shared_ptr<IEntity>> entities;
        for (int i = 0; i < 5; i++) {
            entities.push_back(createEnnemy(name, posX, posY, angle, type));
            posX += 10;
        }
        return(entities);
    }

    std::shared_ptr<Entity> GameSystem::createProjectiles(int name, Position pos, Velocity velocity, bool byPlayer, sf::IntRect rect)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(pos);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(name, *component2, 0, rect);
        std::shared_ptr<Projectiles> component3 = std::make_shared<Projectiles>(byPlayer);
        std::shared_ptr<Velocity> component4 = std::make_shared<Velocity>(velocity);

        if (name == 10)
            component3->setType(Projectiles::Type::ROCKET);
        
        component->getSprite().setScale(0.7, 0.7);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3)
                .addComponent(component4);
        return (entity);
    }

    std::shared_ptr<Entity> GameSystem::createPlayer(int name, int posX, int posY)
    {
        std::shared_ptr<Entity> player_e = std::make_shared<Entity>();
        std::shared_ptr<Position> player_pos = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Player> player = std::make_shared<Player>(*player_pos);
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(name, *player_pos, 0, sf::IntRect(66, 0, 32, 12));
        std::shared_ptr<Event> event_p = std::make_shared<Event>();
        std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>(0,0);

        player_e->addComponent(player)
            .addComponent(velocity)
            .addComponent(sprite)
            .addComponent(player_pos);

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

                if (player->hasBonus(Bonus::BonusType::SPEED)) {
                    velocity->setY(-0.07f);
                } else 
                    velocity->setY(-0.05f);
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                velocity->setY(0);
            },
            [](SceneManager &) {},
            [](SceneManager &) {});
            

        ButtonCallbacks left (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);

                if (player->hasBonus(Bonus::BonusType::SPEED) == true)
                    velocity->setX(-0.07f);
                else 
                    velocity->setX(-0.05f);
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

                if (player->hasBonus(Bonus::BonusType::SPEED) == true)
                    velocity->setY(0.07f);
                else 
                    velocity->setY(0.05f);
            },
            [player_e](SceneManager &) {
                auto comp = (*player_e)[IComponent::Type::VELOCITY];
                auto velocity = Component::castComponent<Velocity>(comp);
                velocity->setY(0);
            },
            [](SceneManager &) {},
            [](SceneManager &) {});

        ButtonCallbacks right (
            [player_e](SceneManager &) {
                auto comp_v = (*player_e)[IComponent::Type::VELOCITY];
                auto comp_p = (*player_e)[IComponent::Type::PLAYER];
                auto velocity = Component::castComponent<Velocity>(comp_v);
                auto player = Component::castComponent<Player>(comp_p);

                if (player->hasBonus(Bonus::BonusType::SPEED) == true)
                    velocity->setX(0.07f);
                else 
                    velocity->setX(0.05f);
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
                        (1, Position(pos->getPosition().x + 32, pos->getPosition().y + 5), 
                        Velocity(0.5f, 0), true, sf::IntRect(233, 120, 31, 11));
                    auto comp = (*shoot)[IComponent::Type::PROJECTILES];
                    auto projectiles = Component::castComponent<Projectiles>(comp);
                    projectiles->setType(Projectiles::Type::CHARGED);
                    scene.getCurrentScene().addEntity(shoot);
                } else {
                    std::shared_ptr<Entity> shoot = GameSystem::createProjectiles
                        (1, Position(pos->getPosition().x + 32, pos->getPosition().y + 5), 
                        Velocity(0.5f, 0), true, sf::IntRect(249, 90, 15, 3));
                    if (player->hasBonus(Bonus::BonusType::LASER_DIAG) == true) {
                        std::shared_ptr<Entity> shoot2 = GameSystem::createProjectiles
                            (2, Position(player->getPosition().x + 32, player->getPosition().y - 5), 
                            Velocity(0.25f, -0.25f), true, sf::IntRect(208, 183, 15, 17));
                        std::shared_ptr<Entity> shoot3 = GameSystem::createProjectiles
                            (2, Position(player->getPosition().x + 32, player->getPosition().y + 5), 
                            Velocity(0.25f, 0.25f), true, sf::IntRect(242, 183, 15, 17));
                        scene.getCurrentScene().addEntity(shoot2);
                        scene.getCurrentScene().addEntity(shoot3);
                    }
                    scene.getCurrentScene().addEntity(shoot);
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
            [entity, goTo, click](SceneManager &sceneManager) {
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);
                sf::Vector2<int> mousePosition = sf::Mouse::getPosition(*GraphicSystem::getWindow());

                if (mousePosition.x > pos->getPosition().x && mousePosition.x < pos->getPosition().x + click.x &&
                    mousePosition.y > pos->getPosition().y && mousePosition.y < pos->getPosition().y + click.y) {
                        if (goTo != SceneManager::SceneType::NONE)
                            sceneManager.setCurrentScene(goTo);
                        else
                            sceneManager.setShouldClose(true);
                }
            },
            [](SceneManager &) {});

        std::shared_ptr<Event> eventListener = std::make_shared<Event>();

        eventListener->addMouseEvent(sf::Mouse::Button::Left, mouseCallbacks);
        entity->addComponent(eventListener);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createMainMenu()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createMainMenu, this));
        std::shared_ptr<Entity> entity = createSprite(45, 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite(50, 350, 350);
        std::shared_ptr<Entity> entity3 = createSprite(51, 350, 410);
        std::shared_ptr<Entity> entity4 = createSprite(52, 120, 289);

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
        std::shared_ptr<Entity> entity = createSprite(45, 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite(46, 230, 500);
        std::shared_ptr<Entity> entity3 = createText("OPTION", 350, 250, 50);

        createButtonEvent(entity2, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity2)
              .addEntity(entity3);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createPauseMenu()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createOptionMenu, this));
        std::shared_ptr<Entity> entity = createSprite(47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(46, 230, 400);
        std::shared_ptr<Entity> entity3 = createText("PAUSE", 350, 25, 50);

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
        std::shared_ptr<Entity> player = createPlayer(53, 50, 100);
        // std::shared_ptr<Entity> tower1 = createEnnemy("assets/sprites_sheets/r-typesheet9.gif", 183, 50, 0.f, Ennemy::Type::JORYDE_ALIEN);
        std::shared_ptr<Entity> tower2 = createEnnemy(10, 53, 150, 0.f, Ennemy::Type::ROBOT_DINO);
        std::shared_ptr<Entity> tower3 = createEnnemy(5, 183, 50, 0.f, Ennemy::Type::SPATIAL);

        scene->addEntity(player)
              .addEntity(tower3)
              .addEntity(tower2);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createFirstLevel()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createFirstLevel, this));
        std::shared_ptr<Entity> top_wall = createSprite(48, 100, 0);
        std::shared_ptr<Entity> bottom_wall = createSprite(49, 100, 127);
        std::shared_ptr<Entity> player = createPlayer(53, 50, 100);
        std::shared_ptr<Entity> tower1 = createEnnemy(55, 333, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower2 = createEnnemy(55, 385, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower3 = createEnnemy(55, 428, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower4 = createEnnemy(55, 529, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower5 = createEnnemy(55, 573, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower6 = createEnnemy(55, 720, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower7 = createEnnemy(55, 772, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower8 = createEnnemy(55, 823, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower9 = createEnnemy(55, 702, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower10 = createEnnemy(55, 754, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower11 = createEnnemy(55, 806, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower12 = createEnnemy(55, 145, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower13 = createEnnemy(55, 957, 17, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower14 = createEnnemy(55, 957, 17, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> joryde1 = createEnnemy(9, 183, 50, 0.f, Ennemy::Type::JORYDE_ALIEN);
        std::vector<std::shared_ptr<IEntity>> spatial1 = createWavesEnnemy(5, 300, 90, 0.f, Ennemy::Type::SPATIAL);
        std::shared_ptr<Entity> dino1 = createEnnemy(10, 345, 179, 0.f, Ennemy::Type::ROBOT_DINO);

        scene-> addEntity(top_wall)
                .addEntity(bottom_wall)
                .addEntity(player)
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
                .addEntity(dino1)
                .addEntity(joryde1)
                .addEntities(spatial1);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneLose()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneLose, this));
        std::shared_ptr<Entity> entity = createText("You Lose", 350, 25, 50);
        std::shared_ptr<Entity> entity1 = createSprite(47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(51, 230, 400);

        createButtonEvent(entity1, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity1)
              .addEntity(entity2);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneWin()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneWin, this));
        std::shared_ptr<Entity> entity = createText("You Win", 350, 25, 50);
        std::shared_ptr<Entity> entity1 = createSprite(47, 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite(51, 230, 400);

        createButtonEvent(entity1, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity1)
              .addEntity(entity2);
        return (scene);
    }
}
