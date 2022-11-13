#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>
#include <stdexcept>

#include "IComponent.hpp"

namespace R_TYPE {

    class Component : public IComponent {
        public:
            Component(const Type &type);
            virtual ~Component() = default;
            const Type &getType() const;

            /// @brief Fonction to get a component from Entity
            /// @tparam T Component class you want 
            /// @param component components inside the Entity class (voir graphic system)
            /// @return 
            template <typename T>
            static std::shared_ptr<T> castComponent(std::shared_ptr<IComponent> component)
            {
                std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(component);

                if (res == nullptr)
                    throw std::runtime_error("Component: dynamic_pointer_cast failed");
                return res;
            }
        protected:
            Type _type = Type::TYPE_NB;
            bool _isInitialized = false;
    };
    template <typename T>
    std::shared_ptr<T> castComponent(std::shared_ptr<IComponent> component)
    {
        std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(component);

        if (res == nullptr)
            throw std::runtime_error("Component: dynamic_pointer_cast failed");
        return res;
    }
}
#endif /* COMPONENT_HPP */