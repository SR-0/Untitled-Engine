#pragma once

#include "Asset/Tile.h"
#include <vector>
#include <memory>


class Tilemap
	:
	public Asset<Tilemap>
{
public: // type alias

	using Container = std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>;

private: // data

	sf::Vector2f    size                = sf::Vector2f(0.f, 0.f);
	float           depth               = 0.f;
	sf::Vector2f    origin              = sf::Vector2f(0.f, 0.f);
	sf::Vector2f    scale               = sf::Vector2f(0.f, 0.f);
	TileType        tileType            = TileType::Isometric; // TileType::Conventional has little to no functionality right now
	std::size_t     textureColumnCount  = 1;
	std::size_t     textureRowCount     = 1;
	std::size_t     textureStartColumn  = 0;
	std::size_t     textureStartRow     = 0;
	sf::Vector2u    textureSize         = sf::Vector2u(0, 0);
	sf::Vector3i    activeIndex         = sf::Vector3i(0, 0, 0);
	Container       tiles               = Container{};
	bool            centeredOrigin      = false;

public: // ctor(s)/dtor(s)

	Tilemap(const std::string& id = "unidentified", class Scene* parentScene = nullptr, class Port* port = nullptr);

	Tilemap(
		const std::string&  id,
		std::size_t         columns,
		std::size_t         rows,
		std::size_t         layers,
		float               depth,
		const sf::Vector2f&	scale,
		Texture*            texture,
		std::size_t         textureColumnCount,
		std::size_t         textureRowCount,
		std::size_t         textureStartColumn,
		std::size_t         textureStartRow,
		bool                centeredOrigin,
		const TileType&     tileType,
		class Scene*  parentScene         = nullptr,
		class Port*   port                = nullptr);

public: // core

	void setup(
		const std::string&  id,
		std::size_t         columns,
		std::size_t         rows,
		std::size_t         layers,
		float               depth,
		const sf::Vector2f& scale,
		Texture*            texture,
		std::size_t         textureColumnCount,
		std::size_t         textureRowCount,
		std::size_t         textureStartColumn,
		std::size_t         textureStartRow,
		bool                centeredOrigin,
		const TileType&     tileType,
		class Scene*  parentScene         = nullptr,
		class Port*   port                = nullptr);

public: // utility

	void updateTilesRenderEnabled();

public: // getter(s)

	Tile*               getTile(const sf::Vector3i& index);
	Tile*               getTile(std::size_t column, std::size_t row, std::size_t layer);
	Tile*               getActiveTile();
	sf::Vector2f        getTileSize() const;
	float               getTileDepth() const;
	sf::Vector2f        getTileOrigin() const;
	sf::Vector2f        getTileScale() const;
	const TileType&     getTileType() const;
	bool                isConventional() const;
	bool                isIsometric() const;
	sf::Vector3i        getActiveIndex() const;
	std::size_t         getActiveColumn() const;
	std::size_t         getActiveRow() const;
	std::size_t         getActiveLayer() const;
	std::size_t         getColumnCount();
	std::size_t         getRowCount();
	std::size_t         getLayerCount() const;
	std::size_t         getTileCount() const;
	std::size_t         getTextureColumnCount() const;
	std::size_t         getTextureRowCount() const;
	std::size_t         getTextureStartColumn() const;
	std::size_t         getTextureStartRow() const;
	sf::Vector2u        getTextureStartIndex() const;
	sf::Vector2u        getTextureSize() const;
	bool                isCenteredOrigin() const;
	Container&          getTileData();
	void                iterateTiles(const std::function<void(Tile& tile)>& function, bool reversed = false);

public: // setter(s)


	void setPort(Port* port);
	void setActiveIndex(const sf::Vector3i& activeIndex);
	void setActiveIndex(std::size_t column, std::size_t row, std::size_t layer);
	void setActiveColumn(std::size_t column);
	void setActiveRow(std::size_t row);
	void setActiveLayer(std::size_t layer);
	void setTextureStartIndex(const sf::Vector2u& textureStartIndex);
	void setTextureStartIndex(std::size_t textureStartColumn, std::size_t textureStartRow);

};