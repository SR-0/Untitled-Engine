#pragma once

#include "Core/Scene.h"
#include <vector>
#include <memory>
#include <type_traits>
#include <thread>
#include <mutex>

class SceneManager
{
private: // data

	std::vector<std::shared_ptr<Scene>> scenes   = {};
	std::mutex                          mutex    = std::mutex{};

public: // ctor(s)/dtor(s)

	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	~SceneManager();

private: // operator overloading

	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

private: // core

	void update(float deltaTime); // for use within Engine.cpp only

public: // scenes

	template <typename Derived, typename ... Args> Derived* createScene(Args ... args);
	std::size_t                                             getSceneCount() const;
	Scene*                                                  getScene(std::size_t index);
	Scene*                                                  getScene(const std::string& id);
	Scene*                                                  getSceneFront();
	Scene*                                                  getSceneBack();
	std::vector<std::shared_ptr<Scene>>&                    getSceneData();
	void                                                    removeScene(std::size_t index);
	void                                                    removeScene(const std::string& id);
	void                                                    removeScenes();
	void                                                    iterateScenes(const std::function<void(Scene&)>& function, bool reversed = false);

private: // friend(s)

	friend class Engine;

};

template <typename Derived, typename ... Args>
Derived* SceneManager::createScene(Args ... args)
{
	if (std::is_base_of<Scene, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->scenes.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->scenes.back().get()->as<Derived>();
	}

	return nullptr;
}
