#pragma once

#include "Asset/Shape.h"

class Rectangle : public Shape
{
private: // data

	sf::Vector2f size;

public: // ctor(s)/dtor(s)

	Rectangle(const sf::FloatRect& floatRect, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const sf::FloatRect& floatRect, const sf::Color& outlineColor, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const sf::FloatRect& floatRect, const sf::Color& outlineColor, float outlineThickness, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const sf::FloatRect& floatRect, const sf::Vector2f& scale, const sf::Color& outlineColor, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const sf::FloatRect& floatRect, const sf::Vector2f& scale, const sf::Color& outlineColor, float outlineThickness, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const std::string& id, const sf::Vector2f& size = { 100.f, 100.f }, const sf::Vector2f& position = { 0.f, 0.f }, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const std::string& id, const Texture* texture, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const std::string& id, const Texture* texture, const sf::Vector2f& position, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const std::string& id, const Texture* texture, const sf::Vector2u& imageCount, float switchTime, std::size_t activeRow, bool animated, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const std::string& id, const Texture* texture, const sf::Vector2f& position, const sf::Vector2u& imageCount, float switchTime, std::size_t activeRow, bool animated, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(const sf::Vector2f& size = { 100.f, 100.f }, const sf::Vector2f& position = { 0.f, 0.f }, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(Texture* texture, class Scene* parent = nullptr, class Port* port = nullptr);
	Rectangle(Texture* texture, const sf::Vector2f& size, class Scene* parent = nullptr, class Port* port = nullptr);

public: // utility

	void move(const sf::Vector2f& distance);
	virtual bool intersects(const sf::FloatRect& floatRect) const override;
	virtual bool intersects(const sf::Vector2f& point) const override;
	virtual bool intersects(const sf::Vector2i& point) const override;

public: // getter(s)

	virtual ShapeType       getShapeType() const override final;
	float                   getWidth() const;
	float                   getHeight() const;
	const sf::Vector2f&     getSize() const;
	virtual std::size_t     getPointCount() const override final;
	virtual sf::Vector2f    getPoint(std::size_t index) const override final;

public: // setter(s)

	void setSize(const sf::Vector2f& size);
	void setSize(float x, float y);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);

};