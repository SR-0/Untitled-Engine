#include "Core/Script.h"
#include "Core/Scene.h"

Script::Script()
{
}

Script::Script(const std::string& id, bool active, Scene* parentScene)
{
	this->setId(id);
	this->setActive(active);
	this->setParentScene(parentScene);
}

const std::string& Script::getUuid() const
{
	return this->uuid;
}

const std::string& Script::getId() const
{
	return this->id;
}

bool Script::isActive() const
{
	return this->active && (!this->parentScene ? true : static_cast<bool>(this->parentScene));
}

Scene* Script::getParentScene() const
{
	return this->parentScene;
}

const std::string& Script::getFileString() const
{
	return this->fileString;
}

void Script::setId(const std::string& id)
{
	this->id = id;
}

void Script::setActive(bool active)
{
	this->active = active;
}

void Script::setParentScene(Scene* parentScene)
{
	this->parentScene = parentScene;
}

void Script::setFileString(const std::string& fileString)
{
	this->fileString = fileString;
}
