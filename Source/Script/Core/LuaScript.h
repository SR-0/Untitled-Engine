#pragma once

#include "Core/Script.h"

extern "C"
{
	#include "Lua/lua.h"
	#include "Lua/lualib.h"
	#include "Lua/lauxlib.h"
}

class LuaScript : public Script
{
private: // data

	lua_State* luaState = nullptr;

public: // ctor(s)/dtor(s)

	LuaScript();
	LuaScript(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~LuaScript() override = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) override final;
	virtual void update(float deltaTime) override final;

};

