#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include "Component.hpp"

namespace R_TYPE {
    class Bonus : public Component {
        public:
            enum class Type {
                SPEED,
                DOUBLE,
                LASER_DIAG,
                LASER,
                NONE,
            };
            Bonus(Type type);
            ~Bonus();
        
            Type getType() {return (type);};
        private:
            Type type;
    };
}

#endif