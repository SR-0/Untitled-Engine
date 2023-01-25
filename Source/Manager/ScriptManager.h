#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include "Script/Core/LuaScript.h"
#include "Script/Core/PythonScript.h"
#include "Script/Core/ChaiscriptScript.h"
#include "Script/Core/CSharpScript.h"
#include "Script/Core/JavascriptScript.h"

class ScriptManager
{
private: // data

	std::vector<std::shared_ptr<Script>>    scripts = {};
	std::mutex                              mutex   = std::mutex{};

public: // ctor(s)/dtor(s)

	ScriptManager() = default;
	ScriptManager(const ScriptManager&) = delete;
	ScriptManager(ScriptManager&&) = delete;
	~ScriptManager();

private: // operator overloading

	ScriptManager& operator = (const ScriptManager&) = delete;
	ScriptManager& operator = (ScriptManager&&) = delete;

private: // core

	void update(float deltaTime); // for use within Engine.cpp only

public: // bindings

	template <typename Derived, typename ... Args> Derived* createScript(Args ... args);
	std::size_t                                             getScriptCount() const;
	Script*                                                 getScript(std::size_t index);
	Script*                                                 getScript(const std::string& id);
	Script*                                                 getScriptFront();
	Script*                                                 getScriptBack();
	std::vector<std::shared_ptr<Script>>&                   getScriptData();
	void                                                    removeScript(std::size_t index);
	void                                                    removeScript(const std::string& id);
	void                                                    removeScripts(class Scene* scene = nullptr);
	void                                                    iterateScripts(const std::function<void(Script&)>& function, bool reversed = false);

private: // friend(s)

	friend class Engine;

};

template <typename Derived, typename ... Args>
Derived* ScriptManager::createScript(Args ... args)
{
	if (std::is_base_of<Script, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->scripts.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->scripts.back().get()->as<Derived>();
	}

	return nullptr;
}