#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <memory>
#include <vector>
#include <functional>
#include "IEntity.hpp"
#include "IScene.hpp"

namespace R_TYPE {
    class Scene : public IScene {
        public:
            Scene(std::function<std::unique_ptr<IScene>()> init);

            /// @brief Add entity to scene, you MUST call this function AFTER adding all the components to an entity
            IScene &addEntity(std::shared_ptr<IEntity> entity);

            /// @brief add several entities at once to a scene
            IScene &addEntities(std::vector<std::shared_ptr<IEntity>> entity);

            /// @brief Removes the given entity from scene
            void removeEntity(std::shared_ptr<IEntity> entity);

            /**
             * @brief Inits the scene by calling its init function
             * @return Returns the new scene's ptr
             */
            std::unique_ptr<IScene> initScene();

            /**
             * @brief Get entities with correcponding tags
             * @param tags Tags to search for
             * @return Returns a vector of entities
             */
            std::map<IEntity::Tags, std::vector<std::shared_ptr<IEntity>>> getTaggedEntities(std::vector<IEntity::Tags> tags);

            /**
             * @brief retrieves the entities for a given id
             *
             * @param id to filter by
             * @return std::vector<std::shared_ptr<IEntity>>&
             */
            std::vector<std::shared_ptr<IEntity>> get_by_id(size_t id);

            /**
             * @brief retrieves the entities for a given tag
             *
             * @param tag to filter by
             * @return std::vector<std::shared_ptr<IEntity>>&
             */
            std::vector<std::shared_ptr<IEntity>> &operator[](IEntity::Tags tag);
        
        private:
            /// @brief Entities sorted by tags
            std::map<IEntity::Tags, std::vector<std::shared_ptr<IEntity>>> _taggedEntities;
            /// @brief Scene's init function; called by GameSystem::init & Scene::reloadScene
            std::function<std::unique_ptr<IScene>()> _initFunc;
    };
}
#endif /* SCENE_HPP */
