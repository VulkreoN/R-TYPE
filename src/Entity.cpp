#include <iostream>

#include "Entity.hpp"

namespace R_TYPE {
    const std::map<Entity::Tags, std::vector<std::vector<IComponent::Type>>> Entity::entityTags = {
        {IEntity::Tags::SPRITE_2D,
         {{IComponent::Type::SPRITE, IComponent::Type::POSITION}}},
        {Entity::Tags::TEXT,
         {{IComponent::Type::TEXT, IComponent::Type::POSITION}}},
        {Entity::Tags::AUDIBLE,
         {{IComponent::Type::MUSIC},
          {IComponent::Type::SOUND}}},
        {Entity::Tags::COLLIDABLE,
         {{IComponent::Type::HITBOX}}},
        {Entity::Tags::PLAYER,
         {{IComponent::Type::PLAYER}}},
        {Entity::Tags::DESTRUCTIBLE,
         {{IComponent::Type::DESTRUCTIBLE}}},
    };

    IEntity &Entity::addComponent(std::shared_ptr<IComponent> component) {
    }

    IEntity &Entity::addComponents(std::vector<std::shared_ptr<IComponent>> components)
    {}

    std::map<IComponent::Type, std::shared_ptr<IComponent>> &Entity::getComponents() {
    }
    
}