#include "Script/Core/ChaiscriptScript.h"

ChaiscriptScript::ChaiscriptScript()
	:
	Script()
{
}

ChaiscriptScript::ChaiscriptScript(const std::string& id, bool active, Scene* parentScene)
	:
	Script(id, active, parentScene)
{
}

bool ChaiscriptScript::loadFromFile(const std::string& fileString)
{
	this->setFileString(fileString);

	return false;
}

void ChaiscriptScript::update(float deltaTime)
{
	return; // @TODO
}
