#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Component.hpp"
#include "Script.hpp"
#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>
#include "Position.hpp"

namespace R_TYPE {
    class Ennemy : public Component {
        public:
            enum class Type {
                TURRET,
                JORYDE_ALIEN,
            };
            Ennemy(Ennemy::Type type);
            ~Ennemy();

            /// @brief check if ennemy is alive 
            bool IsAlive() {return (isAlive);};

            /// @brief Launch the good script with the type of the ennemy
            void launchScript(SceneManager &manager, Position selfPos);
        private:
            bool isAlive;
            Type type;
            Script scripts;
    };
}

#endif