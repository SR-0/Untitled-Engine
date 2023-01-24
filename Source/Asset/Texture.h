#pragma once

#include "Core/Asset.h"

class Texture
	:
	public sf::Texture,
	public Asset<Texture>
{
private: // data

	std::string fileString = std::string{};

public: // ctor(s)/dtor(s)

	Texture(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Texture(const std::string& id, const std::string& path, class Scene* parentScene = nullptr);

public: // getter(s)

	const std::string& getFileString() const;

public: // utility

	bool loadFromFile(const std::string& fileString);

};