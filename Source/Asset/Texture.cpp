#include "Asset/Texture.h"
#include "Utility/Debug.h"

Texture::Texture(const std::string& id, Scene* parentScene)
	:
	sf::Texture(),
	Asset<Texture>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
}

Texture::Texture(const std::string& id, const std::string& path, Scene* parentScene)
	:
	sf::Texture(),
	Asset<Texture>(*this)
{
	this->setId(id);
	sf::Texture::loadFromFile(path);
	this->setParentScene(parentScene);
}

const std::string& Texture::getFileString() const
{
	return this->fileString;
}

bool Texture::loadFromFile(const std::string& fileString)
{
	if (!sf::Texture::loadFromFile(fileString))
	{
		debug::print("failed to load file for " + this->getId() + "\n");
		return false;
	}

	this->fileString = fileString;
	return true;
}
