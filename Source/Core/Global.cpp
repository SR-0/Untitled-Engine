#include "Global.h"

Window*			Global::window			= nullptr;
ClockManager*	Global::clockManager	= nullptr;
EventManager*	Global::eventManager	= nullptr;
SceneManager*	Global::sceneManager	= nullptr;
AssetManager*	Global::assetManager	= nullptr;

void Global::reference(
	Window&			window,
	ClockManager&	clockManager,
	EventManager&	eventManager,
	SceneManager&	sceneManager,
	AssetManager&	assetManager)
{
	Global::window			= &window;
	Global::clockManager	= &clockManager;
	Global::eventManager	= &eventManager;
	Global::sceneManager	= &sceneManager;
	Global::assetManager	= &assetManager;
}

Window*			Global::getWindow()			{ return Global::window; }
ClockManager*	Global::getClockManager()	{ return Global::clockManager; }
EventManager*	Global::getEventManager()	{ return Global::eventManager; }
SceneManager*	Global::getSceneManager()	{ return Global::sceneManager; }
AssetManager*	Global::getAssetManager()	{ return Global::assetManager; }