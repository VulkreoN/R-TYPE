#ifndef NONO_HPP_
#define NONO_HPP_

    #include "Sprite.hpp"
    #include "Velocity.hpp"
    #include "Bonus.hpp"
    #include "Animation.hpp"
    #include "SceneManager.hpp"
    #include "Entity.hpp"

namespace R_TYPE {
    class Nono : public Component {
        public:
            Nono();
            ~Nono();
        
            void nextUpgrade();
            int getUpgrade() {return upgrade;};

            sf::Vector2f getDistance(SceneManager &manager, Position selfPos);

            Velocity getVelocityTarget(sf::Vector2f distance);

            void setPosPlayer(std::shared_ptr<Position> pos) {posPlayer = pos;};
            std::shared_ptr<Position> getPosPlayer() {return posPlayer;};

            void setState(Animation::State state);

            Animation::State getState();

            void disableNonoPlayer(SceneManager &manager);
            bool isSnap;
            bool unKillable;
        private:
            int upgrade;
            std::shared_ptr<Position> posPlayer;
            Animation::State _state;
    };
}

#endif