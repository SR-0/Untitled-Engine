#pragma once

#include "Asset/SoundBuffer.h"
#include <SFML/Audio/Sound.hpp>

class Sound : public sf::Sound, public Asset<Sound>
{
public:

	Sound(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Sound(const SoundBuffer* soundBuffer, class Scene* parentScene = nullptr);
	Sound(const std::string& id, const SoundBuffer* soundBuffer, class Scene* parentScene = nullptr);

public:

	bool isPlaying() const;
	bool isPaused() const;
	bool isStopped() const;

};
