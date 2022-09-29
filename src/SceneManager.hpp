#include <map>
#include <memory>

#include "IScene.hpp"

namespace R_TYPE {
    class SceneManager {
        public:
            enum class SceneType {
                NONE = -1,
                GAME,
                MAIN_MENU,
            };
        /**
         * @brief Add a scene to the scene manager
         * @param scene Scene to add
         * @param sceneType Type of the scene, needs to be unique for each scene
         */
        void addScene(std::unique_ptr<IScene> scene, SceneType sceneType);

        /**
         * @brief Returns the current scene
         * @return Reference of the current scene
         */
        IScene &getCurrentScene();

        /**
         * @brief Set the current scene to the scene corresponding to the given sceneType
         * @param sceneType Type of the scene to set as the current scene
         * @param initScene Boolean to reinitialize the scene, set too false by default
         */
        void setCurrentScene(SceneType scene, bool initScene = false);

        /// @brief  Check if game should close
        bool getShouldClose();

        /// @brief  Set if game should close
        void setShouldClose(bool shouldClose);

        SceneType getCurrentSceneType() {return (_currentScene);};

        private:
            std::map<SceneType, std::unique_ptr<IScene>> _scenes;
            SceneType _currentScene = SceneType::NONE;
            bool _shouldClose = false;
    };
}