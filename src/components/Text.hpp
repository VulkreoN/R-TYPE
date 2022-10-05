#ifndef TEXT_HPP
#define TEXT_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Position.hpp>

namespace R_TYPE {
    class Text : public Component{
    public:
        /** @brief init Text Class
         * @param path path to the front you want to use
         * @param string string you want print
         * @param size size you want for your text
         * @param color color you want for the text
         **/
        Text(std::string pathFont, std::string string, int size, sf::Color color);
        ~Text();

        /// @brief Print text
        void printText(sf::RenderWindow window, Position position);
    private:
        sf::Text text;
        /* data */
    };
}

#endif
