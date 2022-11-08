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
#include "ClientSystem.hpp"

namespace R_TYPE {

    sf::RenderWindow *GraphicSystem::window;
    std::vector<std::shared_ptr<sf::Texture>> GraphicSystem::_textures;
    bool EventSystem::isInit;

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

        window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");
        window->setFramerateLimit(60);
        // eventSystem->init(manager);
        // eventSystem->setWindow(window);
        camera = new sf::View(sf::FloatRect(0.f, 0.f, 270.f, 205.f));
        window->setView(*camera);
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
            // if (!_textures[i].loadFromFile(_pathTextures[i]))
            //     std::cerr << "error load texture path\n";
        }
        _isInit = false;
    }

    void GraphicSystem::initAllSprites(SceneManager &manager)
    {
        for (auto &scene : manager.getScenes()) {
            // for (auto &entity : (*scene.second)[IEntity::Tags::PLAYER]) {
            //     auto sprite = Component::castComponent<Player>((*entity)[IComponent::Type::PLAYER]);
            //     sprite->getSprite().setTexture(*_textures[0]);
            //     sprite->getSprite().setTextureRect(sprite->getSprite().getTextureRect());
            //     sprite->getSprite().setOrigin(sprite->getSprite().getTextureRect().width / 2, sprite->getSprite().getTextureRect().height / 2);
            //     sprite->getSprite().setPosition(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
            //     sprite->getSprite().setRotation(sprite->getSprite().getRotation());
            // }


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
            camera = new sf::View(sf::FloatRect(0.f, 0.f, 270.f, 205.f));
            window->setView(*camera);
            _isInit = true;
        } else if (manager.getCurrentSceneType() != SceneManager::SceneType::LEVEL1 && _isInit == true) {
            camera = new sf::View(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
            window->setView(*camera);
            _isInit = false;
        }
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        initAllSprites(manager);
        if (EventSystem::isInit == false) {
            eventSystem->init(manager);
            eventSystem->setWindow(window);
            EventSystem::isInit = true;
        }
        eventSystem->update(manager, deltaTime);
        window->clear(sf::Color::Black);
        setCamera(manager);

        for (auto &e : manager.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sprite->setPos(pos->getPosition());
            std::cout << "pos: " << pos->getPosition().x << " " << pos->getPosition().y << std::endl;
            window->draw(sprite->getSprite());
        }
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::TEXT]) {
            auto text = Component::castComponent<Text>((*e)[IComponent::Type::TEXT]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            text->printText(window, *pos.get());
        }
        if (manager.getCurrentSceneType() == SceneManager::SceneType::LEVEL1) {
            // camera->move(0.25f, 0.f);
            // window->setView(*camera);
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