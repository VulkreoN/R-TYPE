/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** EventSystem
*/

#ifndef EVENTSYSTEM_HPP_
#define EVENTSYSTEM_HPP_

#include "ISystem.hpp"
#include "Event.hpp"

namespace R_TYPE {

    class EventSystem: public ISystem {
        public:
            EventSystem();
            ~EventSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;

            void setWindow(sf::RenderWindow *_window) {window = _window;};

        protected:
        private:
            void handleKeyboard(SceneManager &manager, std::shared_ptr<Event> listener, sf::Event event);
            static std::map<int, std::vector<std::shared_ptr<Event>>> _event;
            sf::RenderWindow *window;
    };
}

#endif /* !EventSYSTEM_HPP_ */
