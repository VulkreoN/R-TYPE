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
                DOUBLE = 3,
                LASER = 4,
            };
            Bonus(BonusType type);
            ~Bonus();
        
            BonusType getType();
        private:
            BonusType type;
    };
}

#endif