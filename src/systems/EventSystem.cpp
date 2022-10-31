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
#include "Ennemy.hpp"
#include "Position.hpp"

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
        for (auto &index : manager.getSceneTypeList()) {
            for (auto &entity : manager.getScene(index)[IEntity::Tags::CALLABLE]) {
                auto listener = Component::castComponent<Event>((*entity)[IComponent::Type::EVENT]);
                if (listener)
                    _event[(int)index].push_back(listener);
            }
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
                handleMouse(manager, listener, event);
            }
        }
        for (auto &script : manager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto pos = Component::castComponent<Position>((*script)[IComponent::Type::POSITION]);
            auto ennemy = Component::castComponent<Ennemy>((*script)[IComponent::Type::ENNEMY]);
            float windowPosX = window->getView().getCenter().x - 135;

            if (pos->getPosition().x < windowPosX + 270 && pos->getPosition().x > windowPosX) {
                ennemy->launchScript(manager, script);
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
            if (it.second.pressed && event.type == sf::Event::KeyPressed && event.key.code == it.first) {
                if (wasPressed == true) {
                    it.second.down(manager);
                }
            }
            if (it.second.released && event.type == sf::Event::KeyReleased && event.key.code == it.first) {
                if (wasPressed == false)
                    it.second.up(manager);
            }
        }
    }

    void EventSystem::handleMouse(SceneManager &manager, std::shared_ptr<Event> listener, sf::Event event)
    {
        for (auto &it : listener->getMouseMappings()) {
            if (it.second._pressed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == it.first) {
                it.second._pressed(manager);
                break;
            }
            // if (it.second._down && Window::isMouseButtonDown(it.first)) {
            //     it.second._down(manager, pos);
            //     break;
            // }
            if (it.second._released && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == it.first) {
                it.second._released(manager);
                break;
            }
            // if (Window::isMouseButtonUp(it.first)) {
            //     it.second._up(manager, pos);
            //     break;
            // }
        }
    }
}
