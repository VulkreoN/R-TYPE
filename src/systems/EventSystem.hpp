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

    class NetworkSystem;

    class EventSystem: public ISystem {
        public:
            EventSystem(std::unique_ptr<NetworkSystem> network);
            ~EventSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void updateClient(SceneManager &manager, uint64_t deltaTime);
            void updateServer(SceneManager &manager, uint64_t deltaTime);
            void destroy() final;

            void setWindow(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<sf::View> _camera, std::shared_ptr<sf::View> _normalView);
            static bool isInit;

        protected:
        private:
            void handleKeyboard(SceneManager &manager, std::shared_ptr<Event> listener, sf::Event event);
            void handleMouse(SceneManager &, std::shared_ptr<Event> listener, sf::Event event);
            static std::map<int, std::vector<std::shared_ptr<Event>>> _event;
            
            std::unique_ptr<NetworkSystem> _network;
            std::shared_ptr<sf::RenderWindow> window;
            std::shared_ptr<sf::View> camera;
            std::shared_ptr<sf::View> normalView;
    };
}

#endif /* !EventSYSTEM_HPP_ */
