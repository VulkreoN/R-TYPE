/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#include "GameSystem.hpp"
#include "Scene.hpp"
#include "Event.hpp"
#include "SceneManager.hpp"

#include "Entity.hpp"
#include "Position.hpp"
#include "Sprite.hpp"

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
        sceneManager.setCurrentScene(SceneManager::SceneType::GAME);
    }

    void GameSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        
    }

    void GameSystem::destroy()
    {
        std::cout << "Game System destroyed" << std::endl;
    }

    std::unique_ptr<R_TYPE::IScene> GameSystem::createSceneTest()
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(std::bind(&GameSystem::createSceneTest, this));
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        std::shared_ptr<Position> component2 = std::make_shared<Position>(200, 0);
        std::shared_ptr<Sprite> component = std::make_shared<Sprite>("arrow.png", *component2);
        std::shared_ptr<Event> event = std::make_shared<Event>();

        ButtonCallbacks call (
            [](SceneManager &) {
                std::cout << "pressed Z" << std::endl;
            },
            [](SceneManager &) {
                std::cout << "released Z" << std::endl;
            });

        event->addKeyboardEvent(sf::Keyboard::Z, call);

        entity->addComponent(component)
            .addComponent(event);

        scene->addEntity(entity);
        return (scene);
    }
}