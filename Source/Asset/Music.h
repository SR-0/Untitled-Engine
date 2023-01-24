#pragma once

#include "Core/Asset.h"
#include <SFML/Audio/Music.hpp>

class Music : public sf::Music, public Asset<Music>
{
private: // data

	std::string fileString = std::string{};

public: // ctor(s)/dtor(s)

	Music(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Music(const std::string& id, const std::string& fileString, bool playNow = false, class Scene* parentScene = nullptr);

public: // getter(s)

	const std::string& getFileString() const;

public: // utility

	bool openFromFile(const std::string& fileString);

};
