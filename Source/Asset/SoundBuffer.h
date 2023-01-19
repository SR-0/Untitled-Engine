#pragma once

#include <Core/Asset.h>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundBuffer : public sf::SoundBuffer, public Asset<SoundBuffer>
{
private:

	std::string fileString = std::string{};

public:

	SoundBuffer(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	SoundBuffer(const std::string& id, const std::string& file, class Scene* parentScene = nullptr);

public:

	const std::string& getFileString() const;

public:

	bool loadFromFile(const std::string& file);

};

