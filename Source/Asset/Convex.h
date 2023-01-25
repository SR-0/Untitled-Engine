#pragma once

#include "Asset/Shape.h"

class Convex : public Shape
{
protected: // data

	std::vector<sf::Vector2f> points;

public: // ctor(s)/dtor(s)

	Convex(const std::string& id, std::size_t pointCount = 4, class Scene* parentScene = nullptr, class Port* port = nullptr);
	Convex(std::size_t pointCount = 4, class Scene* parentScene = nullptr, class Port* port = nullptr);
	virtual ~Convex() override;

public: // getter(s)

	virtual ShapeType   getShapeType() const override final;
	virtual std::size_t getPointCount() const override final;
	sf::Vector2f        getPoint(std::size_t index) const;

public: // setter(s)

	void setPointCount(std::size_t pointCount);
	void setPoint(std::size_t index, const sf::Vector2f& point);

};