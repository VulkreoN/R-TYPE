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
#include "AnimationManager.hpp"

namespace R_TYPE {

    class ClientSystem;

    class GraphicSystem: public ISystem {
        public:
            GraphicSystem(std::unique_ptr<ClientSystem> client);
            ~GraphicSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manaer, uint64_t deltaTime) final;
            void destroy() final;

            static const std::shared_ptr<sf::RenderWindow> &getWindow() {return (window);};
            static std::vector<std::shared_ptr<sf::Texture>> getTextures() {return (_textures);};
            void initAllSprites(SceneManager &manager);

            void setCamera(SceneManager &manager);

            static void updateCamera(float offset);

        protected:
        private:
            static std::shared_ptr<sf::RenderWindow> window;
            std::unique_ptr<EventSystem> eventSystem;
            static std::shared_ptr<sf::View> camera;
            std::shared_ptr<sf::View> normalView;
            static std::vector<std::shared_ptr<sf::Texture>> _textures;
            std::vector<std::string> _pathTextures;
            bool _isInit;
            AnimationManager amanager;

    };
}

#endif /* !GraphicSYSTEM_HPP_ */
