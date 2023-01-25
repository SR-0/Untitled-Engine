#pragma once

#include <memory>
#include <functional>
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

	lua_State*	luaState	= nullptr;
	bool		newState	= false;

public: // ctor(s)/dtor(s)

	LuaScript();
	LuaScript(const LuaScript&) = delete;
	~LuaScript();
	
	LuaScript
	(
		const std::string&  id,
		const std::string&  fileString  = "",
		bool                active      = true,
		bool                repeating   = false,
		const sf::Time&     runInterval = sf::Time::Zero,
		class Scene*        parentScene = nullptr
	);
	
	
	LuaScript
	(
		const std::string&  id,
		const std::string&  fileString,
		bool                active,
		bool                repeating,
		float               runIntervalSeconds  = 0.000000f,
		class Scene*        parentScene         = nullptr
	);

public: // core

	virtual void run(float deltaTime) override final;

public:

	virtual ScriptLanguage getScriptLanguage() const override final;

};
