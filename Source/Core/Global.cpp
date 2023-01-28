#include "Global.h"

Window*             Global::window                      = nullptr;
ClockManager*       Global::clockManager                = nullptr;
EventManager*       Global::eventManager                = nullptr;
SceneManager*       Global::sceneManager                = nullptr;
AssetManager*       Global::assetManager                = nullptr;
ScriptManager*      Global::scriptManager               = nullptr;
EngineSystem*       Global::engineSystem                = nullptr;
EngineMenu*         Global::engineMenu                  = nullptr;
EngineFooter*       Global::engineFooter                = nullptr;
EngineExplorer*     Global::engineExplorer              = nullptr;
EngineModifier*     Global::engineModifier              = nullptr;
EngineEditor*       Global::engineEditor                = nullptr;
EngineAuxiliary*    Global::engineAuxiliary             = nullptr;
int                 Global::positiveOutlineThickness    = 0;
std::size_t         Global::fontSize                    = Global::minFontSize;  // testing
float               Global::uiScale                     = Global::minUiScale;   // testing
std::size_t         Global::maxTicksPerSecond           = 0;                    // no limit
std::size_t         Global::maxFramesPerSecond          = 0;                    // no limit
sf::Time            Global::timeSinceLastUpdate         = sf::Time::Zero;
sf::Time            Global::timeSinceLastRender         = sf::Time::Zero;
bool                Global::updating                    = false;
bool                Global::rendering                   = false;

void Global::referenceCore(
	Window&         window,
	ClockManager&   clockManager,
	EventManager&   eventManager,
	SceneManager&   sceneManager,
	AssetManager&   assetManager,
	ScriptManager&  scriptManager)
{
	Global::window          = &window;
	Global::clockManager    = &clockManager;
	Global::eventManager    = &eventManager;
	Global::sceneManager    = &sceneManager;
	Global::assetManager    = &assetManager;
	Global::scriptManager   = &scriptManager;
}

void Global::referenceScenes(
	EngineSystem&       engineSystem,
	EngineMenu&         engineMenu,
	EngineFooter&       engineFooter,
	EngineExplorer&     engineExplorer,
	EngineModifier&     engineModifier,
	EngineEditor&       engineEditor,
	EngineAuxiliary&    engineAuxiliary)
{
	Global::engineSystem    = &engineSystem;
	Global::engineMenu      = &engineMenu;
	Global::engineFooter    = &engineFooter;
	Global::engineExplorer  = &engineExplorer;
	Global::engineModifier  = &engineModifier;
	Global::engineEditor    = &engineEditor;
	Global::engineAuxiliary = &engineAuxiliary;
}

Window*                 Global::getWindow()                     { return Global::window;                }
ClockManager*           Global::getClockManager()               { return Global::clockManager;          }
EventManager*           Global::getEventManager()               { return Global::eventManager;          }
SceneManager*           Global::getSceneManager()               { return Global::sceneManager;          }
AssetManager*           Global::getAssetManager()               { return Global::assetManager;          }
ScriptManager*          Global::getScriptManager()              { return Global::scriptManager;         }
EngineSystem*           Global::getEngineSystem()               { return Global::engineSystem;          }
EngineMenu*             Global::getEngineMenu()                 { return Global::engineMenu;            }
EngineFooter*           Global::getEngineFooter()               { return Global::engineFooter;          }
EngineExplorer*         Global::getEngineExplorer()             { return Global::engineExplorer;        }
EngineModifier*         Global::getEngineModifier()             { return Global::engineModifier;        }
EngineEditor*           Global::getEngineEditor()               { return Global::engineEditor;          }
EngineAuxiliary*        Global::getEngineAuxiliary()            { return Global::engineAuxiliary;       }
constexpr std::size_t   Global::getMinFontSize()                { return Global::minFontSize;           }
int                     Global::getPositiveOutlineThickness()   { return Global::positiveOutlineThickness; }
std::size_t             Global::getFontSize()                   { return Global::fontSize;              }
constexpr std::size_t   Global::getMinUiScale()                 { return Global::minUiScale;            }
float                   Global::getUiScale()                    { return Global::uiScale;               }
constexpr std::size_t   Global::getMinMaxTicksPerSecond()       { return Global::minMaxTicksPerSecond;  }
constexpr std::size_t   Global::getMinMaxFramesPerSecond()      { return Global::minMaxFramesPerSecond; }
std::size_t             Global::getMaxTicksPerSecond()          { return Global::maxTicksPerSecond;     }
std::size_t             Global::getMaxFramesPerSecond()         { return Global::maxFramesPerSecond;    }
sf::Time                Global::getTimeSinceLastUpdate()        { return Global::timeSinceLastUpdate;   }
sf::Time                Global::getTimeSinceLastRender()        { return Global::timeSinceLastRender;   }
bool                    Global::isUpdating()                    { return Global::updating;              }
bool                    Global::isRendering()                   { return Global::rendering;             }

void Global::setFontSize(std::size_t fontSize)
{
	if (fontSize >= Global::minFontSize)
	{
		Global::fontSize = fontSize;
	}
	else
	{
		Global::fontSize = Global::minFontSize;
		debug::print("[ERROR] min font size must be a value of ", Global::minFontSize, " or higher - setting value to ", Global::minFontSize, "\n");
	}
}

void Global::setUiScale(float uiScale)
{
	if (uiScale >= Global::minUiScale)
	{
		Global::uiScale = uiScale;
	}
	else
	{
		Global::uiScale = Global::minUiScale;
		debug::print("[ERROR] min UI scale must be a value of ", Global::minUiScale, " or higher - setting value to ", Global::minUiScale, "\n");
	}
}

void Global::setPositiveOutlineThickness(int positiveOutlineThickness)
{
	Global::positiveOutlineThickness = positiveOutlineThickness;
}

void Global::setMaxTicksPerSecond(std::size_t maxTicksPerSecond)
{
	if ((maxTicksPerSecond == 0) || (maxTicksPerSecond >= Global::minMaxTicksPerSecond))
	{
		Global::maxTicksPerSecond = maxTicksPerSecond;
	}
	else
	{
		Global::maxTicksPerSecond = Global::minMaxTicksPerSecond;
		debug::print("[ERROR] max ticks per second must be 0 (no limit) or a value of at least ", Global::minMaxTicksPerSecond, " - anything less will negatively affect event handling beyond acceptable level - setting value to ", Global::minMaxTicksPerSecond, "\n");
	}
}

void Global::setMaxFramesPerSecond(std::size_t maxFramesPerSecond)
{
	if ((maxFramesPerSecond == 0) || (maxFramesPerSecond >= Global::minMaxFramesPerSecond))
	{
		Global::maxFramesPerSecond = maxFramesPerSecond;
	}
	else
	{
		Global::maxFramesPerSecond = Global::minMaxFramesPerSecond;
		debug::print("[ERROR] max frames per second must be 0 (no limit) or a value of at least ", Global::minMaxFramesPerSecond, " - anything less will negatively affect video quality beyond acceptable level - setting value to ", Global::minMaxFramesPerSecond, "\n");
	}
}

void Global::setTimeSinceLastUpdate(const sf::Time& timeSinceLastUpdate)
{
	Global::timeSinceLastUpdate = timeSinceLastUpdate;
}

void Global::setTimeSinceLastRender(const sf::Time& timeSinceLastRender)
{
	Global::timeSinceLastRender = timeSinceLastRender;
}

void Global::setUpdating(bool updating)
{
	Global::updating = updating;
}

void Global::setRendering(bool rendering)
{
	Global::rendering = rendering;
}
