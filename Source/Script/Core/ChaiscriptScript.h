#pragma once

#include "Core/Script.h"

class ChaiscriptScript : public Script
{
public: // ctor(s)/dtor(s)

	ChaiscriptScript();
	ChaiscriptScript(const ChaiscriptScript&) = delete;
	virtual ~ChaiscriptScript() = default;
	
	ChaiscriptScript
	(
		const std::string&  id,
		const std::string&  fileString  = "",
		bool                active      = true,
		bool                repeating   = false,
		const sf::Time&     runInterval = sf::Time::Zero,
		class Scene*        parentScene = nullptr
	);
	
	ChaiscriptScript
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

