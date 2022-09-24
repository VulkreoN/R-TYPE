#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>
#include <stdexcept>

#include "IComponent.hpp"

namespace R_TYPE {

    class Component : public IComponent {
        public:
            Component(const Type &type);
            const Type &getType() const;

        protected:
            Type _type = Type::TYPE_NB;
            bool _isInitialized = false;
    };
}
#endif /* COMPONENT_HPP */