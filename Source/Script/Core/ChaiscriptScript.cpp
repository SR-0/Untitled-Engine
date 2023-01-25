#include "Script/Core/ChaiscriptScript.h"

ChaiscriptScript::ChaiscriptScript()
{
}

ChaiscriptScript::ChaiscriptScript(
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

ChaiscriptScript::ChaiscriptScript(
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

void ChaiscriptScript::run(float deltaTime)
{
	return; // @TODO
}

ScriptLanguage ChaiscriptScript::getScriptLanguage() const
{
	return ScriptLanguage::Chaiscript;
}
