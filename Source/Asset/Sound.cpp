#include "Asset/Sound.h"
#include "Core/Scene.h"

Sound::Sound(const std::string& id, Scene* parentScene)
	:
	sf::Sound(),
	Asset<Sound>(*this)
{
	this->setId(id);
	this->setParentScene(parentScene);
}

Sound::Sound(const SoundBuffer* soundBuffer, Scene* parentScene)
	:
	sf::Sound(),
	Asset<Sound>(*this)
{
	this->setBuffer(*soundBuffer);
	this->setParentScene(parentScene);
}

Sound::Sound(const std::string& id, const SoundBuffer* soundBuffer, Scene* parentScene)
	:
	sf::Sound(),
	Asset<Sound>(*this)
{
	this->setId(id);
	this->setBuffer(*soundBuffer);
	this->setParentScene(parentScene);
}

bool Sound::isPlaying() const
{
	return this->getStatus() == sf::Sound::Playing;
}

bool Sound::isPaused() const
{
	return this->getStatus() == sf::Sound::Paused;
}

bool Sound::isStopped() const
{
	return this->getStatus() == sf::Sound::Stopped;
}
