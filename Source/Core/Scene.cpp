#include "Core/Scene.h"

Scene::Scene()
{
	//
}

Scene::Scene(const std::string& id, bool active)
{
	this->id		= id;
	this->active	= active;
}

void Scene::initialize()
{
	this->functionInitialize();
}

void Scene::update(float deltaTime)
{
	this->functionUpdate(deltaTime);
}

void Scene::terminate()
{
	this->functionTerminate();
}

const std::string& Scene::getUuid() const
{
	return this->uuid;
}

const std::string& Scene::getId() const
{
	return this->id;
}

void Scene::setId(const std::string& id)
{
	this->id = id;
}

bool Scene::isActive() const
{
	return this->active;
}

bool Scene::isTimeScaled() const
{
	return this->timeScaled;
}

float Scene::getTimeScale() const
{
	return this->timeScale;
}

const Scene::State& Scene::getState() const
{
	return this->state;
}

const sf::Vector2f& Scene::getPosition() const
{
	return this->position;
}

std::size_t Scene::getRenderLayer() const
{
	return this->renderLayer;
}

bool Scene::isRenderEnabled() const
{
	return this->renderEnabled;
}

void Scene::setActive(bool active)
{
	this->active = active;
}

void Scene::setTimeScaled(bool timeScaled)
{
	this->timeScaled = timeScaled;
}

void Scene::setTimeScale(float timeScale)
{
	this->timeScale = timeScale;
}

void Scene::setState(const Scene::State& state)
{
	this->state = state;
}

void Scene::setInitialize(std::function<void()>&& functionInitialize)
{
	this->functionInitialize = std::move(functionInitialize);
}

void Scene::setUpdate(std::function<void(float)>&& functionUpdate)
{
	this->functionUpdate = std::move(functionUpdate);
}

void Scene::setTerminate(std::function<void()>&& functionTerminate)
{
	this->functionTerminate = std::move(functionTerminate);
}

void Scene::setPosition(const sf::Vector2f& position)
{
	this->position = position;
}

void Scene::setRenderLayer(std::size_t renderLayer)
{
	this->renderLayer = renderLayer;
}

void Scene::setRenderEnabled(bool renderEnabled)
{
	this->renderEnabled = renderEnabled;
}
