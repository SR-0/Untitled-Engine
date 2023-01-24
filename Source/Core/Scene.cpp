#include "Core/Scene.h"
#include "Core/Global.h"

Scene::Scene()
{
	//
}

Scene::Scene(const std::string& id, bool active, const CodeUtilization& codeUtilization)
{
	this->id				= id;
	this->active			= active;
	this->codeUtilization	= codeUtilization;
}

void Scene::initialize()
{
	return;
}

void Scene::update(float deltaTime)
{
	return;
}

void Scene::terminate()
{
	return;
}

void Scene::callInitialize()
{
	switch (this->codeUtilization)
	{
		case CodeUtilization::DynamicFunction:
		{
			this->functionInitialize();
		}
		break;

		case CodeUtilization::VirtualOverride:
		{
			this->initialize();
		}
		break;

		case CodeUtilization::Combination:
		{
			switch (this->priorityCodeUtilization)
			{
				case CodeUtilization::DynamicFunction:
				{
					this->functionInitialize();
					this->initialize();
				}
				break;

				case CodeUtilization::VirtualOverride:
				{
					this->initialize();
					this->functionInitialize();
				}
				break;
			}
		}
		break;
	}
}

void Scene::callUpdate(float deltaTime)
{
	switch (this->codeUtilization)
	{
		case CodeUtilization::DynamicFunction:
		{
			this->functionUpdate(deltaTime);
		}
		break;

		case CodeUtilization::VirtualOverride:
		{
			this->update(deltaTime);
		}
		break;

		case CodeUtilization::Combination:
		{
			switch (this->priorityCodeUtilization)
			{
				case CodeUtilization::DynamicFunction:
				{
					this->functionUpdate(deltaTime);
					this->update(deltaTime);
				}
				break;

				case CodeUtilization::VirtualOverride:
				{
					this->update(deltaTime);
					this->functionUpdate(deltaTime);
				}
				break;
			}
		}
		break;
	}
}

void Scene::callTerminate()
{
	switch (this->codeUtilization)
	{
		case CodeUtilization::DynamicFunction:
		{
			this->functionTerminate();
		}
		break;

		case CodeUtilization::VirtualOverride:
		{
			this->terminate();
		}
		break;

		case CodeUtilization::Combination:
		{
			switch (this->priorityCodeUtilization)
			{
				case CodeUtilization::DynamicFunction:
				{
					this->functionInitialize();
					this->initialize();
				}
				break;

				case CodeUtilization::VirtualOverride:
				{
					this->initialize();
					this->functionInitialize();
				}
				break;
			}
		}
		break;
	}
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
	return bool
	(
		this->active &&
		(!this->isFocusRequired() ? true : global::getWindow()->isFocused()) &&
		(!this->isMouseEnteredRequired() ? true : global::getWindow()->isMouseEntered())
	);
}

bool Scene::isFocusRequired() const
{
	return this->focusRequired;
}

bool Scene::isMouseEnteredRequired() const
{
	return this->mouseEnteredRequired;
}

const SceneState& Scene::getSceneState() const
{
	return this->sceneState;
}

const CodeUtilization& Scene::getCodeUtilization() const
{
	return this->codeUtilization;
}

const CodeUtilization& Scene::getPriorityCodeUtilization() const
{
	return this->priorityCodeUtilization;
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

void Scene::setFocusRequired(bool focusRequired)
{
	this->focusRequired = focusRequired;
}

void Scene::setMouseEnteredRequired(bool mouseEnteredRequired)
{
	this->mouseEnteredRequired = mouseEnteredRequired;
}

void Scene::setSceneState(const SceneState& sceneState)
{
	this->sceneState = sceneState;
}

void Scene::setCodeUtilization(const CodeUtilization& codeUtilization)
{
	this->codeUtilization = codeUtilization;
}

void Scene::setPriorityCodeUtilization(const CodeUtilization& priorityCodeUtilization)
{
	if (priorityCodeUtilization == CodeUtilization::Combination)
	{
		this->priorityCodeUtilization = CodeUtilization::DynamicFunction; // default on "Combination" value attempt

		debug::print
		(
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
			"#\n"
			"#   [ WARNING ]\n"
			"#\n"
			"#   priority scene code utilization must a be value of either\n"
			"#   \"CodeUtilization::DynamicFunction\" or\n"
			"#   \"CodeUtilization::VirtualOverride\" - the value of\n"
			"#   \"CodeUtilization::Combination\" is not accepted as\n"
			"#   a priority code utilization - defaulted to value of\n"
			"#   \"CodeUtilization::DynamicFunction\" - in which case\n"
			"#   virutally overridden functions will automatically be called\n"
			"#   before dynamically set functions of Scene class instance\n"
			"#   \"", this->getId(), "\"\n"
			"#\n"
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
		);

		return;
	}

	this->priorityCodeUtilization = priorityCodeUtilization;
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
