#include "Core/Engine.h"
#include "Core/Global.h"
#include "Scene/Core/EngineSystem.h"
#include "Scene/Core/EngineMenu.h"
#include "Scene/Core/EngineFooter.h"
#include "Scene/Core/EngineExplorer.h"
#include "Scene/Core/EngineModifier.h"
#include "Scene/Core/EngineEditor.h"
#include "Scene/Core/EngineAuxiliary.h"





#pragma region CTOR(S)/DTOR(S)

Engine::Engine()
{
	////////////////////////////
	// global core references //
	////////////////////////////
	//////
	////
	//
	
	global::referenceCore
	(
		this->window,
		this->clockManager,
		this->eventManager,
		this->sceneManager,
		this->assetManager,
		this->scriptManager
	);

	////////////////////////
	// create core scenes // order of creation is critical
	////////////////////////
	//////
	////
	//

	auto& sceneEngineSystem		= *global::getSceneManager()->createScene<EngineSystem>();
	auto& sceneEngineMenu		= *global::getSceneManager()->createScene<EngineMenu>();
	auto& sceneEngineFooter		= *global::getSceneManager()->createScene<EngineFooter>();
	auto& sceneEngineExplorer	= *global::getSceneManager()->createScene<EngineExplorer>();
	auto& sceneEngineModifier	= *global::getSceneManager()->createScene<EngineModifier>();
	auto& sceneEngineEditor		= *global::getSceneManager()->createScene<EngineEditor>();
	auto& sceneEngineAuxiliary	= *global::getSceneManager()->createScene<EngineAuxiliary>();

	/////////////////////////////
	// global scene references //
	/////////////////////////////
	//////
	////
	//

	global::referenceScenes
	(
		sceneEngineSystem,
		sceneEngineMenu,
		sceneEngineFooter,
		sceneEngineExplorer,
		sceneEngineModifier,
		sceneEngineEditor,
		sceneEngineAuxiliary
	);

	///////////////////////////////////////////
	// initial check for mouse within window //
	///////////////////////////////////////////
	//////
	////
	//

	if ((global::getEventManager()->getGlobalMousePosition().x >= global::getWindow()->getPosition().x)										&&
		(global::getEventManager()->getGlobalMousePosition().y >= global::getWindow()->getPosition().y)										&&
		(global::getEventManager()->getGlobalMousePosition().y <= global::getWindow()->getPosition().x + global::getWindow()->getSize().x)	&&
		(global::getEventManager()->getGlobalMousePosition().y <= global::getWindow()->getPosition().y + global::getWindow()->getSize().y)	)
	{
		global::getWindow()->setMouseEntered(true);
	}

	///////////////////////////
	// test code for scripts //
	///////////////////////////
	//////
	////
	//

	auto& luaScript = *global::getScriptManager()->createScript<LuaScript>("luaScriptTest");
	luaScript.loadFromFile("Source/Script/Testing/test.lua");
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

bool Engine::isRunning()
{
	return global::getWindow()->isOpen();
}

void Engine::update()
{
	global::getClockManager()->update();
	global::setTimeSinceLastUpdate(global::getTimeSinceLastUpdate() + global::getClockManager()->getDeltaTime());

	switch (global::getMaxTicksPerSecond())
	{
		case 0: // no tick limit
		{
			global::setUpdating(true);
		}
		break;

		default: // tick limit
		{
			if (global::getTimeSinceLastUpdate().asSeconds() >= (1.000000f / static_cast<float>(global::getMaxTicksPerSecond())))
				global::setUpdating(true);
		}
		break;
	}

	if (global::isUpdating())
	{
		global::getEventManager()->update(global::getTimeSinceLastUpdate().asSeconds());
		global::getSceneManager()->update(global::getTimeSinceLastUpdate().asSeconds());
		global::getAssetManager()->update(global::getTimeSinceLastUpdate().asSeconds());
		global::getScriptManager()->update(global::getTimeSinceLastUpdate().asSeconds());
		global::setTimeSinceLastUpdate(sf::Time::Zero);
		global::setUpdating(false);
	}
}

void Engine::render()
{
	global::setTimeSinceLastRender(global::getTimeSinceLastRender() + global::getClockManager()->getDeltaTime());

	switch (global::getMaxFramesPerSecond())
	{
		case 0: // no frame limit
		{
			global::setRendering(true);
		}
		break;

		default: // frame limit
		{
			if (global::getTimeSinceLastRender().asSeconds() >= (1.000000f / static_cast<float>((global::getMaxFramesPerSecond()))))
				global::setRendering(true);
		}
		break;
	}

	if (global::isRendering())
	{
		global::getWindow()->clear();
		global::getWindow()->draw();
		global::getWindow()->display();
		global::setTimeSinceLastRender(sf::Time::Zero);
		global::setRendering(false);
	}
}

#pragma endregion CORE