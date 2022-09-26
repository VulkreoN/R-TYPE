/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** EventSystem
*/

#ifndef EVENTSYSTEM_HPP_
#define EVENTSYSTEM_HPP_

#include "ISystem.hpp"

namespace R_TYPE {

    class EventSystem: public ISystem {
        public:
            EventSystem();
            ~EventSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;

        protected:
        private:
    };
}

#endif /* !EventSYSTEM_HPP_ */
