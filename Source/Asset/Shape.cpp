#include "Asset/Shape.h"
#include "Asset/Rectangle.h"
#include "Asset/Tile.h"
#include "Core/Scene.h"
#include <SFML/Window/Mouse.hpp>
#include "Core/Port.h"
#include "Core/Global.h"

Shape::Shape(const std::string& id, Scene* parent, Port* port)
	:
	sf::Shape(),
	Asset<Shape>(*this)
{
	this->setId(id);
	this->setParentScene(parent);
	this->setPort(*port);
	if (parent)
		this->setPosition(parent->getPosition());
}

Shape::Shape(const std::string& id, const Texture* texture, Scene* parent, Port* port)
	:
	sf::Shape(),
	Asset<Shape>(*this)
{
	this->setId(id);
	this->setTexture(texture);
	this->setParentScene(parent);
	this->setPort(*port);
	if (parent)
		this->setPosition(parent->getPosition());
}

const std::size_t& Shape::getRenderLayer() const
{
	return this->renderLayer;
}

bool Shape::isRenderEnabled() const
{
	return this->renderEnabled && (static_cast<bool>(this->getParentScene()) ? this->getParentScene()->isRenderEnabled() : true);
}

Port* Shape::getPort() const
{
	return this->port;
}

bool Shape::isAnimated() const
{
	return this->animation.isActive();
}

bool Shape::isHoveredOver() const
{
	switch (this->getShapeType())
	{
		case ShapeType::Rectangle: // @TODO include scale calculations
		{
			sf::Vector2i position = sf::Mouse::getPosition(*global::getWindow()->getInstance());

			if (this->port != nullptr)
			{
				position.x -= (global::getWindow()->getSize().x * port->getView().getViewport().left);
				position.y -= (global::getWindow()->getSize().y * port->getView().getViewport().top);
			}

			return this->as<Rectangle>()->intersects(position);
		}
		break;

		case ShapeType::Circle: // @TODO
		{
			return false;
		}
		break;

		case ShapeType::Convex: // @TODO
		{
			return false;
		}
		break;
	}
}

bool Shape::isLeftClicked() const
{
	return this->isHoveredOver() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Shape::isMiddleClicked() const
{
	return this->isHoveredOver() && sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}

bool Shape::isRightClicked() const
{
	return this->isHoveredOver() && sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

sf::Uint8 Shape::getOpacity() const
{
	return this->getFillColor().a;
}

bool Shape::isTransparent() const
{
	return this->getFillColor().a == sf::Uint8(0);
}

bool Shape::isOpaque() const
{
	return this->getFillColor().a == sf::Uint8(255);
}

void Shape::setRenderLayer(std::size_t renderLayer)
{
	this->renderLayer = renderLayer;
}

void Shape::setRenderLayerFront()
{
	this->renderLayer = global::getWindow()->getRenderLayerCount() - 1;
}

void Shape::setRenderLayerBack()
{
	this->renderLayer = 0;
}

void Shape::setRenderEnabled(bool renderEnabled)
{
	this->renderEnabled = renderEnabled;
}

void Shape::setPort(Port& port)
{	
	this->port = &port;
}

void Shape::setAnimated(bool animated)
{
	this->animation.setActive(animated);
}

void Shape::setAnimation(sf::Vector2u imageCount, float switchTime, std::size_t activeRow)
{
	this->animation.set
	(
		this,
		imageCount,
		switchTime,
		activeRow
	);
}

void Shape::setAnimation(const Texture* texture, sf::Vector2u imageCount, float switchTime, std::size_t activeRow)
{
	this->setTexture(texture);

	this->animation.set
	(
		this,
		imageCount,
		switchTime,
		activeRow
	);
}

void Shape::setOpacity(float opacity)
{
	if (opacity < 0)
	{
		this->setFillColor(sf::Color(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			0));
	}
	else if (opacity > 255)
	{
		this->setFillColor(sf::Color(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			255));
	}
	else
	{
		this->setFillColor(sf::Color(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			opacity));
	}
}

void Shape::setOpaque()
{
	this->setFillColor(sf::Color
	(
		this->getFillColor().r,
		this->getFillColor().g,
		this->getFillColor().b,
		255
	));
}

void Shape::setTransparent()
{
	this->setFillColor(sf::Color
	(
		this->getFillColor().r,
		this->getFillColor().g,
		this->getFillColor().b,
		0
	));
}

void Shape::fadeIn(float alphaIncrement, const sf::Uint8& max)
{
	if (this->getOpacity() + alphaIncrement < max)
	{
		this->setOpacity(this->getOpacity() + alphaIncrement);
	}
	else
	{
		this->setOpacity(max);
	}
}

void Shape::fadeOut(float alphaDecrement, const sf::Uint8& min)
{
	if (this->getOpacity() - alphaDecrement > min)
	{
		this->setOpacity(this->getOpacity() - alphaDecrement);
	}
	else
	{
		this->setOpacity(min);
	}
}

void Shape::updateAnimation(float deltaTime)
{
	this->animation.update(deltaTime);
}
