/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** EventSystem
*/

#include <iostream>
#include "EventSystem.hpp"
#include "GraphicSystem.hpp"
#include "SceneManager.hpp"
#include "Ennemy.hpp"
#include "Position.hpp"
#include "ClientSystem.hpp"
#include "ServerSystem.hpp"
#include "Core.hpp"

namespace R_TYPE {

    std::map<int, std::vector<std::shared_ptr<Event>>> EventSystem::_event;

    EventSystem::EventSystem(std::unique_ptr<NetworkSystem> network)
    {
        _network = std::move(network);
        std::cout << "Event System create" << std::endl;
        isInit = false;
    }

    EventSystem::~EventSystem()
    {
    }

    void EventSystem::init(SceneManager &manager)
    {
        std::cout << "Event System init" << std::endl;
        for (auto &index : manager.getSceneTypeList()) {
            for (auto &entity : manager.getScene(index)[IEntity::Tags::CALLABLE]) {
                auto listener = Component::castComponent<Event>((*entity)[IComponent::Type::EVENT]);
                if (listener)
                    _event[(int)index].push_back(listener);
            }
        }
    }

    void EventSystem::putCallback(SceneManager &manager, std::shared_ptr<IEntity> entity)
    {
        auto listener = Component::castComponent<Event>((*entity)[IComponent::Type::EVENT]);
        if (listener)
            _event[(int)manager.getCurrentSceneType()].push_back(listener);
    }

    void EventSystem::setWindow(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<sf::View> _camera,
        std::shared_ptr<sf::View> _normalView)
    {
        window = _window;
        camera = _camera;
        normalView = _normalView;
    }

    void EventSystem::updateClient(SceneManager &manager, uint64_t deltaTime)
    {
        sf::Event event;
        float result = 0;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                manager.setShouldClose(true);
            else if (event.type == sf::Event::Resized) {
                normalView->setSize(event.size.width, event.size.height);
                normalView->zoom((float)600.0 / event.size.height);
                window->setView(*normalView);
                result = event.size.width * 205.0 / event.size.height;
                camera->setViewport(sf::FloatRect(((result - 270.0) / 2) / result, 0, 270.0 / (event.size.width * 205.0 / event.size.height), 1));
            }
            for (auto &listener : _event[(int)manager.getCurrentSceneType()]) {
                handleKeyboard(manager, listener, event);
                handleMouse(manager, listener, event);
            }
        }
        // for (auto &script : manager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
        //     auto pos = Component::castComponent<Position>((*script)[IComponent::Type::POSITION]);
        //     auto ennemy = Component::castComponent<Ennemy>((*script)[IComponent::Type::ENNEMY]);
        //     float windowPosX = window->getView().getCenter().x - 135;

        //     if (pos->getPosition().x < windowPosX + 270 && pos->getPosition().x > windowPosX) {
        //         ennemy->launchScript(manager, script);
        //     }
        // }
    }

    void EventSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        if (Core::getIsServeur())
            updateServer(manager, deltaTime);
        else
            updateClient(manager, deltaTime);
    }

    void EventSystem::updateServer(SceneManager &manager, uint64_t deltaTime)
    {
        auto keys = dynamic_cast<ServerSystem &>(*_network).getKeys();
        auto mouseButtons = dynamic_cast<ServerSystem &>(*_network).getMouseButtons();
        auto mousePositions = dynamic_cast<ServerSystem &>(*_network).getMousePositions();

        while (!keys.empty()) {
            for (auto &listener : _event[(int)manager.getCurrentSceneType()]) {
                auto call = listener->getKeyboardMap()[static_cast<sf::Keyboard::Key>(keys.front().first)];
                switch (keys.front().second) {
                    case NetworkSystem::ButtonState::PRESSED:
                        if (call.pressed)
                            call.pressed(manager);
                        break;
                    case NetworkSystem::ButtonState::DOWN:
                        if (call.down)
                            call.down(manager);
                        break;
                    case NetworkSystem::ButtonState::UP:
                        if (call.up)
                            call.up(manager);
                        break;
                    case NetworkSystem::ButtonState::RELEASED:
                        if (call.released)
                            call.released(manager);
                        break;
                }
            }
            keys.pop_front();
            dynamic_cast<ServerSystem &>(*_network).removeKey();
        }

        while(!mouseButtons.empty() && !mousePositions.empty()) {
            for (auto &listener : _event[(int)manager.getCurrentSceneType()]) {
                auto call = listener->getMouseMappings()[static_cast<sf::Mouse::Button>(mouseButtons.front().first)];
                switch (mouseButtons.front().second) {
                    case NetworkSystem::ButtonState::PRESSED:
                        if (call._pressed) {
                            call._pressed(manager, sf::Vector2i(mousePositions.front().first, mousePositions.front().second));
                        }
                        break;
                    case NetworkSystem::ButtonState::RELEASED:
                        if (call._released)
                            call._released(manager, sf::Vector2i(mousePositions.front().first, mousePositions.front().second));
                        break;
                }
            }
            mouseButtons.pop_front();
            mousePositions.pop_front();
            dynamic_cast<ServerSystem &>(*_network).removeMouse();
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
                    // it.second.pressed(manager);
                    dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::PRESSED, true);
                    wasPressed = true;
                }
            }
            if (it.second.released && event.type == sf::Event::KeyReleased && event.key.code == it.first) {
                // it.second.released(manager);
                dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::RELEASED, true);
                wasPressed = false;
            }
            if (it.second.pressed && event.type == sf::Event::KeyPressed && event.key.code == it.first) {
                if (wasPressed == true) {
                    // it.second.down(manager);
                    dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::DOWN, true);
                }
            }
            if (!sf::Keyboard::isKeyPressed(it.first) ) {
                if (wasPressed == false) {
                    // it.second.up(manager);
                    dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::UP, true);
                }
            }
        }
    }

    void EventSystem::handleMouse(SceneManager &manager, std::shared_ptr<Event> listener, sf::Event event)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*GraphicSystem::getWindow());
        mousePosition = (sf::Vector2i)GraphicSystem::getWindow()->mapPixelToCoords(mousePosition);

        for (auto &it : listener->getMouseMappings()) {
            if (it.second._pressed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == it.first) {
                it.second._pressed(manager, mousePosition);
                dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::PRESSED, false, mousePosition.x, mousePosition.y);
                break;
            }
            // if (it.second._down && Window::isMouseButtonDown(it.first)) {
            //     it.second._down(manager, pos);
            //     break;
            // }
            if (it.second._released && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == it.first) {
                it.second._released(manager, mousePosition);
                dynamic_cast<ClientSystem &>(*_network).sendEvent(it.first, NetworkSystem::ButtonState::RELEASED, false, mousePosition.x, mousePosition.y);
                break;
            }
            // if (Window::isMouseButtonUp(it.first)) {
            //     it.second._up(manager, pos);
            //     break;
            // }
        }
    }
}
