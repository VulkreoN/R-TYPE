#include "CollideSystem.hpp"
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "Projectiles.hpp"
#include "Player.hpp"

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
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);

            sf::FloatRect box = player->getSprite().getGlobalBounds();
            if (pos->getPosition().x > player->getPosition().x && pos->getPosition().x < player->getPosition().x + box.width
            && pos->getPosition().y > player->getPosition().y && pos->getPosition().y < player->getPosition().y + box.height)  {
                sceneManager.getCurrentScene().removeEntity(e);
                sceneManager.getCurrentScene().removeEntity(project);
                return;
            }
        }
    }
    
    bool CollideSystem::isBlack(Position pos)
    {
        sf::Image imageUp;
        sf::Image imageDown;
        Position realSize(0 ,0);
        sf::Color color(0, 0, 0);
        sf::Color get;

        imageUp.loadFromFile("assets/sprites_statics/top_wall_lvl1.png");
        imageDown.loadFromFile("assets/sprites_statics/bottom_wall_lvl1.png");
        for (int a = 0; a < 32; a++) {
            for (int b = 0; b < 12; b++) {

                realSize.setX(pos.getPosition().x - 100);
                realSize.setY(pos.getPosition().y);

                if (pos.getPosition().x < 100)
                    return(true);

                if (pos.getPosition().y < 80)
                    get = imageUp.getPixel(realSize.getPosition().x + a, realSize.getPosition().y + b);
                else if (pos.getPosition().y > 127) {
                    realSize.setY(pos.getPosition().y - 127);
                    get = imageDown.getPixel(realSize.getPosition().x + a, realSize.getPosition().y + b);
                }
                if (get.r != color.r && get.g != color.g && get.b != color.b) {
                    return (false);
                }
            }
        }
        return (true);
    }

    bool CollideSystem::canMoveLeft(Position pos, SceneManager &sceneManger)
    {
        Position real(0, 0);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER))
                continue;
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos) == false)
                    return (false);
            }
        }
        return true;
    }

    bool CollideSystem::canMoveRight(Position pos, SceneManager &sceneManger)
    {
        Position real(0, 0);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER))
                continue;
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos.getPosition().x + 32 > posEnnemi->getPosition().x && pos.getPosition().x + 32 < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos) == false)
                    return (false);
            }
        }
        return true;
    }

    bool CollideSystem::canMoveUp(Position pos, SceneManager &sceneManger)
    {
        Position real(0, 0);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        const sf::Image image = GraphicSystem::getWindow()->capture();
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER))
                continue;
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();

            if (pos.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos) == false)
                    return (false);
            }
        }
        return true;
    }

    bool CollideSystem::canMoveDown(Position pos, SceneManager &sceneManger)
    {
        Position real(0, 0);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER))
                continue;
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y + 15 > posEnnemi->getPosition().y && pos.getPosition().y + 15 < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos) == false)
                    return (false);
            }
        }
        return true;
    }

    void CollideSystem::destroy()
    {
        std::cout << "Collide System destroyed" << std::endl;
    }
}