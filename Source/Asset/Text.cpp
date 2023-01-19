#include "Asset/Text.h"
#include "Core/Scene.h"
#include "Core/Global.h"
#include "Core/Port.h"

Text::Text(const std::string& id, Scene* parentScene, Port* port)
	:
	sf::Text(),
	Asset<Text>(*this)
{
	this->setId(id);
	this->setString(id);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setFillColor(sf::Color::Black);
}

Text::Text(const Font* font, Scene* parentScene, Port* port)
	:
	sf::Text(),
	Asset<Text>(*this)
{
	this->setFont(*font);
	this->setParentScene(parentScene);
	this->setFillColor(sf::Color::Black);
}

Text::Text(const std::string& id, const Font* font, Scene* parentScene, Port* port)
	:
	sf::Text(),
	Asset<Text>(*this)
{
	this->setId(id);
	this->setString(id);
	this->setFont(*font);
	this->setParentScene(parentScene);
	this->setPort(*port);
	this->setFillColor(sf::Color::Black);
}

Text::~Text()
{
}

const std::size_t& Text::getRenderLayer() const
{
	return this->renderLayer;
}

bool Text::isRenderEnabled() const
{
	return this->renderEnabled && (static_cast<bool>(this->getParentScene()) ? this->getParentScene()->isRenderEnabled() : true);
}

Port* Text::getPort() const
{
	return this->port;
}

sf::Uint8 Text::getOpacity() const
{
	return this->getFillColor().a;
}

bool Text::isTransparent() const
{
	return this->getFillColor().a == sf::Uint8(0);
}

bool Text::isOpaque() const
{
	return this->getFillColor().a == sf::Uint8(255);
}

void Text::setRenderLayer(std::size_t renderLayer)
{
	this->renderLayer = renderLayer;
}

void Text::setRenderLayerFront()
{
	this->renderLayer = global::getWindow()->getRenderLayerCount() - 1;
}

void Text::setRenderLayerBack()
{
	this->renderLayer = 0;
}

void Text::setRenderEnabled(bool renderEnabled)
{
	this->renderEnabled = renderEnabled;
}

void Text::setPort(Port& port)
{
	this->port = &port;
}

void Text::setOpacity(float opacity)
{
	if (opacity < 0)
	{
		this->setFillColor(sf::Color
		(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			0
		));
	}
	else if (opacity > 255)
	{
		this->setFillColor(sf::Color
		(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			255
		));
	}
	else
	{
		this->setFillColor(sf::Color
		(
			this->getFillColor().r,
			this->getFillColor().g,
			this->getFillColor().b,
			opacity
		));
	}
}

void Text::setOpaque()
{
	this->setFillColor(sf::Color
	(
		this->getFillColor().r,
		this->getFillColor().g,
		this->getFillColor().b,
		255
	));
}

void Text::setTransparent()
{
	this->setFillColor(sf::Color
	(
		this->getFillColor().r,
		this->getFillColor().g,
		this->getFillColor().b,
		0
	));
}

void Text::fadeIn(float alphaIncrement, const sf::Uint8& max)
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

void Text::fadeOut(float alphaDecrement, const sf::Uint8& min)
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