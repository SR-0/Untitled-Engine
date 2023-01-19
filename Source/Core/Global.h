#pragma once

#include "Core/Window.h"
#include "Manager/ClockManager.h"
#include "Manager/EventManager.h"
#include "Manager/SceneManager.h"
#include "Manager/AssetManager.h"
#include "Scene/Core/EngineSystem.h"
#include "Scene/Core/EngineConsole.h"
#include "Scene/Core/EngineMenu.h"
#include "Scene/Core/EngineFooter.h"
#include "Scene/Core/EngineExplorer.h"
#include "Scene/Core/EngineModifier.h"
#include "Scene/Core/EngineEditor.h"
#include "Utility/Utility.h"
#include "Utility/Random.h"
#include "Utility/Debug.h"

class Global
{
private: // data

	static Window*			window;

	static ClockManager*	clockManager;
	static EventManager*	eventManager;
	static SceneManager*	sceneManager;
	static AssetManager*	assetManager;

	static EngineSystem*	engineSystem;
	static EngineConsole*	engineConsole;
	static EngineMenu*		engineMenu;
	static EngineFooter*	engineFooter;
	static EngineExplorer*	engineExplorer;
	static EngineModifier*	engineModifier;
	static EngineEditor*	engineEditor;

private: // ctor(s)/dtor(s)

	Global() = default;
	Global(const Global&) = delete;
	Global(Global&&) = delete;
	~Global() = default;

private: // operator overloading

	Global& operator = (const Global&) = delete;
	Global& operator = (Global&&) = delete;

private: // core (for use within Engine.cpp only)

	static void referenceCore
	(
		Window&			window,
		ClockManager&	clockManager,
		EventManager&	eventManager,
		SceneManager&	sceneManager,
		AssetManager&	assetManager
	);

	static void referenceScenes
	(
		EngineSystem&	 engineSystem,
		EngineConsole&	 engineConsole,
		EngineMenu&		 engineMenu,
		EngineFooter&	 engineFooter,
		EngineExplorer&	 engineExplorer,
		EngineModifier&	 engineModifier,
		EngineEditor&	 engineEditor
	);

public: // getter(s)

	static Window*			getWindow();
	static ClockManager*	getClockManager();
	static EventManager*	getEventManager();
	static SceneManager*	getSceneManager();
	static AssetManager*	getAssetManager();
	static EngineSystem*	getEngineSystem();
	static EngineConsole*	getEngineConsole();
	static EngineMenu*		getEngineMenu();
	static EngineFooter*	getEngineFooter();
	static EngineExplorer*	getEngineExplorer();
	static EngineModifier*	getEngineModifier();
	static EngineEditor*	getEngineEditor();

private: // friend(s)

	friend class Engine;

};

using global = Global;