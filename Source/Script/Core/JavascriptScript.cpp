#include "Script/Core/JavascriptScript.h"

JavascriptScript::JavascriptScript()
{
}

JavascriptScript::JavascriptScript(
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

JavascriptScript::JavascriptScript(
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

void JavascriptScript::run(float deltaTime)
{
	return; // @TODO
}

ScriptLanguage JavascriptScript::getScriptLanguage() const
{
	return ScriptLanguage::Javascript;
}
