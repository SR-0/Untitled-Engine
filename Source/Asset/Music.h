#pragma once

#include "Core/Asset.h"
#include <SFML/Audio/Music.hpp>

class Music : public sf::Music, public Asset<Music>
{
private:

	std::string fileString = std::string{};

public:

	Music(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Music(const std::string& id, const std::string& fileString, bool playNow = false, class Scene* parentScene = nullptr);

public:

	const std::string& getFileString() const;

public:

	bool openFromFile(const std::string& fileString);

};
