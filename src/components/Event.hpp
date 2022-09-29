#ifndef EVENT_HPP
#define EVENT_HPP

#include "Component.hpp"
#include "ButtonCallback.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {
    class Event : public Component {
    public:
        Event();
        ~Event();

        /**
         * @brief Adds a keyboard event to the listener
         *
         * @param key the key to listen to
         * @param callsbacks the callbacks to call when the key is interacted with
         */
        void addKeyboardEvent(sf::Keyboard::Key key, ButtonCallbacks callbacks);
        /**
         * @brief unbinds a key
         *
         * @param key The key to unbind
         */
        void removeKeyboardEvent(sf::Keyboard::Key key);
        /**
         * @brief updates the key for a listener
         *
         * @param oldKey the old key to take the callbacks from
         * @param newKey the new key that will receive the callbacks
         */
        void replaceKeyboardEvent(sf::Keyboard::Key oldKey, sf::Keyboard::Key newKey);

        std::map<sf::Keyboard::Key, ButtonCallbacks> getKeyboardMap() {return (_keyboardMap);};
    private:

        std::map<sf::Keyboard::Key, ButtonCallbacks> _keyboardMap;
    };
}

#endif