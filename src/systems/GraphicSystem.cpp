/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#include "GraphicSystem.hpp"
#include <iostream>
#include "SceneManager.hpp"

namespace R_TYPE {
    GraphicSystem::GraphicSystem()
    {
        std::cout << "Graphic System create" << std::endl;
    }

    GraphicSystem::~GraphicSystem()
    {
    }

    void GraphicSystem::init(SceneManager &manager)
    {
        std::cout << "Graphic System init" << std::endl;

        window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-TYPE NEW GENERATION");
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                manager.setShouldClose(true);
        }
        
        window->display();
    }

    void GraphicSystem::destroy()
    {
        std::cout << "Graphic System destroyed" << std::endl;
        window->close();
    }
}