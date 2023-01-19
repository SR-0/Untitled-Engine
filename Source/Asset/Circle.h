#pragma once

#include "Asset/Shape.h"

class Circle : public Shape
{
private:

	float	radius;
	size_t	pointCount;

public:

	Circle(const std::string& id, float radius = 10.f, std::size_t pointCount = 30U, class Scene* parentScene = nullptr, class Port* port = nullptr);
	Circle(float radius = 10.f, std::size_t pointCount = 30U, class Scene* parentScene = nullptr, class Port* port = nullptr);
	virtual ~Circle() override;

public:

	float					getRadius() const;
	virtual std::size_t		getPointCount() const override final;
	virtual sf::Vector2f	getPoint(std::size_t index) const override final;

public:

	void setRadius(float radius);
	void setPointCount(std::size_t pointCount);

};

