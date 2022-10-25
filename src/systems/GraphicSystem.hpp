/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#ifndef GRAPHICSYSTEM_HPP_
#define GRAPHICSYSTEM_HPP_

#include "ISystem.hpp"
#include <SFML/Graphics.hpp>
#include "EventSystem.hpp"

namespace R_TYPE {
    class GraphicSystem: public ISystem {
        public:
            GraphicSystem();
            ~GraphicSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;

            static sf::RenderWindow *getWindow() {return (window);};

            void setCamera(SceneManager &manager);

        protected:
        private:
            static sf::RenderWindow *window;
            std::unique_ptr<EventSystem> eventSystem;
            sf::View *camera;
            bool _isInit;
    };
}

#endif /* !GraphicSYSTEM_HPP_ */
