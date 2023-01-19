#pragma once

#include "Core/Asset.h"
#include <SFML/Graphics/Font.hpp>

class Font
	:
	public sf::Font,
	public Asset<Font>
{
private:

	std::string fileString = std::string{};

public:

	Font(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Font(const std::string& id, const std::string& path, class Scene* parentScene = nullptr);
	virtual ~Font();

public:

	const std::string& getFileString() const;

public:

	bool loadFromFile(const std::string& fileString);

};