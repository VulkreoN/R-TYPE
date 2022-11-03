/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#ifndef GRAPHICSYSTEM_HPP_
#define GRAPHICSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "ISystem.hpp"
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
            static std::vector<std::shared_ptr<sf::Texture>> getTextures() {return (_textures);};
            void initAllSprites(SceneManager &manager);

            void setCamera(SceneManager &manager);

        protected:
        private:
            static sf::RenderWindow *window;
            std::unique_ptr<EventSystem> eventSystem;
            sf::View *camera;
            static std::vector<std::shared_ptr<sf::Texture>> _textures;
            std::vector<std::string> _pathTextures;
            bool _isInit;
    };
}

#endif /* !GraphicSYSTEM_HPP_ */
