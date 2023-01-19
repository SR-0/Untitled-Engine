#pragma once

#include "Core/Window.h"
#include "Manager/ClockManager.h"
#include "Manager/EventManager.h"
#include "Manager/SceneManager.h"
#include "Manager/AssetManager.h"
#include "Utility/Utility.h"
#include "Utility/Debug.h"
#include "Utility/Random.h"

class Global
{
private:

	static Window*			window;
	static ClockManager*	clockManager;
	static EventManager*	eventManager;
	static SceneManager*	sceneManager;
	static AssetManager*	assetManager;

private: // core (for use within Engine.cpp only)

	static void reference
	(
		Window&			window,
		ClockManager&	clockManager,
		EventManager&	eventManager,
		SceneManager&	sceneManager,
		AssetManager&	assetManager
	);

public: // getter(s)

	static Window*			getWindow();
	static ClockManager*	getClockManager();
	static EventManager*	getEventManager();
	static SceneManager*	getSceneManager();
	static AssetManager*	getAssetManager();

private: // friend(s)

	friend class Engine;

};

using global = Global;