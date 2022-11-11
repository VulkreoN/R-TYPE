#include "SceneManager.hpp"
#include <iostream>
#include <string>

namespace R_TYPE {

    void SceneManager::addScene(std::unique_ptr<IScene> scene, SceneType sceneType)
    {
        if (_scenes.find(sceneType) != _scenes.end())
            throw std::invalid_argument("SceneManager: Scene already exists");
        _scenes[sceneType] = std::move(scene);
    }

    IScene &SceneManager::getCurrentScene()
    {
        if (_scenes.find(_currentScene) == _scenes.end())
            throw std::runtime_error("SceneManager: Invalid current scene");
        return *_scenes[_currentScene];
    }

    void SceneManager::setCurrentScene(SceneType sceneType, bool initScene)
    {
        if (_scenes.find(sceneType) == _scenes.end())
            throw std::invalid_argument("SceneManager: Invalid scene type: " + std::to_string((int)sceneType));
        _currentScene = sceneType;
        if (initScene) {
            _scenes[_currentScene] = _scenes[_currentScene]->initScene();
        }
    }

    void SceneManager::setShouldClose(bool shouldClose)
    {
        _shouldClose = shouldClose;
    }

    bool SceneManager::getShouldClose()
    {
        return _shouldClose;
    }

    std::map<SceneManager::SceneType, std::unique_ptr<IScene>> &SceneManager::getScenes()
    {
        return _scenes;
    }

    std::vector<SceneManager::SceneType> SceneManager::getSceneTypeList()
    {
        std::vector<SceneType> sceneTypeList;

        for (auto &scene : _scenes) {
            sceneTypeList.push_back(scene.first);
        }
        return sceneTypeList;
    }

    IScene &SceneManager::getScene(SceneType sceneType)
    {
        if (_scenes.find(sceneType) == _scenes.end())
            throw std::invalid_argument("SceneManager: Invalid scene type: " + std::to_string((int)sceneType));
        return *_scenes[sceneType];
    }
}
