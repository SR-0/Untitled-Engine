#pragma once

#include "Core/Common.h"
#include "Core/Window.h"
#include "Manager/ClockManager.h"
#include "Manager/EventManager.h"
#include "Manager/SceneManager.h"
#include "Manager/AssetManager.h"
#include "Manager/ScriptManager.h"
#include "Scene/Core/EngineSystem.h"
#include "Scene/Core/EngineMenu.h"
#include "Scene/Core/EngineFooter.h"
#include "Scene/Core/EngineExplorer.h"
#include "Scene/Core/EngineModifier.h"
#include "Scene/Core/EngineEditor.h"
#include "Scene/Core/EngineAuxiliary.h"
#include "Utility/Utility.h"
#include "Utility/Random.h"
#include "Utility/Debug.h"

class Global
{
private: // data

	static Window*					window;
	static ClockManager*			clockManager;
	static EventManager*			eventManager;
	static SceneManager*			sceneManager;
	static AssetManager*			assetManager;
	static ScriptManager*			scriptManager;
	static EngineSystem*			engineSystem;
	static EngineMenu*				engineMenu;
	static EngineFooter*			engineFooter;
	static EngineExplorer*			engineExplorer;
	static EngineModifier*			engineModifier;
	static EngineEditor*			engineEditor;
	static EngineAuxiliary*			engineAuxiliary;
	static constexpr std::size_t	minFontSize = 10;
	static std::size_t				fontSize;
	static constexpr float			minUiScale = 1.000000f;
	static float					uiScale;
	static constexpr std::size_t	minMaxTicksPerSecond = 24; // limiting user to 0 (no limit) or at least 24 max tick per second
	static constexpr std::size_t	minMaxFramesPerSecond = 24; // limiting user to 0 (no limit) or at least 24 max frames per second (possible change) 
	static std::size_t				maxTicksPerSecond;
	static std::size_t				maxFramesPerSecond;
	static sf::Time					timeSinceLastUpdate;
	static sf::Time					timeSinceLastRender;
	static bool						updating;
	static bool						rendering;

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
		AssetManager&	assetManager,
		ScriptManager&	scriptManager
	);

	static void referenceScenes
	(
		EngineSystem&		engineSystem,
		EngineMenu&			engineMenu,
		EngineFooter&		engineFooter,
		EngineExplorer&		engineExplorer,
		EngineModifier&		engineModifier,
		EngineEditor&		engineEditor,
		EngineAuxiliary&	engineConsole
	);

public: // getter(s)

	static Window*					getWindow();
	static ClockManager*			getClockManager();
	static EventManager*			getEventManager();
	static SceneManager*			getSceneManager();
	static AssetManager*			getAssetManager();
	static ScriptManager*			getScriptManager();
	static EngineSystem*			getEngineSystem();
	static EngineMenu*				getEngineMenu();
	static EngineFooter*			getEngineFooter();
	static EngineExplorer*			getEngineExplorer();
	static EngineModifier*			getEngineModifier();
	static EngineEditor*			getEngineEditor();
	static EngineAuxiliary*			getEngineAuxiliary();
	static constexpr std::size_t	getMinFontSize();
	static std::size_t				getFontSize();
	static constexpr std::size_t	getMinUiScale();
	static float					getUiScale();
	static constexpr std::size_t	getMinMaxTicksPerSecond(); // limiting user to 0 (no limit) or at least 24 max tick per second
	static constexpr std::size_t	getMinMaxFramesPerSecond(); // limiting user to 0 (no limit) or at least 24 max frames per second (possible change) 
	static std::size_t				getMaxTicksPerSecond();
	static std::size_t				getMaxFramesPerSecond();
	static sf::Time					getTimeSinceLastUpdate();
	static sf::Time					getTimeSinceLastRender();
	static bool						isUpdating();
	static bool						isRendering();

public: // setter(s)

	static void setFontSize(std::size_t fontSize);
	static void setUiScale(float uiScale);
	static void setMaxTicksPerSecond(std::size_t maxTicksPerSecond);
	static void setMaxFramesPerSecond(std::size_t maxFramesPerSecond);

private: // setter(s) (for engine use only)

	static void setTimeSinceLastUpdate(const sf::Time& timeSinceLastUpdate);
	static void setTimeSinceLastRender(const sf::Time& timeSinceLastRender);
	static void setUpdating(bool updating);
	static void setRendering(bool rendering);


private: // friend(s)

	friend class Engine;
	friend class EngineAuxiliary;

};

using global = Global;