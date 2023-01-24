#include "Script/Core/PythonScript.h"

PythonScript::PythonScript()
	:
	Script()
{
}

PythonScript::PythonScript(const std::string& id, bool active, Scene* parentScene)
	:
	Script(id, active, parentScene)
{
}

bool PythonScript::loadFromFile(const std::string& fileString)
{
	this->setFileString(fileString);

	return false;
}

void PythonScript::update(float deltaTime)
{
	return; // @TODO
}
