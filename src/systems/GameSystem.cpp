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
#include "Position.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "Text.hpp"

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
        sceneManager.setCurrentScene(SceneManager::SceneType::MAIN_MENU);
    }

    void GameSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        
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

        createButtonEvent(entity4, SceneManager::SceneType::GAME, sf::Vector2i(230, 240));
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
        createButtonEvent(entity2, SceneManager::SceneType::GAME, sf::Vector2i(315, 50));

        scene->addEntity(entity)
              .addEntity(entity2)
              .addEntity(entity3);
        return (scene);
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneTest()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneTest, this));
        std::shared_ptr<Entity> entity = createSprite("arrow.png", 200, 0);
        std::shared_ptr<Entity> entity2 = createSprite("arrow.png", 200, 400);
        std::shared_ptr<Event> event = std::make_shared<Event>();
        std::shared_ptr<Event> move_up = std::make_shared<Event>();
        std::shared_ptr<Event> move_down = std::make_shared<Event>();
        std::shared_ptr<Event> move_RIGHT = std::make_shared<Event>();
        std::shared_ptr<Event> move_Left = std::make_shared<Event>();

        ButtonCallbacks moveLeft (
            [](SceneManager &sceneManager) {
                auto entity = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);

                pos->setX(pos->getPosition().x - 10);
            },
            [](SceneManager &) {});

        ButtonCallbacks moveRight (
            [](SceneManager &sceneManager) {
                auto entity = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);

                pos->setX(pos->getPosition().x + 10);
            },
            [](SceneManager &) {});

        ButtonCallbacks moveUp (
            [](SceneManager &sceneManager) {
                auto entity = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);

                pos->setY(pos->getPosition().y - 10);
            },
            [](SceneManager &) {});
        
        ButtonCallbacks moveDown (
            [](SceneManager &sceneManager) {
                auto entity = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
                auto comp = (*entity)[IComponent::Type::POSITION];
                auto pos = Component::castComponent<Position>(comp);

                pos->setY(pos->getPosition().y + 10);
            },
            [](SceneManager &) {});

        event->addKeyboardEvent(sf::Keyboard::Z, moveUp);
        event->addKeyboardEvent(sf::Keyboard::S, moveDown);
        event->addKeyboardEvent(sf::Keyboard::D, moveRight);
        event->addKeyboardEvent(sf::Keyboard::Q, moveLeft);
        entity->addComponent(move_up)
               .addComponent(move_down)
               .addComponent(move_RIGHT)
               .addComponent(move_Left);


        ButtonCallbacks call (
            [](SceneManager &sceneManager) {
                sceneManager.setCurrentScene(SceneManager::SceneType::PAUSE);
            },
            [](SceneManager &) {});

        event->addKeyboardEvent(sf::Keyboard::Escape, call);
        entity->addComponent(event);

        scene->addEntity(entity)
              .addEntity(entity2);
        return (scene);
    }
}