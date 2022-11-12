#ifndef EVENT_HPP
#define EVENT_HPP

#include "Component.hpp"
#include "ButtonCallback.hpp"
#include <SFML/Graphics.hpp>
#include "MouseCallback.hpp"

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

        /**
         * @brief Adds a mouse event to the listener
         *
         * @param key the key to listen to
         * @param func the function to call when the key is pressed
         */
        void addMouseEvent(sf::Mouse::Button key, MouseCallback func);
        /**
         * @brief unbinds a mouseButton
         *
         * @param button The mouseButton to unbind
         */
        void removeMouseEvent(sf::Mouse::Button button);
        /**
         * @brief replaces the key for a listener
         *
         * @param oldKey the old key to take the callbacks from
         * @param newKey the new key that will receive the callbacks
         */
        void replaceMouseEvent(sf::Mouse::Button oldKey, sf::Mouse::Button newKey);

        std::map<sf::Keyboard::Key, ButtonCallbacks> getKeyboardMap() {return (_keyboardMap);};

        /// @brief gets a reference to the mouse mappings
        std::map<sf::Mouse::Button, MouseCallback> &getMouseMappings();
    private:

        std::map<sf::Keyboard::Key, ButtonCallbacks> _keyboardMap;
        std::map<sf::Mouse::Button, MouseCallback> _mouseMap;
    };
}

#endif