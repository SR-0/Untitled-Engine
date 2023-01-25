#include "Script/Core/CSharpScript.h"

CSharpScript::CSharpScript()
{
}

CSharpScript::CSharpScript(
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

CSharpScript::CSharpScript(
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

void CSharpScript::run(float deltaTime)
{
	return; // @TODO
}

ScriptLanguage CSharpScript::getScriptLanguage() const
{
	return ScriptLanguage::CSharp;
}
