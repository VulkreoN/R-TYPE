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

namespace R_TYPE {
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
        eventSystem->init(manager);
        eventSystem->setWindow(window);
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        eventSystem->update(manager, deltaTime);
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            auto test = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            window->draw(test->getSprite());
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