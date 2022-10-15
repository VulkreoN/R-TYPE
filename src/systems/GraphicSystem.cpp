/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#include "GraphicSystem.hpp"
#include <iostream>
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Ennemy.hpp"

namespace R_TYPE {

    sf::RenderWindow *GraphicSystem::window;

    GraphicSystem::GraphicSystem()
    {
        std::cout << "Graphic System create" << std::endl;
        eventSystem = std::make_unique<EventSystem>();
    }

    GraphicSystem::~GraphicSystem()
    {
    }

    void GraphicSystem::init(SceneManager &manager)
    {
        std::cout << "Graphic System init" << std::endl;

        window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");
        window->setFramerateLimit(60);
        eventSystem->init(manager);
        eventSystem->setWindow(window);
        camera = new sf::View(sf::FloatRect(0.f, 0.f, 270.f, 205.f));
        window->setView(*camera);
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        eventSystem->update(manager, deltaTime);
        window->clear(sf::Color::Black);
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sprite->setPos(pos->getPosition());
            window->draw(sprite->getSprite());
        }
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::TEXT]) {
            auto text = Component::castComponent<Text>((*e)[IComponent::Type::TEXT]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            text->printText(window, *pos.get());
        }
        if (manager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            camera->move(0.25f, 0.f);
            window->setView(*camera);
        }
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
            player->getSprite().setPosition(player->getPosition());
            window->draw(player->getSprite());
        }
        window->display();
    }

    void GraphicSystem::destroy()
    {
        std::cout << "Graphic System destroyed" << std::endl;
        eventSystem->destroy();
        window->close();
    }
}