#pragma once

#include "Core/Script.h"

class PythonScript : public Script
{
public: // ctor(s)/dtor(s)

	PythonScript();
	PythonScript(const PythonScript&) = delete;
	virtual ~PythonScript() = default;
	
	PythonScript
	(
		const std::string&  id,
		const std::string&  fileString  = "",
		bool                active      = true,
		bool                repeating   = false,
		const sf::Time&     runInterval = sf::Time::Zero,
		class Scene*        parentScene = nullptr
	);
	
	PythonScript
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

