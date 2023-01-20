#include "Manager/SceneManager.h"
#include "Core/Global.h"




#pragma region CTOR(S)/DTOR(S)

SceneManager::~SceneManager()
{
	this->removeScenes();
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void SceneManager::update(float deltaTime)
{
	for (auto& scene : this->scenes)
	{
		if (scene->isActive())
		{
			switch (scene->getState())
			{
				case Scene::State::Initialize:
				{
					scene->callInitialize();
					scene->setState(Scene::State::Update);
				}
				break;

				case Scene::State::Update:
				{
					scene->callUpdate(deltaTime);
				}
				break;

				case Scene::State::Terminate:
				{
					scene->callTerminate();
					scene->setState(Scene::State::Initialize);
					scene->setActive(false);
				}
				break;
			}
		}
	}
}

#pragma endregion CORE





#pragma region SCENE(S)

std::size_t SceneManager::getSceneCount() const
{
	return this->scenes.size();
}

Scene* SceneManager::getScene(std::size_t index)
{
	return this->scenes[index].get();
}

Scene* SceneManager::getScene(const std::string& id)
{
	for (std::size_t index = 0; index < this->scenes.size(); index++)
	{
		if (this->scenes[index]->getId() == id)
		{
			return this->scenes[index].get();
		}
	}

	return nullptr;
}

Scene* SceneManager::getSceneFront()
{
	return this->scenes.front().get();
}

Scene* SceneManager::getSceneBack()
{
	return this->scenes.back().get();
}

void SceneManager::removeScene(std::size_t index)
{
	this->scenes.erase(this->scenes.begin() + index);
}

void SceneManager::removeScene(const std::string& id)
{
	for (std::size_t index = 0; index < this->scenes.size(); index++)
	{
		if (this->scenes[index]->getId() == id)
		{
			this->scenes.erase(this->scenes.begin() + index);
			index--;
		}
	}
}

void SceneManager::removeScenes()
{
	this->scenes.clear();
}

void SceneManager::iterateScenes(const std::function<void(Scene&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->scenes.rbegin(); iter != this->scenes.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->scenes.begin(); iter != this->scenes.end(); iter++)
		return function(*iter->get());
}

#pragma endregion SCENE(S)