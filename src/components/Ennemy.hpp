#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {
    class Ennemy : public Component {
        public:
            enum class Type {
                TURRET,
                ALIEN_DRONE,
            };
            Ennemy();
            ~Ennemy();

            /// @brief check if ennemy is alive 
            bool IsAlive() {return (isAlive);};

            /// @brief Launch the good script with the type of the ennemy
            void launchScript();
        private:
            void script1();

            bool isAlive;
            Type type;
            sf::Clock clock;
    };
}

#endif