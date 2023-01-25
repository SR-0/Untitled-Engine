#include "Asset/Rectangle.h"
#include "Core/Scene.h"
#include "Core/Port.h"

Rectangle::Rectangle(const sf::FloatRect& floatRect, Scene* parentScene, Port* port)
	:
	Shape("unidentifed")
{
	this->setPosition(floatRect.left, floatRect.top);
	this->setSize(floatRect.width, floatRect.height);
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(sf::Color::Red);
	this->setOutlineThickness(-1.f);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const sf::FloatRect& floatRect, const sf::Color& outlineColor, Scene* parentScene, Port* port)
	:
	Shape("unidentifed")
{
	this->setPosition(floatRect.left, floatRect.top);
	this->setSize(floatRect.width, floatRect.height);
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(outlineColor);
	this->setOutlineThickness(-1.f);
	this->setParentScene(parentScene);
	this->setPort(*port);
	sf::Shape::update();
}

Rectangle::Rectangle(const sf::FloatRect& floatRect, const sf::Color& outlineColor, float outlineThickness, Scene* parentScene, Port* port)
	:
	Shape("unidentifed")
{
	this->setPosition(floatRect.left, floatRect.top);
	this->setSize(floatRect.width, floatRect.height);
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(outlineColor);
	this->setOutlineThickness(outlineThickness);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const sf::FloatRect& floatRect, const sf::Vector2f& scale, const sf::Color& outlineColor, Scene* parentScene, Port* port)
	:
	Shape("unidentifed")
{
	this->setPosition(floatRect.left, floatRect.top);
	this->setSize(floatRect.width, floatRect.height);
	this->setScale(scale);
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(outlineColor);
	this->setOutlineThickness(-1.f);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const sf::FloatRect& floatRect, const sf::Vector2f& scale, const sf::Color& outlineColor, float outlineThickness, Scene* parentScene, Port* port)
	:
	Shape("unidentifed")
{
	this->setPosition(floatRect.left, floatRect.top);
	this->setSize(floatRect.width, floatRect.height);
	this->setScale(scale);
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(outlineColor);
	this->setOutlineThickness(outlineThickness);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const std::string& id, const sf::Vector2f& size, const sf::Vector2f& position, Scene* parentScene, Port* port)
	:
	Shape(id)
{
	this->setSize(size);
	this->setPosition(position);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const std::string& id, const Texture* texture, Scene* parentScene, Port* port)
	:
	Shape(id, texture)
{
	this->setSize(sf::Vector2f(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle::Rectangle(const std::string& id, const Texture* texture, const sf::Vector2f& position, Scene* parentScene, Port* port)
	:
	Shape(id, texture)
{
	this->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	this->setPosition(position);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(const std::string& id, const Texture* texture, const sf::Vector2u& imageCount, float switchTime, std::size_t activeRow, bool animated, Scene* parentScene, Port* port)
	:
	Shape(id, texture)
{
	this->setSize(sf::Vector2f(static_cast<float>(texture->getSize().x / imageCount.x), static_cast<float>(texture->getSize().y / imageCount.y)));
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	this->setAnimated(animated);
	this->setAnimation(texture, imageCount, switchTime, activeRow);
	sf::Shape::update();
}

Rectangle::Rectangle(const std::string& id, const Texture* texture, const sf::Vector2f& position, const sf::Vector2u& imageCount, float switchTime, std::size_t activeRow, bool animated, Scene* parentScene, Port* port)
	:
	Shape(id, texture)
{
	this->setSize(sf::Vector2f(static_cast<float>(texture->getSize().x / imageCount.x), static_cast<float>(texture->getSize().y / imageCount.y)));
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setPosition(position);
	this->setActive(true);
	this->setAnimated(animated);
	this->setAnimation(texture, imageCount, switchTime, activeRow);
	sf::Shape::update();
}

Rectangle::Rectangle(const sf::Vector2f& size, const sf::Vector2f& position, Scene* parentScene, Port* port)
	:
	Shape("unidentified"),
	size(size)
{
	this->setSize(size);
	this->setPosition(position);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle::Rectangle::Rectangle(Texture* texture, Scene* parentScene, Port* port)
	:
	Shape("unidentified", texture)
{
	this->setSize(sf::Vector2f(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

Rectangle::Rectangle(Texture* texture, const sf::Vector2f& size, Scene* parentScene, Port* port)
	:
	Shape("unidentified", texture)
{
	this->setSize(size);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setActive(true);
	sf::Shape::update();
}

void Rectangle::move(const sf::Vector2f& distance)
{
	this->setPosition(this->getPosition() + distance);
}

bool Rectangle::intersects(const sf::FloatRect& floatRect) const
{
	return this->getLocalBounds().intersects(floatRect);
}

bool Rectangle::intersects(const sf::Vector2f& point) const
{
	return bool
	(
		point.x >= this->getPosition().x - this->getOrigin().x                      &&
		point.y >= this->getPosition().y - this->getOrigin().y                      &&
		point.x <= this->getPosition().x - this->getOrigin().x + this->getSize().x  &&
		point.y <= this->getPosition().y - this->getOrigin().y + this->getSize().y
	);
}

bool Rectangle::intersects(const sf::Vector2i& point) const
{
	return bool
	(
		point.x >= this->getPosition().x - this->getOrigin().x                      &&
		point.y >= this->getPosition().y - this->getOrigin().y                      &&
		point.x <= this->getPosition().x - this->getOrigin().x + this->getSize().x  &&
		point.y <= this->getPosition().y - this->getOrigin().y + this->getSize().y
	);
}

ShapeType Rectangle::getShapeType() const
{
	return ShapeType::Rectangle;
}

float Rectangle::getWidth() const
{
	return this->size.x;
}

float Rectangle::getHeight() const
{
	return this->size.y;
}

const sf::Vector2f& Rectangle::getSize() const
{
	return size;
}

std::size_t Rectangle::getPointCount() const
{
	return 4;
}

sf::Vector2f Rectangle::getPoint(std::size_t index) const
{
	switch (index)
	{
		case 0: return sf::Vector2f(0, 0);
		case 1: return sf::Vector2f(size.x, 0);
		case 2: return sf::Vector2f(size.x, size.y);
		case 3: return sf::Vector2f(0, size.y);
		default: throw;
	}
}

void Rectangle::setSize(const sf::Vector2f& size)
{
	this->size = size;
	sf::Shape::update();
}

void Rectangle::setSize(float x, float y)
{
	setSize(sf::Vector2f(x, y));
}

void Rectangle::setPosition(float x, float y)
{
	sf::Shape::setPosition(sf::Vector2f(x, y));
}

void Rectangle::setPosition(const sf::Vector2f& position)
{
	this->setPosition(position.x, position.y);
}