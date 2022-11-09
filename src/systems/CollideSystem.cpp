#include "CollideSystem.hpp"
#include "GameSystem.hpp"
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "Projectiles.hpp"
#include "Player.hpp"
#include "Velocity.hpp"
#include "Ennemy.hpp"

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
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto component = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            didHitWall(sceneManager, e);
            didHitProj(sceneManager, e);
            if (component->shootByPlayer() == false) {
                didHitPlayer(sceneManager, e);

                // ça seg quand il est detruit et que tu tire
                didHitNono(sceneManager, e);
            } else if (component->shootByPlayer() == true)
                didHitEnnemi(sceneManager, e);
        }
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto component = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);

            if (component->getIsActive() == false) {
                sceneManager.getCurrentScene().removeEntity(e);
                break;
            }
        }
        for (auto &player : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            collideEnnemyPlayer(sceneManager, player);
            collideBonusPlayer(sceneManager, player);
            collideNonoPlayer(sceneManager, player);
        }

        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto component = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
            auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();

            if (component->getType() == Ennemy::Type::ROBOT_DINO) {
                if (pos->getPosition().y > 32)
                    if (isBlack(*pos, box) == false) {
                        velocity->setX(-velocity->getVelocity().x);
                        if (component->getState() == Animation::State::RIGHT)
                            component->setState(Animation::State::LEFT);
                        else 
                            component->setState(Animation::State::RIGHT);
                    }
            }
        }
    }

    void CollideSystem::collideEnnemyPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            sf::FloatRect playerBox = spritePlayer->getSprite().getGlobalBounds();

            if (box.intersects(playerBox)) {
                component->setAlive(false);
            }
        }
    }

    void CollideSystem::collideBonusPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::BONUS]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto bonus = Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            sf::FloatRect playerBox = spritePlayer->getSprite().getGlobalBounds();

            if (box.intersects(playerBox) && component->getLevelNono() < 3) {
                if (bonus->getType() == Bonus::BonusType::SPEED || component->getNono() == false)
                    component->addBonus(bonus->getType());
                else if (component->getNono() == true){
                    addUpddateNono(sceneManager, player);
                    component->setLevelNono(component->getLevelNono() + 1);
                }
                sceneManager.getCurrentScene().removeEntity(e);
            }
        }
    }

    void CollideSystem::addUpddateNono(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto pos = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto pos1 = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);

            if (nono->getPosPlayer()->getPosition().x == pos->getPosition().x && nono->getPosPlayer()->getPosition().y == pos->getPosition().y) {
                // nono->disableNonoPlayer(sceneManager);
                nono->nextUpgrade();
            }
            if (nono->getUpgrade() == 1) {
                sprite->setRect(sf::IntRect(120, 69, 28, 21));
                nono->setState(Animation::State::LV2);
                auto anim = Component::castComponent<Animation>((*e)[IComponent::Type::ANIMATION]);
                anim->setRect(sprite->getRect());
            } else if (nono->getUpgrade() == 2) {
                sprite->setRect(sf::IntRect(270, 342, 28, 31));
                nono->setState(Animation::State::LV3);
                auto anim = Component::castComponent<Animation>((*e)[IComponent::Type::ANIMATION]);
                anim->setRect(sprite->getRect());
            }
        }
    }

    void CollideSystem::collideNonoPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        auto posPlayer = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
            auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            sf::FloatRect playerBox = spritePlayer->getSprite().getGlobalBounds();
            if (box.intersects(playerBox)) {
                pos->setX(posPlayer->getPosition().x + playerBox.width);
                pos->setY(posPlayer->getPosition().y);
                nono->isSnap = true;
                nono->unKillable = false;
                nono->setPosPlayer(posPlayer);
                velocity->setX(0);
                velocity->setY(0);
                component->setNono(true);
            }
        }
    }

    void CollideSystem::didHitWall(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto component = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto sprite = Component::castComponent<Sprite>((*project)[IComponent::Type::SPRITE]);
        auto velocity = Component::castComponent<Velocity>((*project)[IComponent::Type::VELOCITY]);
        
        sf::FloatRect box = sprite->getSprite().getGlobalBounds();
        if (pos->getPosition().y > 10)
            if (isBlack(*pos, box) == false)
                component->setIsActive(false);
    }

    void CollideSystem::didHitProj(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto proj = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            auto posProj = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();

            if (box.contains(pos->getPosition().x, pos->getPosition().y) && pos != posProj && projectile->shootByPlayer() != proj->shootByPlayer()) {
                if (projectile->getType() != Projectiles::Type::CHARGED && projectile->getType() != Projectiles::Type::LASER_BOUCLE)
                    projectile->setIsActive(false);
                if (proj->getType() != Projectiles::Type::CHARGED && proj->getType() != Projectiles::Type::LASER_BOUCLE)
                    proj->setIsActive(false);
                return;
            }
        }
    }

    void CollideSystem::didHitEnnemi(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
            sf::FloatRect box = sprite->getSprite().getGlobalBounds();

            if (box.contains(pos->getPosition().x, pos->getPosition().y)) {
                if (projectile->getType() != Projectiles::Type::CHARGED && projectile->getType() != Projectiles::Type::LASER_BOUCLE)
                    projectile->setIsActive(false);
                if (ennemy->getLoot() != Bonus::BonusType::NONE) {
                    auto bonus = GameSystem::createBonus(56, posEnnemi->getPosition(), ennemy->getLoot());
                    sceneManager.getCurrentScene().addEntity(bonus);
                }
                sceneManager.getCurrentScene().removeEntity(e);
                return;
            }
        }
    }

    void CollideSystem::didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            
            if (box.contains(pos->getPosition().x, pos->getPosition().y)) {
                projectile->setIsActive(false);
                player->setAlive(false);
                return;
            }
        }
    }

    void CollideSystem::didHitNono(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            
            if (box.contains(pos->getPosition().x, pos->getPosition().y) && nono->unKillable == false) {
                projectile->setIsActive(false);
                nono->disableNonoPlayer(sceneManager);
                sceneManager.getCurrentScene().removeEntity(e);
                return;
            }
        }
    }
    
    bool CollideSystem::isBlack(Position pos, sf::FloatRect box)
    {
        sf::Image imageUp;
        sf::Image imageDown;
        Position realSize(0 ,0);
        sf::Color color(0, 0, 0);
        sf::Color get;

        imageUp.loadFromFile("assets/sprites_statics/top_wall_lvl1.png");
        imageDown.loadFromFile("assets/sprites_statics/bottom_wall_lvl1.png");
        for (int a = 0; a < box.width; a++) {
            for (int b = 0; b < box.height; b++) {

                realSize.setX(pos.getPosition().x - 100);
                realSize.setY(pos.getPosition().y);

                if (pos.getPosition().x < 100)
                    return(true);

                if (pos.getPosition().y + b < 79)
                    get = imageUp.getPixel(realSize.getPosition().x + a, realSize.getPosition().y + b);
                else if (pos.getPosition().y + b > 127) {
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

    bool CollideSystem::canMove(Position pos, SceneManager &sceneManger, Position toCheck)
    {
        Position real(0, 0);
        Position toAdd(0, 0);

        if (toCheck.getPosition().x > 0)
            toAdd.setX(32);
        if (toCheck.getPosition().y > 0)
            toAdd.setY(15);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));
        sf::FloatRect playerBox(0, 0, 33, 15);

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER))
                continue;
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::FloatRect box = sprite->getSprite().getGlobalBounds();
            if (pos.getPosition().x + toAdd.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x + toAdd.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y + toAdd.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y + toAdd.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos, playerBox) == false)
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