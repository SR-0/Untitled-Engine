#include "Asset/Tilemap.h"
#include "Core/Scene.h"
#include "Core/Port.h"
#include "Core/Global.h"
#include "Utility/Debug.h"
#include <algorithm>

Tilemap::Tilemap(const std::string& id, Scene* parentScene, Port* port)
	:
	Asset<Tilemap>(*this)
{
	this->setup
	(
		id,
		0,
		0,
		0,
		0,
		sf::Vector2f(1.f, 1.f),
		nullptr,
		0,
		0,
		0,
		0,
		false,
		Tile::Type::Conventional,
		parentScene,
		port
	);
}

Tilemap::Tilemap(
	const std::string&	id,
	std::size_t			columns,
	std::size_t			rows,
	std::size_t			layers,
	float				depth,
	const sf::Vector2f&	scale,
	Texture*			texture,
	std::size_t			textureColumnCount,
	std::size_t			textureRowCount,
	std::size_t			textureStartColumn,
	std::size_t			textureStartRow,
	bool				centeredOrigin,
	const Tile::Type&	type,
	Scene*				parentScene,
	Port*				port)
	:
	Asset<Tilemap>(*this)
{
	this->setup
	(
		id,
		columns,
		rows,
		layers,
		depth,
		scale,
		texture,
		textureColumnCount,
		textureRowCount,
		textureStartColumn,
		textureStartRow,
		centeredOrigin,
		type,
		parentScene,
		port
	);
}

void Tilemap::setup(
	const std::string&	id,
	std::size_t			columns,
	std::size_t			rows,
	std::size_t			layers,
	float				depth,
	const sf::Vector2f&	scale,
	Texture*			texture,
	std::size_t			textureColumnCount,
	std::size_t			textureRowCount,
	std::size_t			textureStartColumn,
	std::size_t			textureStartRow,
	bool				centeredOrigin,
	const Tile::Type&	type,
	Scene*				parentScene,
	Port*				port)
{
	if (texture == nullptr)
	{
		debug::print("Tilemap \"", id, "\" setup failed - Texture object evalutated to nullptr (", texture, ")\n");
		return;
	}

	this->size					= (texture ? sf::Vector2f((texture->getSize().x / textureColumnCount), (texture->getSize().y / textureRowCount)) : sf::Vector2f(0, 0));
	this->depth					= depth;
	this->origin				= sf::Vector2f(centeredOrigin ? sf::Vector2f((texture->getSize().x / textureColumnCount) / 2, ((texture->getSize().y / textureRowCount) - depth) / 2) : sf::Vector2f(0, 0));
	this->scale					= scale;
	this->type					= type;
	this->activeIndex			= sf::Vector3i(0, 0, 0);
	this->textureColumnCount	= textureColumnCount;
	this->textureRowCount		= textureRowCount;
	this->textureSize			= (texture ? texture->getSize() : sf::Vector2u(0, 0));
	this->centeredOrigin		= centeredOrigin;

	if (this->tiles.size() > 0)
	{
		this->tiles.clear();
	}

	for (std::size_t layer = 0; layer < layers; layer++)
	{
		this->tiles.push_back(std::vector<std::vector<std::shared_ptr<Tile>>>{});

		for (std::size_t row = 0; row < rows; row++)
		{
			this->tiles[layer].push_back(std::vector<std::shared_ptr<Tile>>{});
	
			for (std::size_t column = 0; column < columns; column++)
			{
				this->tiles[layer][row].emplace_back(std::move(std::make_shared<Tile>
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
					type
				)));

				Tile&		tile	= *this->tiles[layer][row][column].get();
				const float	width	= static_cast<float>(tile.getSize().x);
				const float	height	= static_cast<float>(tile.getSize().y);

				switch (tile.getType())
				{
					case Tile::Type::Conventional: // @TODO untested
					{
						tile.setPosition(sf::Vector2f
						(
							scale.x * (width * column),
							scale.y * ((height - depth) * row) + (depth * layer)
						));
					}
					break;

					case Tile::Type::Isometric: // @TODO bug on y axis
					{
						tile.setPosition
						(
							scale.x * ((width * column) + (row % 2 == 0 ? 0 : (width / 2))),
							scale.y * ((((height - depth) / 2) * row) + (depth * (layers - layer - 1)))

						);
					}
					break;

					default:
					{
						//
					}
					break;
				}
			}
		}
	}

	this->setId(id);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);

	if (layers > (global::getWindow()->getRenderLayerCount() - 1)) // @TODO move to global and tailored debug/unit test class/source
	{
		debug::print
		(
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
			"#\n"
			"#   [ WARNING ]\n"
			"#\n"
			"#   At time of construction, tilemap \"", this->getId(), "\"\n"
			"#   has more tile layers than global window render layers,\n"
			"#   which might lead to unintentional and unseen tiles.\n"
			"#\n"
			"#   If this was done on purpose, ignore this warning and\n"
			"#   do your thang.\n"
			"#\n"
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
		);
	}
}

void Tilemap::updateTilesRenderEnabled() // @TODO complete shit, doesn't work, needs fix, fuck me
{
	/*
		the idea being that we find tiles completely hidden by other tiles
		and disable rendering for those tiles
	*/

	for (std::size_t zIndex = 0; zIndex < this->tiles.size(); zIndex++)
	{
		for (std::size_t yIndex = 0; yIndex < this->tiles[zIndex].size(); yIndex++)
		{
			for (std::size_t xIndex = 0; xIndex < this->tiles[zIndex][yIndex].size(); xIndex++)
			{
				static Tile* above		= nullptr;
				static Tile* frontLeft	= nullptr;
				static Tile* frontRight	= nullptr;

				auto& tile = *this->tiles[zIndex][yIndex][xIndex].get();

				if ((this->getLayerCount() - 1) > zIndex)
					above = this->tiles[zIndex + 1][yIndex][xIndex].get();

				if ((this->getRowCount() - 1) > yIndex)
				{
					if ((tile.getRow() % 2 == 1) && xIndex > 0)
					{
						frontLeft	= this->tiles[zIndex][yIndex + 1][xIndex - 1].get();
						frontRight	= this->tiles[zIndex][yIndex + 1][xIndex].get();
					}
					else if ((tile.getRow() % 2 == 0) && xIndex < (this->getColumnCount() - 1))
					{
						frontLeft	= this->tiles[zIndex][yIndex + 1][xIndex].get();
						frontRight	= this->tiles[zIndex][yIndex + 1][xIndex + 1].get();
					}
				}

				if (above && frontLeft && frontRight)
				{
					if (above->isRenderEnabled() && frontLeft->isRenderEnabled() && frontRight->isRenderEnabled())
					{
						tile.setRenderEnabled(false);
					}
				}

				above		= nullptr;
				frontLeft	= nullptr;
				frontRight	= nullptr;
			}
		}
	}
}

Port* Tilemap::getPort() const
{
	return this->port;
}

Tile* Tilemap::getTile(const sf::Vector3i& index)
{
	return this->tiles[index.z][index.y][index.x].get();
}

Tile* Tilemap::getTile(std::size_t column, std::size_t row, std::size_t layer)
{
	return this->tiles[layer][row][column].get();
}

Tile* Tilemap::getActiveTile()
{
	return this->getTile(getActiveIndex());
}

sf::Vector2f Tilemap::getTileSize() const
{
	return this->size;
}

float Tilemap::getTileDepth() const
{
	return this->depth;
}

sf::Vector2f Tilemap::getTileOrigin() const
{
	return this->origin;
}

sf::Vector2f Tilemap::getTileScale() const
{
	return this->scale;
}

const Tile::Type& Tilemap::getType() const
{
	return this->type;
}

bool Tilemap::isConventional() const
{
	return this->type == Tile::Type::Conventional;;
}

bool Tilemap::isIsometric() const
{
	return this->type == Tile::Type::Isometric;
}

sf::Vector3i Tilemap::getActiveIndex() const
{
	return this->activeIndex;
}

std::size_t Tilemap::getActiveColumn() const
{
	return this->activeIndex.x;
}

std::size_t Tilemap::getActiveRow() const
{
	return this->activeIndex.y;
}

std::size_t Tilemap::getActiveLayer() const
{
	return this->activeIndex.z;
}

std::size_t Tilemap::getColumnCount()
{
	if (this->tiles.size() > 0)
	{
		if (this->tiles.at(0).size() > 0)
		{
			return this->tiles.at(0).at(0).size();
		}
	}

	return 0;
}

std::size_t Tilemap::getRowCount()
{
	if (this->tiles.size() > 0)
	{
		return this->tiles.at(0).size();
	}

	return 0;
}

std::size_t Tilemap::getLayerCount() const
{
	return this->tiles.size();
}

std::size_t Tilemap::getTileCount() const
{
	std::size_t counter = 0;

	for (auto& layer : this->tiles)
		for (auto& row : layer)
			for (auto& column : row)
				counter++;

	return counter;
}

std::size_t Tilemap::getTextureColumnCount() const
{
	return this->textureColumnCount;
}

std::size_t Tilemap::getTextureRowCount() const
{
	return this->textureRowCount;
}

std::size_t Tilemap::getTextureStartColumn() const
{
	return this->textureStartColumn;
}

std::size_t Tilemap::getTextureStartRow() const
{
	return this->textureStartRow;
}

sf::Vector2u Tilemap::getTextureStartIndex() const
{
	return sf::Vector2u(this->textureStartColumn, this->textureStartRow);
}

sf::Vector2u Tilemap::getTextureSize() const
{
	return this->textureSize;
}

bool Tilemap::isCenteredOrigin() const
{
	return this->centeredOrigin;
}

Tilemap::Container& Tilemap::getTileData()
{
	return this->tiles;
}

void Tilemap::iterateTiles(const std::function<void(Tile& tile)>& function, bool reversed)
{
	if (reversed)
		for (auto zIter = this->tiles.rbegin(); zIter != this->tiles.rend(); zIter++)
			for (auto yIter = zIter->rbegin(); yIter != zIter->rend(); yIter++)
				for (auto xIter = yIter->rbegin(); xIter != yIter->rend(); xIter++)
					return function(*xIter->get());

	for (auto zIter = this->tiles.begin(); zIter != this->tiles.end(); zIter++)
		for (auto yIter = zIter->begin(); yIter != zIter->end(); yIter++)
			for (auto xIter = yIter->begin(); xIter != yIter->end(); xIter++)
				function(*xIter->get());
}

void Tilemap::setPort(Port& port)
{
	this->port = &port;
	this->iterateTiles([&](Tile& tile){ tile.setPort(port); });
}

void Tilemap::setActiveIndex(const sf::Vector3i& activeIndex)
{
	this->activeIndex = activeIndex;
}

void Tilemap::setActiveIndex(std::size_t column, std::size_t row, std::size_t layer)
{
	this->activeIndex = sf::Vector3i(column, row, layer);
}

void Tilemap::setActiveColumn(std::size_t column)
{
	this->activeIndex = sf::Vector3i(column, this->activeIndex.y, this->activeIndex.z);
}

void Tilemap::setActiveRow(std::size_t row)
{
	this->activeIndex = sf::Vector3i(this->activeIndex.x, row, this->activeIndex.z);
}

void Tilemap::setActiveLayer(std::size_t layer)
{
	this->activeIndex = sf::Vector3i(this->activeIndex.x, this->activeIndex.y, layer);
}

void Tilemap::setTextureStartIndex(const sf::Vector2u& textureStartIndex)
{
	this->textureStartColumn = textureStartIndex.x;
	this->textureStartRow = textureStartIndex.y;

	this->iterateTiles([&](Tile& tile)
	{
		tile.setTextureStartIndex(textureStartIndex);
	});
}

void Tilemap::setTextureStartIndex(std::size_t textureStartColumn, std::size_t textureStartRow)
{
	this->textureStartColumn	= textureStartColumn;
	this->textureStartRow		= textureStartRow;

	this->iterateTiles([&](Tile& tile)
	{
		tile.setTextureStartIndex(textureStartColumn, textureStartRow);
	});
}