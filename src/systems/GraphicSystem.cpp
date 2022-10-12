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
        eventSystem->init(manager);
        eventSystem->setWindow(window);
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
        window->display();
    }

    void GraphicSystem::destroy()
    {
        std::cout << "Graphic System destroyed" << std::endl;
        eventSystem->destroy();
        window->close();
    }
}