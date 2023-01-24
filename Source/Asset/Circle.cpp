#include "Asset/Circle.h"
#include "Core/Scene.h"
#include "Core/Port.h"

Circle::Circle(const std::string& id, float radius, std::size_t pointCount, Scene* parentScene, Port* port)
	:
	Shape(id),
	radius(radius),
	pointCount(pointCount)
{
	this->setRadius(radius);
	this->setPointCount(pointCount);
	this->setParentScene(parentScene);
	this->setPort(*port);
	sf::Shape::update();
}

Circle::Circle(float radius, std::size_t pointCount, Scene* parentScene, Port* port)
	:
	Shape("unidentified"),
	radius(radius),
	pointCount(pointCount)
{
	this->setRadius(radius);
	this->setPointCount(pointCount);
	this->setParentScene(parentScene);
	this->setPort(*port);
	sf::Shape::update();
}

Circle::~Circle()
{
}

ShapeType Circle::getShapeType() const
{
	return ShapeType::Circle;
}

float Circle::getRadius() const
{
	return this->radius;
}

std::size_t Circle::getPointCount() const
{
	return pointCount;
}

sf::Vector2f Circle::getPoint(std::size_t index) const
{
	static constexpr float pi = 3.141592654f;

	float angle	= index * 2 * pi / pointCount - pi / 2;
	float x		= std::cos(angle) * radius;
	float y		= std::sin(angle) * radius;

	return sf::Vector2f(radius + x, radius + y);
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
	sf::Shape::update(); // not needed?
}

void Circle::setPointCount(std::size_t pointCount)
{
	this->pointCount = pointCount;
	sf::Shape::update(); // not needed?
}