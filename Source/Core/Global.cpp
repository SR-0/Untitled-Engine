#include "Global.h"

Window*			Global::window			= nullptr;
ClockManager*	Global::clockManager	= nullptr;
EventManager*	Global::eventManager	= nullptr;
SceneManager*	Global::sceneManager	= nullptr;
AssetManager*	Global::assetManager	= nullptr;
EngineSystem*	Global::engineSystem	= nullptr;
EngineConsole*	Global::engineConsole	= nullptr;
EngineMenu*		Global::engineMenu		= nullptr;
EngineFooter*	Global::engineFooter	= nullptr;
EngineExplorer*	Global::engineExplorer	= nullptr;
EngineModifier*	Global::engineModifier	= nullptr;
EngineEditor*	Global::engineEditor	= nullptr;

void Global::referenceCore(
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

void Global::referenceScenes(
	EngineSystem&	engineSystem,
	EngineConsole&	engineConsole,
	EngineMenu&		engineMenu,
	EngineFooter&	engineFooter,
	EngineExplorer&	engineExplorer,
	EngineModifier&	engineModifier,
	EngineEditor&	engineEditor)
{
	Global::engineSystem	= &engineSystem;
	Global::engineConsole	= &engineConsole;
	Global::engineMenu		= &engineMenu;
	Global::engineFooter	= &engineFooter;
	Global::engineExplorer	= &engineExplorer;
	Global::engineModifier	= &engineModifier;
	Global::engineEditor	= &engineEditor;
}

Window*			Global::getWindow()			{ return Global::window; }
ClockManager*	Global::getClockManager()	{ return Global::clockManager; }
EventManager*	Global::getEventManager()	{ return Global::eventManager; }
SceneManager*	Global::getSceneManager()	{ return Global::sceneManager; }
AssetManager*	Global::getAssetManager()	{ return Global::assetManager; }
EngineSystem*	Global::getEngineSystem()	{ return Global::engineSystem; }
EngineConsole*	Global::getEngineConsole()	{ return Global::engineConsole; }
EngineMenu*		Global::getEngineMenu()		{ return Global::engineMenu; }
EngineFooter*	Global::getEngineFooter()	{ return Global::engineFooter; }
EngineExplorer* Global::getEngineExplorer() { return Global::engineExplorer; }
EngineModifier* Global::getEngineModifier() { return Global::engineModifier; }
EngineEditor*	Global::getEngineEditor()	{ return Global::engineEditor; }
