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
            if (component->getIsActive() == false)
                continue;
            didHitWall(sceneManager, e);
            // didHitProj(sceneManager, e);
            if (component->shootByPlayer() == false) {
                didHitPlayer(sceneManager, e);

                didHitNono(sceneManager, e);
            } else if (component->shootByPlayer() == true)
                didHitEnnemi(sceneManager, e);
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
            sf::IntRect box = sprite->getRect();
            box.width = box.width * 0.7;
            box.height = box.height * 0.7;

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
        auto pos = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        sf::IntRect playerBox = spritePlayer->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto spriteEnnemi = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            sf::IntRect ennemyBox = spriteEnnemi->getRect();

            if (boxCollide(playerBox, pos->getPosition(), ennemyBox, posEnnemi->getPosition())) {
                component->setAlive(false);
            }
        }
    }

    void CollideSystem::collideBonusPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto pos = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        sf::IntRect playerBox = spritePlayer->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::BONUS]) {
            auto bonus = Component::castComponent<Bonus>((*e)[IComponent::Type::BONUS]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posBonus = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sf::IntRect bonusBox = sprite->getRect();

            if (bonus->getActive() == false)
                continue;
            if (boxCollide(bonusBox, posBonus->getPosition(), playerBox, pos->getPosition())) {
                if (bonus->getType() == Bonus::BonusType::SPEED || component->getNono() == false) {
                    component->addBonus(bonus->getType());
                } else if (component->getNono() == true) {
                    addUpddateNono(sceneManager, player);
                    component->setLevelNono(component->getLevelNono() + 1);
                }
                bonus->setActive(false);
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
                nono->nextUpgrade();
            }
            if (nono->getUpgrade() == 1) {
                sprite->setRect(sf::IntRect(120, 69, 30, 21));
                nono->setState(Animation::State::LV2);
                auto anims = e->getFilteredComponents(IComponent::Type::ANIMATION);
                for (int i = 0; i < anims.size(); i++) {
                    auto anim_cast = Component::castComponent<Animation>(anims[i]);
                    if (anim_cast->getState() == nono->getState()) {
                        anim_cast->setRect(sf::IntRect(120, 69, 30, 21));
                    }
                }
            } else if (nono->getUpgrade() == 2) {
                sprite->setRect(sf::IntRect(170, 342, 32, 31));
                nono->setState(Animation::State::LV3);
                auto anims = e->getFilteredComponents(IComponent::Type::ANIMATION);
                for (int i = 0; i < anims.size(); i++) {
                    auto anim_cast = Component::castComponent<Animation>(anims[i]);
                    if (anim_cast->getState() == nono->getState()) {
                        anim_cast->setRect(sf::IntRect(170, 342, 32, 31));
                    }
                }
            }
        }
    }

    void CollideSystem::collideNonoPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        auto posPlayer = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        sf::IntRect playerBox = spritePlayer->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
            sf::IntRect nonoBox = sprite->getRect();

            if (boxCollide(playerBox, posPlayer->getPosition(), nonoBox, pos->getPosition()) && nono->isAlive == true) {
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
        
        sf::IntRect box = sprite->getRect();
        box.width *= 0.7;
        box.height *= 0.7;
        if (isBlack(*pos, box) == false) {
            component->setIsActive(false);
        }
    }

    void CollideSystem::didHitProj(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto proj = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            auto posProj = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sf::IntRect box = sprite->getRect();

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
        auto spriteProj = Component::castComponent<Sprite>((*project)[IComponent::Type::SPRITE]);
        sf::IntRect projBox = spriteProj->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
            sf::IntRect box = sprite->getRect();

            if (ennemy->IsAlive() == false)
                continue;

            if (sprite->getAngle() == 0) {
                if (boxCollide(projBox, pos->getPosition(), box, posEnnemi->getPosition())) {
                    if (projectile->getType() != Projectiles::Type::CHARGED&& projectile->getType() != Projectiles::Type::LASER_BOUCLE)
                        projectile->setIsActive(false);
                    if (ennemy->getLoot() != Bonus::BonusType::NONE) {
                        auto bonus = GameSystem::createBonus(300, 56, posEnnemi->getPosition(), ennemy->getLoot());
                        sceneManager.getCurrentScene().addEntity(bonus);
                    }
                    ennemy->setIsAlive(false);
                    return;
                }
            } else if (sprite->getAngle() == 180) {
                if (pos->getPosition().x < posEnnemi->getPosition().x && pos->getPosition().x > posEnnemi->getPosition().x - box.width 
                && pos->getPosition().y < posEnnemi->getPosition().y && pos->getPosition().y > posEnnemi->getPosition().y - box.height) {
                    if (projectile->getType() != Projectiles::Type::CHARGED&& projectile->getType() != Projectiles::Type::LASER_BOUCLE)
                        projectile->setIsActive(false);
                    if (ennemy->getLoot() != Bonus::BonusType::NONE) {
                        auto bonus = GameSystem::createBonus(300, 56, posEnnemi->getPosition(), ennemy->getLoot());
                        sceneManager.getCurrentScene().addEntity(bonus);
                    }
                    ennemy->setIsAlive(false);
                    return;
                }
            }
        }
    }

    void CollideSystem::didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        auto spritePlayer = Component::castComponent<Sprite>((*project)[IComponent::Type::SPRITE]);
        sf::IntRect playerBox = spritePlayer->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posPlayer = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sf::IntRect box = sprite->getRect();

            if (boxCollide(playerBox, pos->getPosition(), box, posPlayer->getPosition())) {
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
        auto spriteNono = Component::castComponent<Sprite>((*project)[IComponent::Type::SPRITE]);
        sf::IntRect nonoBox = spriteNono->getRect();
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::NONO]) {
            auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
            auto posNono = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);

            sf::IntRect box = sprite->getRect();
            
            if (boxCollide(nonoBox, pos->getPosition(), box, posNono->getPosition()) && nono->unKillable == false) {
                projectile->setIsActive(false);
                nono->disableNonoPlayer(sceneManager);
                nono->isAlive = false;
                return;
            }
        }
    }
    
    bool CollideSystem::isBlack(Position pos, sf::IntRect box)
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
        sf::IntRect playerBox(0, 0, 33, 15);

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER) || e->hasTag(IEntity::Tags::PROJECTILES) || e->hasTag(IEntity::Tags::ENNEMY))
                continue;
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::IntRect box = {posEnnemi->getPosition().x, posEnnemi->getPosition().y, 2608, 80};
            if (pos.getPosition().x + toAdd.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x + toAdd.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y + toAdd.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y + toAdd.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos, playerBox) == false)
                    return (false);
            }
        }
        return true;
    }

    bool CollideSystem::boxCollide(sf::IntRect box1, Position pos1, sf::IntRect box2, Position pos2)
    {
        if (pos1.getPosition().x + box1.width > pos2.getPosition().x && pos1.getPosition().x < pos2.getPosition().x + box2.width
        && pos1.getPosition().y + box1.height > pos2.getPosition().y && pos1.getPosition().y < pos2.getPosition().y + box2.height)
            return (true);
        return (false);
    }

    void CollideSystem::destroy()
    {
        std::cout << "Collide System destroyed" << std::endl;
    }
}