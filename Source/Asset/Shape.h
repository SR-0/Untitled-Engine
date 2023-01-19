#pragma once

#include "Asset/Texture.h"
#include "Core/Animation.h"

class Shape : public sf::Shape, public Asset<Shape>
{
public:

	enum class Type
	{
		Error,
		Rectangle,
		Circle,
		Convex
	};

private:

	Shape::Type type			= Shape::Type::Error;
	Animation	animation		= Animation{};
	std::size_t renderLayer		= 0;
	bool		renderEnabled	= true;
	class Port* port			= nullptr;

public:

	Shape(const std::string& id = "unidentified", class Scene* parent = nullptr, class Port* port = nullptr);
	Shape(const std::string& id, const Texture* texture, class Scene* parent = nullptr, class Port* port = nullptr);

public:

	virtual bool intersects(const sf::FloatRect& floatRect) const = 0;
	virtual bool intersects(const sf::Vector2f& point) const = 0;
	virtual bool intersects(const sf::Vector2i& point) const = 0;

public:

	const Shape::Type&	getType() const;
	const std::size_t&	getRenderLayer() const;
	bool				isRenderEnabled() const;
	class Port*			getPort() const;
	bool				isAnimated() const;
	bool				isHoveredOver() const;
	bool				isLeftClicked() const;
	bool				isMiddleClicked() const;
	bool				isRightClicked() const;
	sf::Uint8			getOpacity() const;
	bool				isTransparent() const;
	bool				isOpaque() const;

public:

	void setRenderLayer(std::size_t renderLayer);
	void setRenderLayerFront();
	void setRenderLayerBack();
	void setRenderEnabled(bool renderEnabled);
	void setPort(class Port& port);
	void setAnimated(bool animated);
	void setAnimation(sf::Vector2u imageCount, float switchTime, std::size_t activeRow = 0);
	void setAnimation(const Texture* texture, sf::Vector2u imageCount, float switchTime, std::size_t activeRow = 0);
	void setOpacity(float opacity);
	void setOpaque();
	void setTransparent();

public:

	void fadeIn(float alphaIncrement, const sf::Uint8& max = 255);
	void fadeOut(float alphaDecrement, const sf::Uint8& min = 0);

public:

	void updateAnimation(float deltaTime);

private:

	friend class Rectangle;
	friend class Circle;
	friend class Convex;

};

