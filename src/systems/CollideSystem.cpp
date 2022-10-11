#include "CollideSystem.hpp"
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"


namespace R_TYPE {

    CollideSystem::CollideSystem() 
    {
        std::cout << "Collide System create" << std::endl;
    }

    CollideSystem::~CollideSystem() 
    {

    }

    void CollideSystem::init(SceneManager &sceneManager) 
    {
        std::cout << "Collide System init" << std::endl;

        // for (auto &scene : sceneManager.getScenes()) {
        //     auto collidables = (*scene.second)[IEntity::Tags::COLLIDABLE];
        // }
    }

    void CollideSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::GAME) {
            const sf::Color wallcolor(254, 136, 45);
            const sf::Image image = GraphicSystem::getWindow()->capture();
            auto e = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
            auto player = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            for (int a = 0; a < 94; a++)
                for (int b = 0; b < 90; b++) {
                    std::cout << "player : " << player->getPosition().x << " " << player->getPosition().y << std::endl;
                    sf::Color get = image.getPixel(player->getPosition().x + a, player->getPosition().y + b);
                    std::cout << (int)get.r << " " << (int)get.g << " " << (int)get.b << std::endl;
                    if (get == wallcolor)
                        std::cout << "collide" << std::endl;
                }
        }


        // if (sceneManager.getCurrentSceneType() == SceneManager::SceneType::GAME) { 
        //     auto e1 = sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][0];
        //     auto e2 =  sceneManager.getCurrentScene()[IEntity::Tags::SPRITE_2D][1];
        //     auto sprite = Component::castComponent<Sprite>((*e1)[IComponent::Type::SPRITE]);
        //     auto sprite2 = Component::castComponent<Sprite>((*e2)[IComponent::Type::SPRITE]);
        //     sf::FloatRect test = sprite->getSprite().getGlobalBounds();
        //     sf::FloatRect check = sprite2->getSprite().getGlobalBounds();
        //     // sprite->getSprite().getTransform().transformRect(test);
        //     // sprite2->getSprite().getTransform().transformRect(check);
        //     if (test.intersects(check))
        //         std::cout << "collide" << std::endl;

    }

    void CollideSystem::destroy()
    {
        std::cout << "Collide System destroyed" << std::endl;
        _collidables2D.clear();
    }
}