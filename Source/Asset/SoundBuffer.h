#pragma once

#include <Core/Asset.h>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundBuffer : public sf::SoundBuffer, public Asset<SoundBuffer>
{
private: // data

	std::string fileString = std::string{};

public: // ctor(s)/dtor(s)

	SoundBuffer(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	SoundBuffer(const std::string& id, const std::string& file, class Scene* parentScene = nullptr);

public: // getter(s)

	const std::string& getFileString() const;

public: // utility

	bool loadFromFile(const std::string& fileString);

};

