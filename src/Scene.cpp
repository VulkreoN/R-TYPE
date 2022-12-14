#include "Scene.hpp"

#include <algorithm>

#include "Core.hpp"

namespace R_TYPE {

    Scene::Scene(std::function<std::unique_ptr<IScene>()> init):
    _initFunc(init)
    {

    }

    IScene &Scene::addEntity(std::shared_ptr<IEntity> entity)
    {
        for (auto &tag : entity->getTags()) {
            _taggedEntities[tag].push_back(entity);
        }
        return *this;
    }

    IScene &Scene::addEntities(std::vector<std::shared_ptr<IEntity>> entities)
    {
        for (auto &entity : entities) {
            for (auto &tag : entity->getTags()) {
                _taggedEntities[tag].push_back(entity);
            }
        }
        return *this;
    }

    void Scene::removeEntity(std::shared_ptr<IEntity> entity)
    {
        if (!entity)
            return;
        for (auto &tag : entity->getTags()) {
            auto it = std::find(_taggedEntities[tag].begin(), _taggedEntities[tag].end(), entity);
            if (it != _taggedEntities[tag].end())
                _taggedEntities[tag].erase(it);
        }
    }

    std::unique_ptr<IScene> Scene::initScene()
    {
        return _initFunc();
    }

    std::map<IEntity::Tags, std::vector<std::shared_ptr<IEntity>>> Scene::getTaggedEntities(std::vector<IEntity::Tags> tags)
    {
        std::map<IEntity::Tags, std::vector<std::shared_ptr<IEntity>>> taggedEntities;

        for (auto &tag : tags) {
            taggedEntities[tag] = _taggedEntities[tag];
        }
        return taggedEntities;
    }

    std::vector<std::shared_ptr<IEntity>> Scene::get_by_id(size_t id)
    {
        std::vector<std::shared_ptr<IEntity>> entities;

        for (auto &iterator : _taggedEntities) {
            for (auto &entity : iterator.second) {
                if (entity->get_id() == id)
                    entities.push_back(entity);
            }
        }
        return (entities);
    }

    std::vector<std::shared_ptr<IEntity>> &Scene::operator[](IEntity::Tags tag)
    {
        return _taggedEntities[tag];
    }
}
