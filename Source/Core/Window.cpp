#include "Core/Window.h"
#include "Core/Global.h"
#include "Utility/Debug.h"
#include "Utility/Random.h"
#include <SFML/Graphics/Sprite.hpp>





#pragma region CTOR(S)/DTOR(S)

Window::Window(bool autoSetup)
{
	if (autoSetup)
	{
		const auto size = sf::Vector2u
		(
			sf::VideoMode::getDesktopMode().width,
			sf::VideoMode::getDesktopMode().height
		);

		this->set
		(
			size,
			sf::String("The Untitled One"),
			sf::Style::Fullscreen,
			sf::ContextSettings()
		);

		return;
	}

	const auto size = sf::Vector2u // @THINK possibly go smaller, but not likely
	(
		Window::minimumWidth,
		Window::minimumHeight
	);

	this->set
	(
		size,
		sf::String("The Untitled One"),
		sf::Style::None,
		sf::ContextSettings()
	);
}

Window::Window(const sf::Vector2u& size, const sf::String& title, const sf::Uint32& style, const sf::ContextSettings& settings)
{
	this->set
	(
		size,
		title,
		style,
		settings
	);
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void Window::close()
{
	this->instance->close();
}

bool Window::pollEvent(sf::Event& event)
{
	return this->instance->pollEvent(event);
}

void Window::clear()
{
	this->instance->clear(this->clearColor);
}

void Window::clear(const sf::Color& clearColor)
{
	this->instance->clear(clearColor);
}

void Window::clear(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->instance->clear(sf::Color(r, g, b, a));
}

void Window::draw(const sf::Drawable& drawable)
{
	this->instance->draw(drawable);
}

void Window::draw() // so much more work to do
{
	if (this->isRenderingPaused())
		return;

	auto	originalView				= this->instance->getView();
	auto&	am							= *global::getAssetManager();
	auto&	portEditor					= *this->getPort("portEditor");
	auto&	rectangleEditorTileCuller	= *am.getShape("rectangleEditorTileCuller")->as<Rectangle>();

	for (std::size_t renderLayer = 0; renderLayer < this->getRenderLayerCount(); renderLayer++)
	{
		for (auto& tilemap : am.getTilemapData())
		{
			const int zIndex = renderLayer;

			if (tilemap->isActive() && (renderLayer < tilemap->getLayerCount()))
			{
				int xStart	= (((rectangleEditorTileCuller.getPosition().x - rectangleEditorTileCuller.getOrigin().x) / (tilemap->getTileSize().x * tilemap->getTileScale().x)) - 1);
				int xEnd	= (xStart + (rectangleEditorTileCuller.getSize().x / (tilemap->getTileSize().x * tilemap->getTileScale().x)) + 3);
				int	yStart	= ((rectangleEditorTileCuller.getPosition().y - rectangleEditorTileCuller.getOrigin().y) / (((tilemap->getTileSize().y - tilemap->getTileDepth()) * tilemap->getTileScale().y) / 2)) - ((tilemap->getLayerCount() - zIndex - 1) * (tilemap->getTileDepth() * tilemap->getTileScale().y)) / (((tilemap->getTileSize().y - tilemap->getTileDepth()) * tilemap->getTileScale().y) / 2) - 2;
				int	yEnd	= yStart + (rectangleEditorTileCuller.getSize().y / (((tilemap->getTileSize().y - tilemap->getTileDepth()) * tilemap->getTileScale().y) / 2)) + 4;

				if (xStart < 0)
					xStart = 0;
				else if (xStart > tilemap->getColumnCount() - 1)
					xStart = tilemap->getColumnCount() - 1;

				if (xEnd < 0)
					xEnd = 0;
				else if (xEnd > tilemap->getColumnCount() - 1)
					xEnd = tilemap->getColumnCount() - 1;

				if (yStart < 0)
					yStart = 0;
				else if (yStart	> tilemap->getRowCount() - 1)
					yStart = tilemap->getRowCount() - 1;

				if (yEnd < 0)
					yEnd = 0;
				else if (yEnd > tilemap->getRowCount() - 1)
					yEnd = tilemap->getRowCount() - 1;

				for (int yIndex = yStart; yIndex < yEnd; yIndex++)
				{
					for (int xIndex = xStart; xIndex < xEnd; xIndex++)
					{
						auto* const tile = tilemap->getTile(xIndex, yIndex, zIndex);

						if (((tile->getPosition().y - (tile->getOrigin().y * tilemap->getTileScale().y)) + (tile->getSize().y * tilemap->getTileScale().y)) < (rectangleEditorTileCuller.getPosition().y - rectangleEditorTileCuller.getOrigin().y))
						{
							yStart++;
							yEnd++;
						
							if (yStart < 0)
								yStart = 0;
							else if (yStart > tilemap->getRowCount() - 1)
								yStart = tilemap->getRowCount() - 1;
						
							if (yEnd < 0)
								yEnd = 0;
							else if (yEnd > tilemap->getRowCount() - 1)
								yEnd = tilemap->getRowCount() - 1;
						
							yIndex = yStart - 1;
						
							break;
						}

						if (tile->isRenderEnabled())
						{
							if (static_cast<bool>(tilemap->getPort()))
							{
								if (tilemap->getPort()->isActive())
								{
									this->instance->setView(tilemap->getPort()->getView());
									this->instance->draw(*tile);
									this->instance->setView(originalView);
								}
							}
							else
							{
								this->instance->draw(*tile);
							}
						}
					}
				}
			}
		}

		// shape(s)
		for (auto& shape : am.getShapeData())
		{
			if (shape->isRenderEnabled() && (shape->getRenderLayer() == renderLayer))
			{
				if (static_cast<bool>(shape->getPort()))
				{
					if (shape->getPort()->isActive())
					{
						this->instance->setView(shape->getPort()->getView());
						this->instance->draw(*shape);
						this->instance->setView(originalView);;
					}
				}
				else
				{
					this->instance->draw(*shape);
				}
			}
		}
		
		// text(s)
		for (auto& text : am.getTextData())
		{
			if (text->isRenderEnabled() && (text->getRenderLayer() == renderLayer))
			{
				if (static_cast<bool>(text->getPort()))
				{
					if (text->getPort()->isActive())
					{
						this->instance->setView(text->getPort()->getView());
						this->instance->draw(*text);
						this->instance->setView(originalView);
					}
				}
				else
				{
					this->instance->draw(*text);
				}
			}
		}
	}
}

void Window::display()
{
	this->instance->display();
}

#pragma endregion CORE





#pragma region GETTER(S)

constexpr std::size_t Window::getMinimumWidth()
{
	return Window::minimumWidth;
}

constexpr std::size_t Window::getMinimumHeight()
{
	return Window::minimumHeight;
}

sf::RenderWindow* Window::getInstance() const
{
	return this->instance.get();
}

sf::Vector2u Window::getResolution() const
{
	return this->resolution;
}

sf::String Window::getTitle() const
{
	return this->title;
}

sf::Uint32 Window::getStyle() const
{
	return this->style;
}

sf::ContextSettings Window::getSettings() const
{
	return this->instance->getSettings();
}

std::size_t Window::getRenderLayerCount() const
{
	return this->renderLayerCount;
}

bool Window::isOpen() const
{
	return this->instance->isOpen();
}

sf::Vector2i Window::getPosition() const
{
	return this->instance->getPosition();
}

sf::Vector2u Window::getSize() const
{
	return this->instance->getSize();
}

std::size_t Window::getWidth() const
{
	return this->getSize().x;
}

std::size_t Window::getHeight() const
{
	return this->getSize().y;
}

sf::View Window::getView() const
{
	return this->instance->getView();
}

sf::FloatRect Window::getViewport() const
{
	return this->instance->getView().getViewport();
}

sf::Color Window::getClearColor() const
{
	return this->clearColor;
}

sf::Vector2f Window::getZoom() const
{
	return sf::Vector2f
	(
		this->instance->getSize().x / this->instance->getView().getSize().x,
		this->instance->getSize().y / this->instance->getView().getSize().y
	);
}

sf::Vector2f Window::getScroll() const
{
	return sf::Vector2f
	(
		this->instance->getView().getCenter().x - this->instance->getView().getSize().x / 2,
		this->instance->getView().getCenter().y - this->instance->getView().getSize().y / 2
	);
}

float Window::getRotation() const
{
	return this->instance->getView().getRotation();
}

bool Window::isRenderingPaused() const
{
	return this->renderingPaused;
}

bool Window::isFocused() const
{
	return this->focused;
}

bool Window::isMouseEntered() const
{
	return this->mouseEntered;
}

#pragma endregion GETTER(S)





#pragma region SETTER(S)

void Window::set(
	const sf::Vector2u&			resolution,
	const sf::String&			title,
	const sf::Uint32&			style,
	const sf::ContextSettings&	settings)
{
	if (!static_cast<bool>(this->instance))
	{
		this->instance = std::make_shared<sf::RenderWindow>
		(
			sf::VideoMode(resolution.x, resolution.y, modeBitsPerPixel),
			title,
			style,
			settings
		);
	}
	else
	{
		this->instance.reset(new sf::RenderWindow
		(
			sf::VideoMode(resolution.x, resolution.y, modeBitsPerPixel),
			title,
			style,
			settings
		));
	}

	this->resolution	= resolution;
	this->title			= title;
	this->style			= style;
}

void Window::setResolution(const sf::Vector2u& resolution)
{
	this->set
	(
		resolution,
		this->getTitle(),
		this->getStyle(),
		this->getSettings()
	);
}

void Window::setTitle(const sf::String& title)
{
	this->instance->setTitle(title);
	this->title = title;
}

void Window::setStyle(const sf::Uint32& style)
{
	this->set
	(
		this->getResolution(),
		this->getTitle(),
		style,
		this->getSettings()
	);
}

void Window::setSettings(const sf::ContextSettings& settings)
{
	this->set
	(
		this->getResolution(),
		this->getTitle(),
		this->getStyle(),
		settings
	);
}

void Window::setRenderLayerCount(std::size_t renderLayerCount)
{
	this->renderLayerCount = renderLayerCount;
}

void Window::setPosition(const sf::Vector2i& position)
{
	this->instance->setPosition(position);
}

void Window::setPosition(int x, int y)
{
	this->instance->setPosition(sf::Vector2i(x, y));
}

void Window::setSize(const sf::Vector2u& size)
{
	this->instance->setSize(size);
}

void Window::setSize(std::size_t width, std::size_t height)
{
	this->instance->setSize(sf::Vector2u(sf::Uint32(width), sf::Uint32(height)));
}

void Window::setWidth(std::size_t width)
{
	this->setSize(width, this->getHeight());
}

void Window::setHeight(std::size_t height)
{
	this->setSize(this->getWidth(), height);
}

void Window::setView(const sf::View& view)
{
	this->instance->setView(view);
}

void Window::setView(const sf::FloatRect& rectangle)
{
	this->instance->setView(sf::View(rectangle));
}

void Window::setView(const sf::Vector2f& center, const sf::Vector2f& size)
{
	this->instance->setView(sf::View(center, size));
}

void Window::setView(float x, float y, float width, float height)
{
	this->instance->setView(sf::View(sf::Vector2f(x, y), sf::Vector2f(width, height)));
}

void Window::setViewport(const sf::FloatRect& viewport)
{
	auto view = this->instance->getView();
	view.setViewport(viewport);
	this->instance->setView(view);
}

void Window::setViewport(float x, float y, float width, float height)
{
	auto view = this->instance->getView();
	view.setViewport(sf::FloatRect(x, y, width, height));
	this->instance->setView(view);
}

void Window::setClearColor(const sf::Color& clearColor)
{
	this->clearColor = clearColor;
}

void Window::setClearColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
	this->clearColor = sf::Color(r, g, b, a);
}

void Window::setZoom(float scalar)
{
	this->setView
	(
		this->instance->getView().getCenter().x,
		this->instance->getView().getCenter().y,
		this->instance->getSize().x / scalar,
		this->instance->getSize().y / scalar
	);
}

void Window::setZoom(float x, float y)
{
	this->setView
	(
		this->instance->getView().getCenter().x,
		this->instance->getView().getCenter().y,
		this->instance->getSize().x / x,
		this->instance->getSize().y / y
	);
}

void Window::setZoom(const sf::Vector2f& zoom)
{
	this->setView
	(
		this->instance->getView().getCenter().x,
		this->instance->getView().getCenter().y,
		this->instance->getSize().x / zoom.x,
		this->instance->getSize().y / zoom.y
	);
}

void Window::setScroll(float horizontal, float vertical)
{
	this->instance->setView(sf::View
	(
		sf::Vector2f((this->instance->getSize().x / 2) + horizontal, (this->instance->getSize().y / 2) + vertical),
		sf::Vector2f(this->instance->getSize())
	));
}

void Window::setScroll(const sf::Vector2f& scroll)
{
	this->setScroll(scroll.x, scroll.y);
}

void Window::setRotation(float rotation)
{
	auto view = this->instance->getView();
	view.setRotation(rotation);
	this->instance->setView(view);
}

void Window::setRenderingPaused(bool renderingPaused)
{
	this->renderingPaused = renderingPaused;
}

void Window::setFocused(bool focused)
{
	this->focused = focused;
}

void Window::setMouseEntered(bool mouseEntered)
{
	this->mouseEntered = mouseEntered;
}

#pragma endregion SETTER(S)





#pragma region PORT(S)

Port* Window::createPort(Port&& port)
{
	std::lock_guard<std::mutex> _(this->mutex);
	this->ports.emplace_back(std::make_shared<Port>(std::move(port)));
	return this->ports.back().get();
}

Port* Window::createPort(const std::string& id, const sf::FloatRect& viewport, std::size_t renderLayerCount, bool active)
{
	std::lock_guard<std::mutex> _(this->mutex);
	this->ports.emplace_back(std::make_shared<Port>(std::move(Port(id, viewport, renderLayerCount, active))));
	return this->ports.back().get();
}

Port* Window::createPort(const std::string& id, float x, float y, float width, float height, std::size_t renderLayerCount, bool active)
{
	std::lock_guard<std::mutex> _(this->mutex);
	this->ports.emplace_back(std::make_shared<Port>(std::move(Port(id, sf::FloatRect(x, y, width, height), renderLayerCount, active))));
	return this->ports.back().get();
}

std::size_t Window::getPortCount() const
{
	return this->ports.size();
}

Port* Window::getPort(std::size_t index)
{
	return this->ports[index].get();
}

Port* Window::getPort(const std::string& id)
{
	for (std::size_t index = 0; index < this->ports.size(); index++)
	{
		if (this->ports[index]->getId() == id)
		{
			return this->ports[index].get();
		}
	}

	return nullptr;
}

Port* Window::getPortFront()
{
	return this->ports.front().get();
}

Port* Window::getPortBack()
{
	return this->ports.back().get();
}

std::vector<std::shared_ptr<Port>>& Window::getPortData()
{
	return this->ports;
}

void Window::removePort(std::size_t index)
{
	this->ports.erase(this->ports.begin() + index);
}

void Window::removePort(const std::string& id)
{
	for (std::size_t index = 0; index < this->ports.size(); index++)
	{
		if (this->ports[index]->getId() == id)
		{
			this->ports.erase(this->ports.begin() + index);
			index--;
		}
	}
}

void Window::removePorts(Scene* scene)
{
	this->ports.clear();
}

void Window::iteratePorts(const std::function<void(Port&)>& function)
{
	for (auto& port : this->ports)
	{
		function(*port);
	}
}

void Window::resizePorts()
{
	for (auto& port : this->ports)
		port->resize();
}

#pragma endregion PORT(S)
