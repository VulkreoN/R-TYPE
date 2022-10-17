#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {

    class Projectiles : public Component {
        public:
            Projectiles(bool _byPlayer);
            ~Projectiles();

            bool shootByPlayer() {return (byPlayer);};
        private:
            bool byPlayer;
    };
}

#endif