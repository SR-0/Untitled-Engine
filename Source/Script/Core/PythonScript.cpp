#include "Script/Core/PythonScript.h"

PythonScript::PythonScript()
{
}

PythonScript::PythonScript(
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

PythonScript::PythonScript(
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

void PythonScript::run(float deltaTime)
{
	return; // @TODO
}

ScriptLanguage PythonScript::getScriptLanguage() const
{
	return ScriptLanguage::Python;
}
