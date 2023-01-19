#pragma once

#include "Asset/Rectangle.h"

class Tile : public Rectangle
{
public:

	enum class Type
	{
		Conventional,
		Isometric
	};

private:

	static std::size_t count;

private: // @TODO orient some data into v2s and v3s

	std::size_t		column				= 0;
	std::size_t		row					= 0;
	std::size_t		layer				= 0;
	float			depth				= 0;
	Tile::Type		type				= Tile::Type::Conventional;
	std::size_t		textureColumnCount	= 1;
	std::size_t		textureRowCount		= 1;
	std::size_t		textureStartColumn	= 0;
	std::size_t		textureStartRow		= 0;
	sf::Vector2u	textureSize			= sf::Vector2u(0, 0);
	sf::Vector2u	textureIndex		= sf::Vector2u(0, 0);
	bool			centeredOrigin		= false;

public:

	Tile(class Scene* parentScene = nullptr, class Port* port = nullptr);

	Tile(
		std::size_t			column,
		std::size_t			row,
		std::size_t			layer,
		float				depth,
		const sf::Vector2f&	scale,
		Texture*			texture,
		std::size_t			textureColumnCount,
		std::size_t			textureRowCount,
		std::size_t			textureStartColumn,
		std::size_t			textureStartRow,
		bool				centeredOrigin,
		const Tile::Type&	type,
		class Scene*		parentScene			= nullptr,
		class Port*			port				= nullptr);

public:

	void setup(
		std::size_t			column,
		std::size_t			row,
		std::size_t			layer,
		float				depth,
		const sf::Vector2f&	scale,
		Texture*			texture,
		std::size_t			textureColumnCount,
		std::size_t			textureRowCount,
		std::size_t			textureStartColumn,
		std::size_t			textureStartRow,
		bool				centeredOrigin,
		const Tile::Type&	type,
		class Scene*		parentScene			= nullptr,
		class Port*			port				= nullptr);

public:

	static std::size_t	getCount();
	std::size_t			getColumn() const;
	std::size_t			getRow() const;
	std::size_t			getLayer() const;
	sf::Vector3i		getCoordinates() const;
	float				getDepth() const;
	const Tile::Type&	getType() const;
	bool				isConventional() const;
	bool				isIsometric() const;
	std::size_t			getTextureColumnCount() const;
	std::size_t			getTextureRowCount() const;
	std::size_t			getTextureStartColumn() const;
	std::size_t			getTextureStartRow() const;
	sf::Vector2u		getTextureStartIndex() const;
	sf::Vector2u		getTextureSize() const;
	std::size_t			getTextureColumn() const;
	std::size_t			getTextureRow() const;
	sf::Vector2u		getTextureIndex() const;
	std::string			getIndexDetails() const;
	bool				isCenteredOrigin() const;

public:

	void			setColumn(std::size_t column);
	void			setRow(std::size_t row);
	void			setLayer(std::size_t layer);
	void			setDepth(float depth);
	void			setType(const Tile::Type& type);
	void			setTextureStartIndex(const sf::Vector2u& textureStartIndex);
	void			setTextureStartIndex(std::size_t textureStartColumn, std::size_t textureStartRow);
	void			setTextureIndex(const sf::Vector2u& textureIndex);
	void			setTextureIndex(std::size_t textureIndexColumn, std::size_t textureIndexRow);

};