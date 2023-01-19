#include "Asset/Convex.h"
#include "Core/Scene.h"
#include "Core/Port.h"

Convex::Convex(const std::string& id, std::size_t pointCount, Scene* parentScene, Port* port)
	:
	Shape(id)
{
	this->setPointCount(pointCount);
	this->setParentScene(parentScene);
	this->setPort(*port);
	Shape::type = Shape::Type::Convex;
	sf::Shape::update();
}

Convex::Convex(std::size_t pointCount, Scene* parentScene, Port* port)
	:
	Shape("unidentified")
{
	this->setPointCount(pointCount);
	this->setParentScene(parentScene);
	this->setPort(*port);
	sf::Shape::update();
}

Convex::~Convex()
{
}

std::size_t Convex::getPointCount() const
{
	return this->points.size();
}

sf::Vector2f Convex::getPoint(std::size_t index) const
{
	return this->points[index];
}

void Convex::setPointCount(std::size_t pointCount)
{
	this->points.resize(pointCount);
	sf::Shape::update();
}

void Convex::setPoint(std::size_t index, const sf::Vector2f& point)
{
	this->points[index] = point;
	sf::Shape::update();
}