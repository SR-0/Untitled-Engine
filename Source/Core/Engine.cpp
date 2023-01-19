#include "Core/Engine.h"
#include "Core/Global.h"
#include "Scene/Core/EngineSystem.h"
#include "Scene/Core/EngineConsole.h"
#include "Scene/Core/EngineMenu.h"
#include "Scene/Core/EngineFooter.h"
#include "Scene/Core/EngineExplorer.h"
#include "Scene/Core/EngineModifier.h"
#include "Scene/Core/EngineEditor.h"

std::size_t	Engine::maxTicksPerSecond		= 0;
std::size_t	Engine::maxFramesPerSecond		= 0;
sf::Time	Engine::timeSinceLastUpdate		= sf::Time::Zero;
sf::Time	Engine::timeSinceLastRender		= sf::Time::Zero;
sf::Time	Engine::deltaTimeBuildUp		= sf::Time::Zero;
bool		Engine::updating				= false;
bool		Engine::rendering				= false;

#pragma region CTOR(S)/DTOR(S)

Engine::Engine()
	:
	Window(sf::Vector2u(1920, 1080), "Untitled Engine", sf::Style::None, sf::ContextSettings(0, 0, 4)),
	ClockManager(),
	EventManager(),
	SceneManager(),
	AssetManager()
{
	////////////////////////////
	// global core references //
	////////////////////////////
	//////
	////
	//
	
	global::referenceCore
	(
		*this,
		*this,
		*this,
		*this,
		*this
	);

	////////////////////////
	// create core scenes // order of creation is critical
	////////////////////////
	//////
	////
	//

	auto& sceneEngineSystem		= *this->createScene<EngineSystem>();
	auto& sceneEngineConsole	= *this->createScene<EngineConsole>();
	auto& sceneEngineMenu		= *this->createScene<EngineMenu>();
	auto& sceneEngineFooter		= *this->createScene<EngineFooter>();
	auto& sceneEngineExplorer	= *this->createScene<EngineExplorer>();
	auto& sceneEngineModifier	= *this->createScene<EngineModifier>();
	auto& sceneEngineEditor		= *this->createScene<EngineEditor>();

	/////////////////////////////
	// global scene references //
	/////////////////////////////
	//////
	////
	//

	global::referenceScenes
	(
		sceneEngineSystem,
		sceneEngineConsole,
		sceneEngineMenu,
		sceneEngineFooter,
		sceneEngineExplorer,
		sceneEngineModifier,
		sceneEngineEditor
	);

	///////////////////////////////////////////
	// initial check for mouse within window //
	///////////////////////////////////////////
	//////
	////
	//

	if (
		(this->getGlobalMousePosition().x >= this->getPosition().x)						&&
		(this->getGlobalMousePosition().y >= this->getPosition().y)						&&
		(this->getGlobalMousePosition().y <= this->getPosition().x + this->getSize().x) &&
		(this->getGlobalMousePosition().y <= this->getPosition().y + this->getSize().y) )
	{
		this->setMouseEntered(true);
	}
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

bool Engine::isRunning()
{
	return Window::isOpen();
}

void Engine::update()
{
	ClockManager::update();

	this->timeSinceLastUpdate += this->getDeltaTime();

	switch (this->maxTicksPerSecond)
	{
		case 0: // no tick limit
		{
			this->updating = true;
		}
		break;

		default: // tick limit
		{
			if (this->timeSinceLastUpdate.asSeconds() >= (1.000000f / static_cast<float>(maxTicksPerSecond)))
				this->updating = true;
		}
		break;
	}

	if (this->updating)
	{
		EventManager::update(this->timeSinceLastUpdate.asSeconds());
		SceneManager::update(this->timeSinceLastUpdate.asSeconds());
		AssetManager::update(this->timeSinceLastUpdate.asSeconds());

		this->timeSinceLastUpdate	= sf::Time::Zero;
		this->updating				= false;
	}
}

void Engine::render()
{
	this->timeSinceLastRender += this->getDeltaTime();

	switch (this->maxFramesPerSecond)
	{
		case 0: // no frame limit
		{
			this->rendering = true;
		}
		break;

		default: // frame limit
		{
			if (this->timeSinceLastRender.asSeconds() >= (1.000000f / static_cast<float>(maxFramesPerSecond)))
				this->rendering = true;
		}
		break;
	}

	if (this->rendering)
	{
		this->clear();
		this->draw();
		this->display();

		this->timeSinceLastRender	= sf::Time::Zero;
		this->rendering				= false;
	}
}

#pragma endregion CORE





#pragma region GETTER(S)

std::size_t Engine::getMaxTicksPerSecond()
{
	return Engine::maxTicksPerSecond;
}

std::size_t Engine::getMaxFramesPerSecond()
{
	return  Engine::maxFramesPerSecond;
}

#pragma endregion GETTER(S)





#pragma region SETTER(S)

void Engine::setMaxTicksPerSecond(std::size_t maxTicksPerSecond)
{
	if ((maxTicksPerSecond == 0) || (maxTicksPerSecond >= Engine::minMaxTicksPerSecond))
	{
		Engine::maxTicksPerSecond = maxTicksPerSecond;
	}
	else
	{
		Engine::maxTicksPerSecond = Engine::minMaxTicksPerSecond;
		debug::print("[ERROR] max ticks per second must be 0 (no limit) or a value of at least ", Engine::minMaxTicksPerSecond, " - anything less will negatively affect event handling beyond acceptable level - setting value to ", Engine::minMaxTicksPerSecond, "\n");
	}
}

void Engine::setMaxFramesPerSecond(std::size_t maxFramesPerSecond)
{
	if ((maxFramesPerSecond == 0) || (maxFramesPerSecond >= Engine::minMaxFramesPerSecond))
	{
		Engine::maxFramesPerSecond = maxFramesPerSecond;
	}
	else
	{
		Engine::maxFramesPerSecond = Engine::minMaxFramesPerSecond;
		debug::print("[ERROR] max frames per second must be 0 (no limit) or a value of at least ", Engine::minMaxFramesPerSecond, " - anything less will negatively affect video quality beyond acceptable level - setting value to ", Engine::minMaxFramesPerSecond, "\n");
	}
}

#pragma endregion SETTER(S)
