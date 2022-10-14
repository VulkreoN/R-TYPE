#include "CollideSystem.hpp"
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "Projectiles.hpp"

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
    }

    void CollideSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        // ca seg la dedans quand tu tue tous les ennemy
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto component = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            if (component->shootByPlayer() == false)
                didHitPlayer(sceneManager, e);
            else if (component->shootByPlayer() == true)
                didHitEnnemi(sceneManager, e);
        }
    }

    void CollideSystem::didHitEnnemi(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos->getPosition().x > posEnnemi->getPosition().x && pos->getPosition().x < posEnnemi->getPosition().x + box.width
            && pos->getPosition().y > posEnnemi->getPosition().y && pos->getPosition().y < posEnnemi->getPosition().y + box.height)  {
                sceneManager.getCurrentScene().removeEntity(e);
                sceneManager.getCurrentScene().removeEntity(project);
                return;
            }
        }
    }

    void CollideSystem::didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posPlayer = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos->getPosition().x > posPlayer->getPosition().x && pos->getPosition().x < posPlayer->getPosition().x + box.width
            && pos->getPosition().y > posPlayer->getPosition().y && pos->getPosition().y < posPlayer->getPosition().y + box.height)  {
                sceneManager.getCurrentScene().removeEntity(e);
                sceneManager.getCurrentScene().removeEntity(project);
                return;
            }
        }
    }

    bool CollideSystem::canMove(Position pos)
    {
        const sf::Image image = GraphicSystem::getWindow()->capture();
        const sf::Color wallcolor(image.getPixel(201, 400));

        for (int a = 0; a < 100; a++) {
            for (int b = 0; b < 38; b++) {
                sf::Color get = image.getPixel(pos.getPosition().x + a, pos.getPosition().y + b);
                if (get == wallcolor)
                    return (false);
            }
        }
        return (true);
    }

    void CollideSystem::destroy()
    {
        std::cout << "Collide System destroyed" << std::endl;
    }
}