#include "Script/Core/LuaScript.h"

LuaScript::LuaScript()
	:
	Script()
{
}

LuaScript::LuaScript(const std::string& id, bool active, Scene* parentScene)
	:
	Script(id, active, parentScene)
{
}

bool LuaScript::loadFromFile(const std::string& fileString)
{
	this->setFileString(fileString);

	return true;
}

void LuaScript::update(float deltaTime)
{
	/* the following is temp to test link/compile */

	/* initialize Lua */
	luaState = luaL_newstate();

	/* load Lua base libraries */
	luaL_openlibs(luaState);

	/* run the script */
	luaL_dofile(luaState, this->getFileString().c_str());

	/* cleanup Lua */
	lua_close(luaState);

	this->setActive(false);
}
