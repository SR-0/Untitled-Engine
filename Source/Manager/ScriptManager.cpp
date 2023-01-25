#include "ScriptManager.h"
#include "Core/Global.h"





#pragma region CTOR(S)/DTOR(S)

ScriptManager::~ScriptManager()
{
	this->removeScripts();
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void ScriptManager::update(float deltaTime)
{
	for (auto& script : this->scripts)
	{
		if (script->isActive() && (script->getTimeSinceLastRan() >= script->getRunInterval()))
		{
			#ifndef NDEBUG

			if (debug::isReportingScriptUpdates())
			{
				std::string scriptLanguage;

				switch (script->getScriptLanguage())
				{
					case ScriptLanguage::Chaiscript:    scriptLanguage = "Chaiscript";  break;
					case ScriptLanguage::CSharp:        scriptLanguage = "CSharp";      break;
					case ScriptLanguage::Javascript:    scriptLanguage = "Javascript";  break;
					case ScriptLanguage::Lua:           scriptLanguage = "Lua";         break;
					case ScriptLanguage::Python:        scriptLanguage = "Python";      break;
				}

				debug::print
				(
					"//////\n"
					"////\n"
					"//\n"
					"\n"
					"script id              = " + script->getId()                                       + "\n"
					"script source          = " + script->getFileString()                               + "\n"
					"script language        = " + scriptLanguage                                        + "\n"
					"script update interval = " + std::to_string(script->getRunInterval().asSeconds())  + " seconds\n"
					"\n"
				);

				script->run(deltaTime);

				debug::print
				(
					"\n"
					"//\n"
					"////\n"
					"//////\n"
					"\n"
				);
			}
			else
			{
				script->run(deltaTime);
			}

			#else

			script->run(deltaTime);

			#endif
			
			script->setTimeSinceLastRan(sf::Time::Zero);

			if (!script->isRepeating())
				script->setActive(false);
		}
		else if (script->isActive() && (script->getTimeSinceLastRan() < script->getRunInterval()))
		{
			script->setTimeSinceLastRan(script->getTimeSinceLastRan().asSeconds() + deltaTime);
		}
	}
}

#pragma endregion CORE





#pragma region SCENE(S)

std::size_t ScriptManager::getScriptCount() const
{
	return this->scripts.size();
}

Script* ScriptManager::getScript(std::size_t index)
{
	return this->scripts[index].get();
}

Script* ScriptManager::getScript(const std::string& id)
{
	for (std::size_t index = 0; index < this->scripts.size(); index++)
	{
		if (this->scripts[index]->getId() == id)
		{
			return this->scripts[index].get();
		}
	}

	return nullptr;
}

Script* ScriptManager::getScriptFront()
{
	return this->scripts.front().get();
}

Script* ScriptManager::getScriptBack()
{
	return this->scripts.back().get();
}

std::vector<std::shared_ptr<Script>>& ScriptManager::getScriptData()
{
	return this->scripts;
}

void ScriptManager::removeScript(std::size_t index)
{
	this->scripts.erase(this->scripts.begin() + index);
}

void ScriptManager::removeScript(const std::string& id)
{
	for (std::size_t index = 0; index < this->scripts.size(); index++)
	{
		if (this->scripts[index]->getId() == id)
		{
			this->scripts.erase(this->scripts.begin() + index);
			index--;
		}
	}
}

void ScriptManager::removeScripts(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->scripts.size(); index++)
		{
			if (static_cast<bool>(this->scripts[index]->getParentScene()) &&
				static_cast<bool>(this->scripts[index]->getParentScene() == scene))
			{
				this->scripts.erase(this->scripts.begin() + index);
				index--;
			}
		}

		return;
	}

	this->scripts.clear();
}

void ScriptManager::iterateScripts(const std::function<void(Script&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->scripts.rbegin(); iter != this->scripts.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->scripts.begin(); iter != this->scripts.end(); iter++)
		return function(*iter->get());
}

#pragma endregion SCENE(S)