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
    }

    void CollideSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
    
    }

    bool CollideSystem::canMove(SceneManager &sceneManager, Position pos)
    {
        const sf::Image image = GraphicSystem::getWindow()->capture();
        const sf::Color wallcolor(image.getPixel(201, 401));

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