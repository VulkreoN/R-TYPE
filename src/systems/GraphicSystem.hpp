/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#ifndef GRAPHICSYSTEM_HPP_
#define GRAPHICSYSTEM_HPP_

#include "ISystem.hpp"

namespace R_TYPE {
    class GraphicSystem: public ISystem {
        public:
            GraphicSystem();
            ~GraphicSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;

        protected:
        private:
    };
}

#endif /* !GraphicSYSTEM_HPP_ */
