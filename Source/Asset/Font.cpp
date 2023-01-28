#include "Asset/Font.h"
#include "Utility/Debug.h"

Font::Font(const std::string& id, Scene* parentScene)
	:
	sf::Font(),
	Asset<Font>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
}

Font::Font(const std::string& id, const std::string& path, Scene* parentScene)
	:
	sf::Font(),
	Asset<Font>(*this)
{
	this->setId(id);
	sf::Font::loadFromFile(path);
	this->setParentScene(parentScene);
}

Font::~Font()
{
}

const std::string& Font::getFileString() const
{
	return this->fileString;
}

bool Font::loadFromFile(const std::string& fileString)
{
	if (!sf::Font::loadFromFile(fileString))
	{
		debug::print("failed to load file for " + this->getId() + "\n");
		return false;
	}

	this->fileString = fileString;
	return true;
}
