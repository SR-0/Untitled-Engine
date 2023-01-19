#include "Asset/Music.h"
#include "Utility/Debug.h"

Music::Music(const std::string& id, Scene* parentScene)
	:
	sf::Music(),
	Asset<Music>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
}

Music::Music(const std::string& id, const std::string& fileString, bool playNow, Scene* parentScene)
	:
	sf::Music(),
	Asset<Music>(*this)
{
	this->setId(id);
	this->openFromFile(fileString);
	this->setParentScene(parentScene);
	if (playNow)
		this->play();
}

const std::string& Music::getFileString() const
{
	return this->fileString;
}

bool Music::openFromFile(const std::string& fileString)
{
	if (!sf::Music::openFromFile(fileString))
	{
		debug::print("failed to load file for " + this->getId() + "\n");
		return false;
	}

	this->fileString = fileString;
	return true;
}
