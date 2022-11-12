#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {

    class Projectiles : public Component {
        public:
            enum class Type {
                LASER_BOUCLE,
                LASER,
                PRE_ROCKET,
                ROCKET,
                BASIC,
                CHARGED,
                TURRET,
                BOSS,
            };
            Projectiles(bool _byPlayer);
            ~Projectiles();

            bool shootByPlayer() {return (byPlayer);};
            void setIsActive(bool _isActive) {isActive = _isActive;};
            bool getIsActive() {return (isActive);};

            void setType(Type _type) {type = _type;};
            Type getType() {return (type);};

            void setSpriteAngle(sf::Vector2f distance, std::shared_ptr<IEntity> entity);
            void nextTimeSend() {timeSend += 1;};
            int getTimeSend() {return (timeSend);};

        private:
            bool byPlayer;
            bool isActive;
            Type type;
            int timeSend;
    };
}

#endif