#include "Script/Core/LuaScript.h"

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
	/* create script state*/
	this->luaState = luaL_newstate();

	/* load Lua base libraries */
	lua_gc(luaState, LUA_GCSTOP, 0);	// stop lua garbage collector (not needed for opening standard lua libs)
	luaL_openlibs(this->luaState);		// open standard lua libs for dev/user
	lua_gc(luaState, LUA_GCRESTART, 0);	// restart lua garbage collector after opening standard lua libs
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
	/* create script state*/
	this->luaState = luaL_newstate();

	/* load Lua base libraries */
	lua_gc(luaState, LUA_GCSTOP, 0);	// stop lua garbage collector (not needed for opening standard lua libs)
	luaL_openlibs(this->luaState);		// open standard lua libs for dev/user
	lua_gc(luaState, LUA_GCRESTART, 0);	// restart lua garbage collector after opening standard lua libs
}

LuaScript::~LuaScript()
{
	/* close the script */
	lua_close(this->luaState);
}

void LuaScript::run(float deltaTime)
{
	/* run the script */
	luaL_dofile(this->luaState, this->getFileString().c_str());
}

ScriptLanguage LuaScript::getScriptLanguage() const
{
	return ScriptLanguage::Lua;
}
