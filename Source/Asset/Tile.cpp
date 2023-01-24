#include "Asset/Tile.h"
#include "Core/Scene.h"
#include "Core/Port.h"

std::size_t Tile::count = 0;

Tile::Tile(Scene* scene, Port* port)
{
	count++;
}

Tile::Tile(
	std::size_t			column,
	std::size_t			row,
	std::size_t			layer,
	float				depth,
	const sf::Vector2f& scale,
	Texture*			texture,
	std::size_t			textureColumnCount,
	std::size_t			textureRowCount,
	std::size_t			textureStartColumn,
	std::size_t			textureStartRow,
	bool				centeredOrigin,
	const TileType&		tileType,
	Scene*				parentScene,
	Port*				port)
	:
	Rectangle("tile" + std::to_string(count))
{
	setup
	(
		column,
		row,
		layer,
		depth,
		scale,
		texture,
		textureColumnCount,
		textureRowCount,
		textureStartColumn,
		textureStartRow,
		centeredOrigin,
		tileType,
		parentScene,
		port
	);

	Tile::count++;
}

void Tile::setup(
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
	const TileType&		tileType,
	Scene*				parentScene,
	Port*				port)
{
	this->textureColumnCount	= textureColumnCount;
	this->textureRowCount		= textureRowCount;
	this->textureStartColumn	= textureStartColumn;
	this->textureStartRow		= textureStartRow;
	this->textureSize			= texture->getSize();
	this->centeredOrigin		= centeredOrigin;

	this->setColumn(column);
	this->setRow(row);
	this->setLayer(layer);
	this->setSize(static_cast<float>(texture->getSize().x) / static_cast<float>(textureColumnCount), static_cast<float>(texture->getSize().y) / static_cast<float>(textureRowCount));
	this->setDepth(depth);
	this->setOrigin(centeredOrigin ? sf::Vector2f(static_cast<float>(texture->getSize().x) / static_cast<float>(textureColumnCount) / 2.0f, ((static_cast<float>(texture->getSize().y) / static_cast<float>(textureRowCount)) - static_cast<float>(depth)) / 2.f) : sf::Vector2f(0.0f, 0.0f));
	this->setScale(scale);
	this->setTexture(texture);
	//this->setTextureRect(sf::IntRect((static_cast<float>(texture->getSize().x) / static_cast<float>(textureColumnCount)) * static_cast<float>(textureStartColumn), (static_cast<float>(texture->getSize().y) / static_cast<float>(textureRowCount)) * static_cast<float>(textureStartRow), static_cast<float>(texture->getSize().x) / static_cast<float>(textureColumnCount), static_cast<float>(texture->getSize().y) / static_cast<float>(textureRowCount))); // temp srngfr
	this->setTextureIndex(textureStartColumn, textureStartRow);
	this->setTileType(tileType);
	this->setParentScene(parentScene);
	this->setPort(*port);
}

std::size_t Tile::getCount()
{
	return Tile::count;
}

std::size_t Tile::getColumn() const
{
	return this->column;
}

std::size_t Tile::getRow() const
{
	return this->row;
}

std::size_t Tile::getLayer() const
{
	return this->layer;
}

sf::Vector3i Tile::getCoordinates() const
{
	return sf::Vector3i(column, row, layer);
}

float Tile::getDepth() const
{
	return this->depth;
}

const TileType& Tile::getTileType() const
{
	return this->tileType;
}

bool Tile::isConventional() const
{
	return this->tileType == TileType::Conventional;
}

bool Tile::isIsometric() const
{
	return this->tileType == TileType::Isometric;
}

std::size_t Tile::getTextureColumnCount() const
{
	return this->textureColumnCount;
}

std::size_t Tile::getTextureRowCount() const
{
	return this->textureRowCount;
}

std::size_t Tile::getTextureStartColumn() const
{
	return this->textureStartColumn;
}

std::size_t Tile::getTextureStartRow() const
{
	return this->textureStartRow;
}

sf::Vector2u Tile::getTextureStartIndex() const
{
	return sf::Vector2u(this->textureStartColumn, this->textureStartRow);
}

sf::Vector2u Tile::getTextureSize() const
{
	return this->textureSize;
}

std::size_t Tile::getTextureColumn() const
{
	return this->textureIndex.x;
}

std::size_t Tile::getTextureRow() const
{
	return this->textureIndex.y;
}

sf::Vector2u Tile::getTextureIndex() const
{
	return this->textureIndex;
}

std::string Tile::getIndexDetails() const
{
	return std::string(" | column: "	+ std::to_string(getColumn()) + " | row: " + std::to_string(getRow()) + " | layer: " + std::to_string(getLayer()) + " |");
}

bool Tile::isCenteredOrigin() const
{
	return this->centeredOrigin;
}

void Tile::setColumn(std::size_t column)
{
	this->column = column;
}

void Tile::setRow(std::size_t row)
{
	this->row = row;
}

void Tile::setLayer(std::size_t layer)
{
	this->layer = layer;
}

void Tile::setDepth(float depth)
{
	this->depth = depth;
}

void Tile::setTileType(const TileType& tileType)
{
	this->tileType = tileType;
}

void Tile::setTextureStartIndex(const sf::Vector2u& textureStartIndex)
{
	this->textureStartColumn	= textureStartIndex.x;
	this->textureStartRow		= textureStartIndex.y;
}

void Tile::setTextureStartIndex(std::size_t textureStartColumn, std::size_t textureStartRow)
{
	this->textureStartColumn	= textureStartColumn;
	this->textureStartRow		= textureStartRow;
}

void Tile::setTextureIndex(const sf::Vector2u& textureIndex)
{
	if ((textureIndex.x < this->textureColumnCount) && (textureIndex.y < this->textureRowCount))
	{
		setTextureRect(sf::IntRect
		(
			(this->textureSize.x / this->textureColumnCount) * textureIndex.x,
			(this->textureSize.y / this->textureRowCount) * textureIndex.y,
			(this->textureSize.x / this->textureColumnCount),
			(this->textureSize.y / this->textureRowCount)
		));
	};

	this->textureIndex = textureIndex;
}

void Tile::setTextureIndex(std::size_t textureIndexColumn, std::size_t textureIndexRow)
{
	if ((textureIndexColumn < this->textureColumnCount) && (textureIndexRow < this->textureRowCount))
	{
		setTextureRect(sf::IntRect
		(
			(this->textureSize.x / this->textureColumnCount) * textureIndexColumn,
			(this->textureSize.y / this->textureRowCount) * textureIndexRow,
			(this->textureSize.x / this->textureColumnCount),
			(this->textureSize.y / this->textureRowCount)
		));
	};

	this->textureIndex = sf::Vector2u(textureIndexColumn, textureIndexRow);
}
