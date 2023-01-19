#include "Core/Port.h"
#include "Utility/Debug.h"
#include "Core/Global.h"
#include "Asset/Rectangle.h"




#pragma region CTOR(S)/DTOR(S)

Port::Port()
{
	this->background = global::getAssetManager()->createShape<Rectangle>(id + "Background");
	this->background->setSize(global::getWindow()->getSize().x, global::getWindow()->getSize().y);
	this->background->setRenderLayer(0);
	this->border = global::getAssetManager()->createShape<Rectangle>(id + "Border");
	this->border->setSize(this->background->getSize());
	this->border->setPosition(this->background->getPosition());
	this->border->setRenderLayer(global::getWindow()->getRenderLayerCount() - 1);
	this->border->setFillColor(sf::Color::Transparent);
	this->border->setOutlineColor(sf::Color::White);
	this->border->setOutlineThickness(-2);
}

Port::Port(const std::string& id, const sf::FloatRect& viewport, std::size_t renderLayerCount, bool active)
{
	this->setId(id);
	this->view.setViewport(viewport);
	this->view.setSize(global::getWindow()->getSize().x * viewport.width, global::getWindow()->getSize().y * viewport.height);
	this->view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	this->renderLayerCount = renderLayerCount;
	this->setActive(active);
	this->background = global::getAssetManager()->createShape<Rectangle>(id + "Background");
	this->background->setSize(global::getWindow()->getSize().x * viewport.width, global::getWindow()->getSize().y * viewport.height);
	this->background->setPosition(global::getWindow()->getSize().x * viewport.left, global::getWindow()->getSize().y * viewport.top);
	this->background->setRenderLayer(0);
	this->border = global::getAssetManager()->createShape<Rectangle>(id + "Border");
	this->border->setSize(this->background->getSize());
	this->border->setPosition(this->background->getPosition());
	this->border->setRenderLayer(global::getWindow()->getRenderLayerCount() - 1);
	this->border->setFillColor(sf::Color::Transparent);
	this->border->setOutlineColor(sf::Color::White);
	this->border->setOutlineThickness(-2);
}

Port::Port(const std::string& id, float x, float y, float width, float height, std::size_t renderLayerCount, bool active)
{
	this->setId(id);
	this->view.setViewport(sf::FloatRect(x, y, width, height));
	this->view.setSize(global::getWindow()->getSize().x * width, global::getWindow()->getSize().y * height);
	this->view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	this->renderLayerCount = renderLayerCount;
	this->setActive(active);
	this->background = global::getAssetManager()->createShape<Rectangle>(id + "Background");
	this->background->setSize(global::getWindow()->getSize().x * width, global::getWindow()->getSize().y * height);
	this->background->setPosition(global::getWindow()->getSize().x * x, global::getWindow()->getSize().y * y);
	this->background->setRenderLayer(0);
	this->border = global::getAssetManager()->createShape<Rectangle>(id + "Border");
	this->border->setSize(this->background->getSize());
	this->border->setPosition(this->background->getPosition());
	this->border->setRenderLayer(global::getWindow()->getRenderLayerCount() - 1);
	this->border->setFillColor(sf::Color::Transparent);
	this->border->setOutlineColor(sf::Color::White);
	this->border->setOutlineThickness(-2);
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void Port::resize() // @TODO
{
	//this->background->setSize(global::getWindow()->getSize().x * this->view.getViewport().width, global::getWindow()->getSize().y * this->view.getViewport().height);
	//this->background->setPosition(global::getWindow()->getSize().x * this->view.getViewport().left, global::getWindow()->getSize().y * this->view.getViewport().top);
	//
	//this->border->setSize(this->background->getSize());
	//this->border->setPosition(this->background->getPosition());

	//this->view.setSize(global::getWindow()->getSize().x, global::getWindow()->getSize().y);
	//this->background->setSize(global::getWindow()->getSize().x * this->view.getViewport().width, global::getWindow()->getSize().y * this->view.getViewport().height);
	//this->background->setPosition(global::getWindow()->getSize().x * this->view.getViewport().left, global::getWindow()->getSize().y * this->view.getViewport().top);
	//this->border->setSize(this->background->getSize());
	//this->border->setPosition(this->background->getPosition());
}

#pragma endregion CORE





#pragma region GETTER(S)

const std::string& Port::getUuid() const
{
	return this->uuid;
}

const std::string& Port::getId() const
{
	return this->id;
}

bool Port::isActive() const
{
	return this->active;
}

std::size_t Port::getRenderLayerCount() const
{
	return this->renderLayerCount;
}

sf::Vector2f Port::getSize() const
{
	return this->view.getSize();
}

sf::Vector2f Port::getCenter() const
{
	return this->view.getCenter();
}

sf::View Port::getView() const
{
	return this->view;
}

sf::FloatRect Port::getViewport() const
{
	return this->view.getViewport();
}

sf::Vector2f Port::getZoom() const
{
	return sf::Vector2f
	(
		this->view.getSize().x / this->view.getSize().x,
		this->view.getSize().y / this->view.getSize().y
	);
}

sf::Vector2f Port::getScroll() const
{
	return sf::Vector2f
	(
		this->view.getCenter().x - this->view.getSize().x / 2,
		this->view.getCenter().y - this->view.getSize().y / 2
	);
}

float Port::getRotation() const
{
	return this->view.getRotation();
}

Rectangle* Port::getBackground() const
{
	return this->background;
}

Rectangle* Port::getBorder() const
{
	return this->border;
}

#pragma endregion GETTER(S)





#pragma region SETTER(S)


void Port::setId(const std::string& id)
{
	this->id = id;
}

void Port::setActive(bool active)
{
	if (this->background)
	{
		this->background->setRenderEnabled(active);
	}

	this->active = active;
}

void Port::setRenderLayerCount(std::size_t renderLayerCount)
{
	this->renderLayerCount = renderLayerCount;
}

void Port::setView(const sf::View& view)
{
	this->view = view;
}

void Port::setView(const sf::FloatRect& rectangle)
{
	this->view = sf::View(rectangle);
}

void Port::setView(const sf::Vector2f& center, const sf::Vector2f& size)
{
	this->view = sf::View(center, size);
}

void Port::setView(float x, float y, float width, float height)
{
	this->view = sf::View(sf::Vector2f(x, y), sf::Vector2f(width, height));
}

void Port::setViewport(const sf::FloatRect& viewport)
{
	this->view.setViewport(viewport);
}

void Port::setViewport(float x, float y, float width, float height)
{
	this->view.setViewport(sf::FloatRect(x, y, width, height));
}

void Port::setZoom(float scalar)
{
	this->setView
	(
		this->view.getCenter().x,
		this->view.getCenter().y,
		this->view.getSize().x / scalar,
		this->view.getSize().y / scalar
	);
}

void Port::setZoom(float x, float y)
{
	this->setView
	(
		this->view.getCenter().x,
		this->view.getCenter().y,
		this->view.getSize().x / x,
		this->view.getSize().y / y
	);
}

void Port::setZoom(const sf::Vector2f& zoom)
{
	this->setView
	(
		this->view.getCenter().x,
		this->view.getCenter().y,
		this->view.getSize().x / zoom.x,
		this->view.getSize().y / zoom.y
	);
}

void Port::setScroll(float horizontal, float vertical)
{
	this->view = sf::View
	(
		sf::Vector2f((this->view.getSize().x / 2) + horizontal, (this->view.getSize().y / 2) + vertical),
		sf::Vector2f(this->view.getSize())
	);
}

void Port::setScroll(const sf::Vector2f& scroll)
{
	this->setScroll(scroll.x, scroll.y);
}

void Port::setRotation(float rotation)
{
	this->view.setRotation(rotation);
}

#pragma endregion SETTER(S)