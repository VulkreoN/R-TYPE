#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "IEntity.hpp"
#include "components/IComponent.hpp"

namespace R_TYPE {
    class Entity : public IEntity {
        public:
            ///@brief Map between Entity tags and combinaisons of Components tags
            static const std::map<Tags, std::vector<std::vector<IComponent::Type>>> entityTags;
            
            ///@brief Add component to entity and update entity's tags accordingly
            IEntity &addComponent(std::shared_ptr<IComponent> component);

            ///@brief Add component to entity and update entity's tags accordingly
            IEntity &addComponents(std::vector<std::shared_ptr<IComponent>> components);

            /**
            * @brief Get entity's components
            * @return Returns a reference of the entity's components vector
            */
            std::map<IComponent::Type, std::shared_ptr<IComponent>> &getComponents();
            /**
             * @brief Get entity's tags
             * @return Returns a reference of the entity's tags vector
             */
            const std::vector<Tags> &getTags() const {return (_tags);};
        private:
            std::vector<Tags> _tags;
            std::map<IComponent::Type, std::shared_ptr<IComponent>> _components;
            std::vector<IComponent::Type> _componentsType;
    };
}
#endif  // ENTITY_HPP