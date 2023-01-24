#include "Script/Core/CSharpScript.h"

CSharpScript::CSharpScript()
	:
	Script()
{
}

CSharpScript::CSharpScript(const std::string& id, bool active, Scene* parentScene)
	:
	Script(id, active, parentScene)
{
}

bool CSharpScript::loadFromFile(const std::string& fileString)
{
	this->setFileString(fileString);

	return false;
}

void CSharpScript::update(float deltaTime)
{
	return; // @TODO
}
