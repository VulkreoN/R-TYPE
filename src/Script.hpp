#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Velocity.hpp"
#include "Entity.hpp"
#include "Animation.hpp"

namespace R_TYPE {

    class Script {
        public: 

        bool turretScript();
        bool jorydeScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy);
        bool robotScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy);
        void spatialScript(std::shared_ptr<R_TYPE::IEntity> ennemy);
        bool bossScript(std::shared_ptr<R_TYPE::IEntity> ennemy, float leftCamera);
        private:
            sf::Clock clock;
            sf::Time lastFrame;
            sf::Time CurrentFrame;
            int repeat = 0;
    };
}

#endif