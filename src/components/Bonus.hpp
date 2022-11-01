#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace R_TYPE {
    class Bonus : public Component {
        public:
            enum class BonusType {
                SPEED,
                DOUBLE,
                LASER_DIAG,
                LASER,
                NONE,
            };
            Bonus(BonusType type);
            ~Bonus();
        
            BonusType getType() {return (type);};
        private:
            BonusType type;
    };
}

#endif