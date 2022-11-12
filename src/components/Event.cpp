#include "Event.hpp"

namespace R_TYPE {
    Event::Event() : 
    Component(Component::Type::EVENT)
    {
        _isInitialized = true;
    }

    Event::~Event() 
    {

    }

    void Event::addKeyboardEvent(sf::Keyboard::Key key, ButtonCallbacks callbacks)
    {
        _keyboardMap[key] = callbacks;
    }

    void Event::removeKeyboardEvent(sf::Keyboard::Key key)
    {
        _keyboardMap.erase(key);
    }

    void Event::replaceKeyboardEvent(sf::Keyboard::Key oldKey, sf::Keyboard::Key newKey)
    {
        _keyboardMap[newKey] = _keyboardMap[oldKey];
        _keyboardMap.erase(oldKey);
    }

    void Event::addMouseEvent(sf::Mouse::Button key, MouseCallback func)
    {
        _mouseMap[key] = func;
    }

    void Event::removeMouseEvent(sf::Mouse::Button button)
    {
        _mouseMap.erase(button);
    }

    void Event::replaceMouseEvent(sf::Mouse::Button oldButton, sf::Mouse::Button newButton)
    {
        _mouseMap[newButton] = _mouseMap[oldButton];
        _mouseMap.erase(oldButton);
    }

    std::map<sf::Mouse::Button, MouseCallback> &Event::getMouseMappings()
    {
        return _mouseMap;
    }
}