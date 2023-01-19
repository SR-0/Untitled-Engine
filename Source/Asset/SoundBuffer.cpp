#include "Asset/SoundBuffer.h"
#include "Utility/Debug.h"

SoundBuffer::SoundBuffer(const std::string& id, Scene* parentScene)
	:
	sf::SoundBuffer(),
	Asset<SoundBuffer>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
}

SoundBuffer::SoundBuffer(const std::string& id, const std::string& file, Scene* parentScene)
	:
	sf::SoundBuffer(),
	Asset<SoundBuffer>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
	this->loadFromFile(file);
}

const std::string& SoundBuffer::getFileString() const
{
	return this->fileString;
}

bool SoundBuffer::loadFromFile(const std::string& fileString)
{
	if (!sf::SoundBuffer::loadFromFile(fileString))
	{
		debug::print("failed to load file for " + this->getId() + "\n");
		return false;
	}

	this->fileString = fileString;
	return true;
}

