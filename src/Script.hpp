#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <SFML/Graphics.hpp>

namespace R_TYPE {

    class Script {
        public: 

            void turretScript();
            void jorydeScript();
        private:
            sf::Clock clock;
            sf::Time lastFrame;
            sf::Time CurrentFrame;
    };
}

#endif