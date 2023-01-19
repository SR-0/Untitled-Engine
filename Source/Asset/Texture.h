#pragma once

#include "Core/Asset.h"

class Texture
	:
	public sf::Texture,
	public Asset<Texture>
{
private:

	std::string fileString = std::string{};

public:

	Texture(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Texture(const std::string& id, const std::string& path, class Scene* parentScene = nullptr);

public:

	const std::string& getFileString() const;

public:

	bool loadFromFile(const std::string& fileString);

};