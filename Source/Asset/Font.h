#pragma once

#include "Core/Asset.h"
#include <SFML/Graphics/Font.hpp>

class Font
	:
	public sf::Font,
	public Asset<Font>
{
private: // data

	std::string fileString = std::string{};

public: // ctor(s)/dtor(s)

	Font(const std::string& id = "unidentified", class Scene* parentScene = nullptr);
	Font(const std::string& id, const std::string& path, class Scene* parentScene = nullptr);
	virtual ~Font();

public: // getter(s)

	const std::string& getFileString() const;

public: // utility

	bool loadFromFile(const std::string& fileString);

};