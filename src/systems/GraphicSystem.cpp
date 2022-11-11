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
#include "Nono.hpp"
#include "Text.hpp"
#include "Ennemy.hpp"
#include "ClientSystem.hpp"

namespace R_TYPE {

    std::shared_ptr<sf::RenderWindow> GraphicSystem::window;
    std::vector<std::shared_ptr<sf::Texture>> GraphicSystem::_textures;
    bool EventSystem::isInit;
    std::shared_ptr<sf::View> GraphicSystem::camera;

    GraphicSystem::GraphicSystem(std::unique_ptr<ClientSystem> client)
    {
        std::cout << "Graphic System create" << std::endl;
        eventSystem = std::make_unique<EventSystem>(std::move(client));

    }

    GraphicSystem::~GraphicSystem()
    {
    }

    void GraphicSystem::init(SceneManager &manager)
    {
        std::ifstream input_file;
        std::string line;
        std::cout << "Graphic System init" << std::endl;

        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML window");
        window->setFramerateLimit(60);
        // eventSystem->init(manager);
        // eventSystem->setWindow(window);
        camera = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 270.f, 205.f));
        normalView = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
        input_file.open("assets/sprites_sheets/pathText.txt");
        while (getline(input_file, line)) {
            std::istringstream ss_line(line);
            while(ss_line){
                std::string element;
                ss_line >> element;
                if (element != "")
                    _pathTextures.push_back(element);
            }
        }
        for (int i = 0; i != _pathTextures.size(); i++) {
            sf::Texture texture;
            texture.loadFromFile(_pathTextures[i]);
            _textures.push_back(std::make_shared<sf::Texture>(texture));
        }
        _isInit = false;
    }

    void GraphicSystem::initAllSprites(SceneManager &manager)
    {
        for (auto &scene : manager.getScenes()) {
            for (auto &entity : (*scene.second)[IEntity::Tags::SPRITE_2D]) {
                auto sprite = Component::castComponent<Sprite>((*entity)[IComponent::Type::SPRITE]);
                if (sprite->isInit == true)
                    continue;
                sprite->getSprite().setTexture(*_textures[sprite->getName() - 1]);
                if (sprite->getRect() != sf::IntRect(0, 0, 0, 0)) {
                    sprite->getSprite().setTextureRect(sprite->getRect());
                }
                sprite->getSprite().setPosition(sprite->getPosition().getPosition().x, sprite->getPosition().getPosition().y);
                sprite->getSprite().setRotation(sprite->getAngle());
                sprite->isInit = true;
            }
        }
    }

    void GraphicSystem::setCamera(SceneManager &manager)
    {
        if (manager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1 && _isInit == false) {
            window->setView(*camera);
            _isInit = true;
        } else if (manager.getCurrentSceneType() != SceneManager::SceneType::LEVEL1 && _isInit == true) {
            window->setView(*normalView);
            _isInit = false;
        }
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        initAllSprites(manager);
        if (EventSystem::isInit == false) {
            eventSystem->init(manager);
            eventSystem->setWindow(window, camera, normalView);
            EventSystem::isInit = true;
        }
        eventSystem->update(manager, deltaTime);
        window->clear(sf::Color::Black);
        setCamera(manager);

        for (auto &e : manager.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sprite->setPos(pos->getPosition());
            window->draw(sprite->getSprite());
        }
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::TEXT]) {
            auto text = Component::castComponent<Text>((*e)[IComponent::Type::TEXT]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            text->printText(window.get(), *pos.get());
        }
        if (manager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            // camera->move(0.25f, 0.f);
            window->setView(*camera);
        
            for (auto &e : manager.getCurrentScene()[IEntity::Tags::NONO]) {
                auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);

                amanager.update_nono(e, deltaTime);
            }
            for (auto &e : manager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
                auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);

                amanager.update_ennemy(e, deltaTime);
            }
        }

        window->display();
    }

    void GraphicSystem::updateCamera(float offset)
    {
        if (camera->getCenter().x + offset - 135 > 1925)
            return;
        camera->move(offset, 0.f);
    }

    void GraphicSystem::destroy()
    {
        std::cout << "Graphic System destroyed" << std::endl;
        eventSystem->destroy();
        window->close();
    }
}