#include "Script/Core/JavascriptScript.h"

JavascriptScript::JavascriptScript()
	:
	Script()
{
}

JavascriptScript::JavascriptScript(const std::string& id, bool active, Scene* parentScene)
	:
	Script(id, active, parentScene)
{
}

bool JavascriptScript::loadFromFile(const std::string& fileString)
{
	this->setFileString(fileString);

	return false;
}

void JavascriptScript::update(float deltaTime)
{
	return; // @TODO
}
