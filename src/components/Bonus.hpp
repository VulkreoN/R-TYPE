#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace R_TYPE {
    class Bonus : public Component {
        public:
            enum class BonusType {
                NONE = 0,
                SPEED = 1,
                LASER_DIAG = 2,
                NONO_LE_ROBOT = 3,
                // appparait avec un bonus 
                // peut se faire ejecter avec un button et tire en meme temps que le joueur
                // se fait attirer par le joueur

                DOUBLE = 4,
                LASER = 5,
            };
            Bonus(BonusType type);
            ~Bonus();
        
            BonusType getType();
        private:
            BonusType type;
    };
}

#endif