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
}