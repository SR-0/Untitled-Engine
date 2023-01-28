#include "Script/Core/LuaScript.h"
#include "Core/Global.h"
LuaScript::LuaScript()
{
}

LuaScript::LuaScript(
	const std::string&  id,
	const std::string&  fileString,
	bool                active,
	bool                repeating,
	const sf::Time&     runInterval,
	class Scene*        parentScene)
	:
	Script(id, fileString, active, repeating, runInterval, parentScene)
{
}

LuaScript::LuaScript(
	const std::string&  id,
	const std::string&  fileString,
	bool                active,
	bool                repeating,
	float               runIntervalSeconds,
	class Scene*        parentScene)
	:
	Script(id, fileString, active, repeating, runIntervalSeconds, parentScene)
{
}

LuaScript::~LuaScript()
{
}

void LuaScript::run(float deltaTime)
{
	// temp from ctor(s)
	this->luaState = luaL_newstate();
	
	// temp from ctor(s)
	lua_gc(luaState, LUA_GCSTOP, 0);    // stop lua garbage collector (not needed for opening standard lua libs)
	luaL_openlibs(this->luaState);      // open standard lua libs for dev/user
	lua_gc(luaState, LUA_GCRESTART, 0);	// restart lua garbage collector after opening standard lua libs

	//static const char* LUA_FILE = R"(
	//function getRunInterval()
	//	return 3
	//end
	//print("stuff")
	//)";


	auto binded = std::bind(&sf::Time::asSeconds, this->getRunInterval());

	auto _getRunInterval = [](lua_State*)
	{
	};

	/* run the script */
	//luaL_dostring(this->luaState, std::string("_thisRunInterval = " + std::to_string(this->getRunInterval().asSeconds())).c_str());

	luaL_dofile(this->luaState, "Source/Script/Testing/Core.lua");
	luaL_dofile(this->luaState, this->getFileString().c_str());

	//if (auto stack = lua_getglobal(this->luaState, "windowWidth"))
	//{
	//	lua_Number luaWindowWidth = lua_tonumber(this->luaState, stack);
	//	if (luaWindowWidth != global::getWindow()->getSize().x)
	//	{
	//		global::getWindow()->setSize(luaWindowWidth, global::getWindow()->getSize().y);
	//	}
	//}
	//
	//if (auto stack = lua_getglobal(this->luaState, "windowHeight"))
	//{
	//	lua_Number luaWindowHeight = lua_tonumber(this->luaState, stack);
	//	if (luaWindowHeight != global::getWindow()->getSize().y)
	//	{
	//		global::getWindow()->setSize(global::getWindow()->getSize().x, luaWindowHeight);
	//	}
	//}


	if (lua_getglobal(this->luaState, "getRunInterval"))
	{
		if (lua_isfunction(this->luaState, -1))
		{
			lua_pcall(this->luaState, 0, 1, 0);

			lua_Number luaRunInterval = lua_tonumber(this->luaState, -1);
			debug::printLine(luaRunInterval);
			this->setRunInterval(luaRunInterval);
		}
	}

	// temp from dtor(s)
	lua_close(this->luaState);
}

ScriptLanguage LuaScript::getScriptLanguage() const
{
	return ScriptLanguage::Lua;
}
