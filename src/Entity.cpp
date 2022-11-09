#include <iostream>
#include <algorithm>

#include "Entity.hpp"

namespace R_TYPE {
    const std::map<Entity::Tags, std::vector<std::vector<IComponent::Type>>> Entity::entityTags = {
        {IEntity::Tags::SPRITE_2D,
         {{IComponent::Type::SPRITE, IComponent::Type::POSITION}}},
        {Entity::Tags::TEXT,
         {{IComponent::Type::TEXT, IComponent::Type::POSITION}}},
        {Entity::Tags::COLLIDABLE,
         {{IComponent::Type::HITBOX}}},
        {Entity::Tags::PLAYER,
         {{IComponent::Type::PLAYER, IComponent::Type::VELOCITY, IComponent::Type::EVENT}}},
        {Entity::Tags::DESTRUCTIBLE,
         {{IComponent::Type::DESTRUCTIBLE}}},
        {Entity::Tags::CALLABLE,
         {{IComponent::Type::EVENT}}},
        {Entity::Tags::ENNEMY,
         {{IComponent::Type::ENNEMY}}},
        {Entity::Tags::BONUS,
         {{IComponent::Type::BONUS}}},
        {Entity::Tags::PROJECTILES,
         {{IComponent::Type::POSITION, IComponent::Type::VELOCITY, IComponent::Type::PROJECTILES}}},
        {Entity::Tags::NONO,
         {{IComponent::Type::NONO}}}
    };

    IEntity &Entity::addComponent(std::shared_ptr<IComponent> component) {
        bool notFound = false;

        IComponent::Type type = component->getType();
        _componentsType.push_back(type);
        _components[type].push_back(component);
        for (auto &tag : entityTags) {
            if (this->hasTag(tag.first))
                continue;
            for (auto &vec : tag.second) {
                notFound = false;
                for (auto &ctag : vec) {
                    if (std::find(_componentsType.begin(), _componentsType.end(), ctag) == _componentsType.end()) {
                        notFound = true;
                        break;
                    }
                }
                if (notFound)
                    continue;
                _tags.push_back(tag.first);
                break;
            }
        }
        return *this;
    }

    bool Entity::hasTag(Tags tag) const
    {
        return (std::find(_tags.begin(), _tags.end(), tag) != _tags.end());
    }

    IEntity &Entity::addComponents(std::vector<std::shared_ptr<IComponent>> components)
    {
        for (auto &component : components)
            this->addComponent(component);
        return *this;
    }

    std::map<IComponent::Type, std::vector<std::shared_ptr<IComponent>>> &Entity::getComponents() {
        return (_components);
    }

    std::shared_ptr<IComponent> &Entity::operator[](IComponent::Type type)
    {
        static std::shared_ptr<IComponent> null = nullptr;

        if (type >= IComponent::Type::TYPE_NB)
            throw std::invalid_argument("Entity: Component type not found");
        if (_components.find(type) != _components.end())
            return _components[type].at(0);
        return null;
    }

    std::vector<std::shared_ptr<IComponent>> Entity::getFilteredComponents(IComponent::Type components)
    {
        std::vector<std::shared_ptr<IComponent>> res;

        for (auto &c : _components) {
            if (c.first == components) {
                for (auto &cc : c.second)
                    res.push_back(cc);
            }
        }
        return res;

    }
}