#ifndef ISCENE_HPP
#define ISCENE_HPP

#include <map>
#include <memory>
#include <vector>
#include "IEntity.hpp"

namespace R_TYPE {
    class IScene {
        public:
            virtual ~IScene() = default;

            /**
             * @brief retrieves the entities for a given id
             *
             * @param id to filter by
             * @return std::vector<std::shared_ptr<IEntity>>&
             */
            virtual std::vector<std::shared_ptr<IEntity>> get_by_id(size_t id) = 0;

            /// @brief Add entity to scene, you MUST call this function AFTER adding all the components to an entity
            virtual IScene &addEntity(std::shared_ptr<IEntity> entity) = 0;

            /// @brief add several entities at once to a scene
            virtual IScene &addEntities(std::vector<std::shared_ptr<IEntity>> entity) = 0;

            /// @brief Removes the given entity from scene
            virtual void removeEntity(std::shared_ptr<IEntity> entity) = 0;

            /**
             * @brief Inits the scene by calling its init function
             * @return Returns the new scene's ptr
             */
            virtual std::unique_ptr<IScene> initScene() = 0;

            /**
             * @brief Get entities with correcponding tags
             * @param tags Tags to search for
             * @return Returns a vector of entities
             */
            virtual std::map<IEntity::Tags, std::vector<std::shared_ptr<IEntity>>> getTaggedEntities(std::vector<IEntity::Tags> tags) = 0;

            virtual std::vector<std::shared_ptr<IEntity>> &operator[](IEntity::Tags tag) = 0;
    };
}
#endif /* ISCENE_HPP */
