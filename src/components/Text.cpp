#include "Text.hpp"
#include <iostream>

namespace R_TYPE {
    Text::Text(std::string pathFont, std::string string, int size, sf::Color color):
    Component(Component::Type::TEXT)
    {
        sf::Font font;
        sf::String str(string);

        if(!font.loadFromFile(pathFont))
            std::cerr << "error to load the path for font\n";

        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setColor(color);
    }
    
    Text::~Text()
    {
    }

    void Text::printText(sf::RenderWindow window)
    {
        window.draw(text);
    }
    
}