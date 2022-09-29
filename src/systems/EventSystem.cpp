/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** EventSystem
*/

#include "EventSystem.hpp"
#include "GraphicSystem.hpp"
#include "SceneManager.hpp"
#include <iostream>

namespace R_TYPE {

    std::map<int, std::vector<std::shared_ptr<Event>>> EventSystem::_event;

    EventSystem::EventSystem()
    {
        std::cout << "Event System create" << std::endl;
    }

    EventSystem::~EventSystem()
    {
    }

    void EventSystem::init(SceneManager &manager)
    {
        for (auto &entity : manager.getCurrentScene()[IEntity::Tags::CALLABLE]) {
            auto listener = Component::castComponent<Event>((*entity)[IComponent::Type::EVENT]);
            if (listener)
                _event[0].push_back(listener);
        }
    }

    void EventSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                manager.setShouldClose(true);
            for (auto &listener : _event[(int)manager.getCurrentSceneType()]) {
                handleKeyboard(manager, listener, event);
            }
        }
    }

    void EventSystem::destroy()
    {
        std::cout << "Event System destroyed" << std::endl;
    }

    void EventSystem::handleKeyboard(SceneManager &manager, std::shared_ptr<Event> listener, sf::Event event)
    {
        for (auto &it : listener->getKeyboardMap()) {
            bool wasPressed = false;
            if (it.second.pressed && event.type == sf::Event::KeyPressed && event.key.code == it.first) {
                if (wasPressed == false) {
                    it.second.pressed(manager);
                    wasPressed = true;
                }
            }
            if (it.second.released && event.type == sf::Event::KeyReleased && event.key.code == it.first) {
                it.second.released(manager);
                wasPressed = false;
            }
        }
    }
}