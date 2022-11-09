#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <map>
#include <vector>
#include <memory>
#include "components/IComponent.hpp"

namespace R_TYPE {
    class IEntity {
    public:
        enum class Tags {
            SPRITE_2D,
            TEXT,
            COLLIDABLE,
            AUDIBLE,
            CALLABLE,
            PROJECTILES,
            DESTRUCTIBLE,
            PLAYER,
            UI,
            ENNEMY,
        };

        virtual ~IEntity() = default;

        ///@brief Add component to entity and update entity's tags accordingly
        virtual IEntity &addComponent(std::shared_ptr<IComponent> component) = 0;

        ///@brief Add component to entity and update entity's tags accordingly
        virtual IEntity &addComponents(std::vector<std::shared_ptr<IComponent>> components) = 0;

        /**
         * @brief Get entity's components
         * @return Returns a reference of the entity's components vector
         */
        // virtual std::map<IComponent::Type, std::shared_ptr<IComponent>> &getComponents() = 0;
        // /**
        //  * @brief Get entity's tags
        //  * @return Returns a reference of the entity's tags vector
        //  */
        virtual const std::vector<Tags> &getTags() const = 0;
        /**
         * @brief [] Operator overload that returns a pointer to a component or null
         *
         * @param type the type to search for
         * @return std::shared_ptr<IComponent> to that component or nullptr
         */
        virtual bool hasTag(Tags tag) const = 0;

        virtual std::shared_ptr<IComponent> &operator[](IComponent::Type type) = 0;
    };
}
#endif /* IENTITY_HPP */
