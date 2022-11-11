#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Component.hpp"
#include "Script.hpp"
#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Velocity.hpp"
#include "Bonus.hpp"
#include "Animation.hpp"

namespace R_TYPE {
    class Ennemy : public Component {
        public:
            enum class Type {
                TURRET,
                JORYDE_ALIEN,
                ROBOT_DINO,
                SPATIAL,
                BOSS,
            };
            Ennemy(Ennemy::Type type);
            ~Ennemy();

            /// @brief check if ennemy is alive 
            bool IsAlive() {return (isAlive);};

            /// @brief set ennemy alive
            void setIsAlive(bool _isAlive) {isAlive = _isAlive;};

            /// @brief Launch the good script with the type of the ennemy
            void launchScript(SceneManager &manager, std::shared_ptr<R_TYPE::IEntity> ennemy);

            static sf::Vector2f getDistance(SceneManager &manager, Position selfPos);

            static Velocity getVelocityTarget(sf::Vector2f distance);

            Type getType() {return (type);};

            Bonus::BonusType getLoot() {return (isLooting);};
            void setLoot(Bonus::BonusType loot) {isLooting = loot;};

            void setState(Animation::State state);

            Animation::State getState();

            void updateAngle(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy);
            void nextTimeSend() {timeSend += 1;};
            int getTimeSend() {return (timeSend);};
        private:
            bool isAlive;
            Bonus::BonusType isLooting;
            Type type;
            Script scripts;
            Animation::State _state;
            float angle;
            int timeSend;
    };
}

#endif