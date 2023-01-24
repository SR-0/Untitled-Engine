#pragma once





#include <SFML/Graphics/RenderWindow.hpp>
#include "Core/Port.h"
#include <memory>
#include <mutex>
#include <functional>





class Window
{
private: // data

	static constexpr std::size_t		minimumWidth		= 1280;
	static constexpr std::size_t		minimumHeight		= 720;
	static constexpr sf::Uint32			modeBitsPerPixel	= 32; // @TODO dig
	std::shared_ptr<sf::RenderWindow>	instance			= nullptr;
	std::size_t							renderLayerCount	= 1;
	sf::Vector2u						resolution			= sf::Vector2u(Window::minimumWidth, Window::minimumHeight);
	sf::String							title				= sf::String{};
	sf::Uint32							style				= 0;
	sf::Color							clearColor			= sf::Color::Black;
	std::size_t							framerateLimit		= 0;
	bool								renderingPaused		= false;
	bool								focused				= true;
	bool								mouseEntered		= false;
	std::vector<std::shared_ptr<Port>>	ports				= {};
	std::mutex							mutex				= std::mutex{};

public: // ctor(s)/dtor(s)

	Window(bool autoSetup = false);
	Window(
		const sf::Vector2u&			resolution,
		const sf::String&			title,
		const sf::Uint32&			style,
		const sf::ContextSettings&	settings);
	Window(const Window&) = delete;

public: // core

	void close();

private: // core
	
	bool pollEvent(sf::Event& event);
	void clear();
	void clear(const sf::Color& clearColor);
	void clear(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);
	void draw(const sf::Drawable& drawable);
	void draw();
	void display();

public: // getters(s)

	inline static constexpr std::size_t	getMinimumWidth()	{ return Window::minimumWidth; }
	inline static constexpr std::size_t	getMinimumHeight()	{ return Window::minimumHeight; }
	sf::RenderWindow*					getInstance() const;
	sf::Vector2u						getResolution() const;
	std::size_t							getResolutionWidth() const;
	std::size_t							getResolutionHeight() const;
	sf::String							getTitle() const;
	sf::Uint32							getStyle() const;
	sf::ContextSettings					getSettings() const;
	std::size_t							getRenderLayerCount() const;
	bool								isOpen() const;
	sf::Vector2i						getPosition() const;
	sf::Vector2u						getSize() const;
	std::size_t							getWidth() const;
	std::size_t							getHeight() const;
	sf::View							getView() const;
	sf::FloatRect						getViewport() const;
	sf::Color							getClearColor() const;
	sf::Vector2f						getZoom() const;
	sf::Vector2f						getScroll() const;
	float								getRotation() const;
	bool								isRenderingPaused() const;
	bool								isFocused() const;
	bool								isMouseEntered() const;

public: // setter(s)

	void set
	(
		const sf::Vector2u&			resolution,
		const sf::String&			title,
		const sf::Uint32&			style,
		const sf::ContextSettings&	settings
	);

	void setResolution(const sf::Vector2u& resolution);
	void setResolution(std::size_t width, std::size_t height);
	void setTitle(const sf::String& title);
	void setStyle(const sf::Uint32& style);
	void setSettings(const sf::ContextSettings& settings);
	void setRenderLayerCount(std::size_t renderLayerCount);
	void setPosition(const sf::Vector2i& position);
	void setPosition(int x, int y);
	void setSize(const sf::Vector2u& size);
	void setSize(std::size_t width, std::size_t height);
	void setWidth(std::size_t width);
	void setHeight(std::size_t height);
	void setView(const sf::View& view);
	void setView(const sf::FloatRect& rectangle);
	void setView(const sf::Vector2f& center, const sf::Vector2f& size);
	void setView(float x, float y, float width, float height);
	void setViewport(const sf::FloatRect& viewport);
	void setViewport(float x, float y, float width, float height);
	void setClearColor(const sf::Color& clearColor);
	void setClearColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255);
	void setZoom(float zoom);
	void setZoom(float x, float y);
	void setZoom(const sf::Vector2f& scalar);
	void setScroll(float horizontal, float vertical);
	void setScroll(const sf::Vector2f& scroll);
	void setRotation(float rotation);
	void setRenderingPaused(bool renderingPaused);

private: // setter(s) (for friends only)

	void setFocused(bool focused);
	void setMouseEntered(bool mouseEntered);

public: // ports

	Port*								createPort(const std::string& id = "unidentified", const sf::FloatRect& viewport = sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f), std::size_t renderLayerCount = 1, bool active = true);
	Port*								createPort(const std::string& id = "unidentified", float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f, std::size_t renderLayerCount = 1, bool active = true);
	std::size_t							getPortCount() const;
	Port*								getPort(std::size_t index);
	Port*								getPort(const std::string& id);
	Port*								getPortFront();
	Port*								getPortBack();
	std::vector<std::shared_ptr<Port>>&	getPortData();
	void								removePort(std::size_t index);
	void								removePort(const std::string& id);
	void								removePorts(class Scene* scene = nullptr);
	void								iteratePorts(const std::function<void(Port&)>& function);
	void								resizePorts();

private: // friend(s)

	friend class Engine;
	friend class EventManager;
	friend class Binding;

};

