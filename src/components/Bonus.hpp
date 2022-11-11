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
                NONO_LE_ROBOT = 2,
                UPGRADE = 3,
                // appparait avec un bonus 
                // peut se faire ejecter avec un button et tire en meme temps que le joueur
                // se fait attirer par le joueur
            };
            Bonus(BonusType type);
            ~Bonus();
        
            BonusType getType();
            void setType(BonusType type) { this->type = type; };

            void setActive(bool active) {isActive = active;};
            bool getActive() {return isActive;};

            void nextTimeSend() {timeSend += 1;};
            int getTimeSend() {return (timeSend);};
        private:
            BonusType type;
            bool isActive;
            int timeSend;
    };
}

#endif