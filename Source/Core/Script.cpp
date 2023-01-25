#include "Core/Script.h"
#include "Core/Scene.h"
#include "Utility/Debug.h"
#include <filesystem>

Script::Script()
{
}

Script::Script(
	const std::string&  id,
	const std::string&  fileString,
	bool                active,
	bool                repeating,
	const sf::Time&     runInterval,
	class Scene*        parentScene)
{
	this->setId(id);
	this->setFileString(fileString);
	this->setRunInterval(runInterval);
	this->setRepeating(repeating);
	this->setActive(active);
	this->setParentScene(parentScene);
}

Script::Script(
	const std::string&  id,
	const std::string&  fileString,
	bool                active,
	bool                repeating,
	float               runIntervalSeconds,
	class Scene*        parentScene)
{
	this->setId(id);
	this->setFileString(fileString);
	this->setRunInterval(runIntervalSeconds);
	this->setRepeating(repeating);
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

bool Script::isRepeating() const
{
	return this->repeating;
}

Scene* Script::getParentScene() const
{
	return this->parentScene;
}

const std::string& Script::getFileString() const
{
	return this->fileString;
}

const sf::Time& Script::getTimeSinceLastRan() const
{
	return this->timeSinceLastRan;
}

const sf::Time& Script::getRunInterval() const
{
	return this->runInterval;
}

void Script::setId(const std::string& id)
{
	this->id = id;
}

void Script::setActive(bool active)
{
	this->active = active;
}

void Script::setRepeating(bool repeating)
{
	this->repeating = repeating;
}

void Script::setParentScene(Scene* parentScene)
{
	this->parentScene = parentScene;
}

void Script::setRunInterval(const sf::Time& runInterval)
{
	this->runInterval = runInterval;
}

void Script::setRunInterval(float seconds)
{
	this->runInterval = sf::Time(sf::seconds(seconds));
}

void Script::setFileString(const std::string& fileString)
{
	std::filesystem::path file{ fileString };

	if (!std::filesystem::exists(file))
		debug::print("script \"" + fileString + "\" was not found\n");

	this->fileString = fileString;
}

void Script::setTimeSinceLastRan(const sf::Time& timeSinceLastRan)
{
	this->timeSinceLastRan = timeSinceLastRan;
}

void Script::setTimeSinceLastRan(float seconds)
{
	this->timeSinceLastRan = sf::Time(sf::seconds(seconds));
}
