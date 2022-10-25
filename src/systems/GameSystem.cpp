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
        sceneManager.setCurrentScene(SceneManager::SceneType::MAIN_MENU);
    }

    void GameSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
                auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
                auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

                pos->setX(pos->getPosition().x + velocity->getVelocity().x * deltaTime);
                pos->setY(pos->getPosition().y + velocity->getVelocity().y * deltaTime);
            }
            for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
                auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);

                if (player->isAlive() == false) {
                    sceneManager.setCurrentScene(SceneManager::SceneType::LOSE);
                }
            }
        }
    }

    void GameSystem::destroy()
    {
        std::cout << "Game System destroyed" << std::endl;
    }

    std::shared_ptr<Entity> GameSystem::createSprite(std::string path, int posX, int posY)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(path, *component2);

        entity->addComponent(component)
                .addComponent(component2);
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

    std::shared_ptr<Entity> GameSystem::createEnnemy(std::string path, int posX, int posY, float angle, Ennemy::Type type)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(path, *component2, angle);
        std::shared_ptr<Ennemy> compoment3 = std::make_shared<Ennemy>(type);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(compoment3);
        return(entity);
    }

    std::shared_ptr<Entity> GameSystem::createProjectiles(std::string path, Position pos, Velocity velocity, bool byPlayer)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(pos);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>(path, *component2);
        std::shared_ptr<Velocity> component4 = std::make_shared<Velocity>(velocity);
        std::shared_ptr<Projectiles> component3 = std::make_shared<Projectiles>(byPlayer);

        entity->addComponent(component)
                .addComponent(component2)
                .addComponent(component3)
                .addComponent(component4);
        return (entity);
    }

    std::shared_ptr<Entity> GameSystem::createPlayer(int posX, int posY)
    {
        std::shared_ptr<Entity> player_e = std::make_shared<Entity>();
        std::shared_ptr<Position> player_pos = std::make_shared<Position>(posX, posY);
        std::shared_ptr<Player> player = std::make_shared<Player>(*player_pos);
        std::shared_ptr<Event> event_p = std::make_shared<Event>();

        player_e->addComponent(player);

        ButtonCallbacks pause (
            [](SceneManager &sceneManager) {
                sceneManager.setCurrentScene(SceneManager::SceneType::PAUSE);
            },
            [](SceneManager &) {}
        );

        ButtonCallbacks up (
            [player_e](SceneManager &manager) {
                auto comp = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp);
                Position moved(player->getPosition().x, player->getPosition().y - 10);

                // std::cout << player->getSprite().getColor().r << std::endl;

                if (CollideSystem::canMoveUp(moved, manager))
                    player->setPosition(moved.getPosition());
            },
            [](SceneManager &) {});

        ButtonCallbacks left (
            [player_e](SceneManager &manager) {
                auto comp = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp);
                Position moved(player->getPosition().x - 10, player->getPosition().y);

                if (CollideSystem::canMoveLeft(moved, manager))
                    player->setPosition(moved.getPosition());
            },
            [](SceneManager &) {});

        ButtonCallbacks down (
            [player_e](SceneManager &manager) {
                auto comp = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp);
                Position moved(player->getPosition().x, player->getPosition().y + 10);

                if (CollideSystem::canMoveDown(moved, manager))
                    player->setPosition(moved.getPosition());
            },
            [](SceneManager &) {});

        ButtonCallbacks right (
            [player_e](SceneManager &manager) {
                auto comp = (*player_e)[IComponent::Type::PLAYER];
                auto player = Component::castComponent<Player>(comp);
                Position moved(player->getPosition().x + 10, player->getPosition().y);

                if (CollideSystem::canMoveRight(moved, manager))
                    player->setPosition(moved.getPosition());
            },
            [](SceneManager &) {});

        ButtonCallbacks shoot (
           [](SceneManager &scene) {
                auto entity = scene.getCurrentScene()[IEntity::Tags::PLAYER][0];
                auto comp = (*entity)[IComponent::Type::PLAYER];
                auto pos = Component::castComponent<Player>(comp);
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles
                    ("projectile.png", Position(pos->getPosition().x + 20, pos->getPosition().y +10), Velocity(0.1f, 0), true);
                scene.getCurrentScene().addEntity(shoot);
           },
           [](SceneManager &scene) {
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
        std::shared_ptr<Entity> entity = createSprite("assets/menus/mnu.jpg", 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite("assets/menus/option1.png", 350, 350);
        std::shared_ptr<Entity> entity3 = createSprite("assets/menus/quit.png", 350, 410);
        std::shared_ptr<Entity> entity4 = createSprite("assets/menus/play.png", 120, 289);

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
        std::shared_ptr<Entity> entity = createSprite("assets/menus/mnu.jpg", 0, 0);
        std::shared_ptr<Entity> entity2 = createSprite("assets/menus/return.png", 230, 500);
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
        std::shared_ptr<Entity> entity = createSprite("assets/menus/backtoMenu.png", 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite("assets/menus/return.png", 230, 400);
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
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createFirstLevel()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createFirstLevel, this));
        std::shared_ptr<Entity> top_wall = createSprite("assets/sprites_statics/top_wall_lvl1.png", 100, 0);
        std::shared_ptr<Entity> bottom_wall = createSprite("assets/sprites_statics/bottom_wall_lvl1.png", 100, 127);
        std::shared_ptr<Entity> player = createPlayer(50, 100);
        std::shared_ptr<Entity> tower1 = createEnnemy("ennemy.png", 333, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower2 = createEnnemy("ennemy.png", 385, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower3 = createEnnemy("ennemy.png", 428, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower4 = createEnnemy("ennemy.png", 529, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower5 = createEnnemy("ennemy.png", 573, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower6 = createEnnemy("ennemy.png", 720, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower7 = createEnnemy("ennemy.png", 772, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower8 = createEnnemy("ennemy.png", 823, 43, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower9 = createEnnemy("ennemy.png", 702, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower10 = createEnnemy("ennemy.png", 754, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower11 = createEnnemy("ennemy.png", 806, 163, 0.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower12 = createEnnemy("ennemy.png", 145, 19, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower13 = createEnnemy("ennemy.png", 957, 17, 180.f, Ennemy::Type::TURRET);
        std::shared_ptr<Entity> tower14 = createEnnemy("ennemy.png", 957, 17, 180.f, Ennemy::Type::TURRET);


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
                .addEntity(tower14);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneLose()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneLose, this));
        std::shared_ptr<Entity> entity = createText("You Lose", 350, 25, 50);
        std::shared_ptr<Entity> entity1 = createSprite("assets/menus/backtoMenu.png", 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite("assets/menus/quit.png", 230, 400);

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
        std::shared_ptr<Entity> entity1 = createSprite("assets/menus/backtoMenu.png", 230, 300);
        std::shared_ptr<Entity> entity2 = createSprite("assets/menus/quit.png", 230, 400);

        createButtonEvent(entity1, SceneManager::SceneType::MAIN_MENU, sf::Vector2i(315, 50));
        createButtonEvent(entity2, SceneManager::SceneType::NONE, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity1)
              .addEntity(entity2);
        return (scene);
    }
}
