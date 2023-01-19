#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <memory>
#include "Utility/Utility.h"

class Port
{
private: // data

	std::string			uuid				= utility::get_uuid();
	std::string			id					= "unidentified";
	bool				active				= true;
	sf::View			view				= sf::View{};
	std::size_t			renderLayerCount	= 1;
	class Rectangle*	background			= nullptr;
	class Rectangle*	border				= nullptr; // @TODO implement port border

public: // ctor(s)/dtor(s)

	Port();
	Port(const std::string& id, const sf::FloatRect& viewport = sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f), std::size_t renderLayerCount = 1, bool active = true);
	Port(const std::string& id = "unidentified", float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f, std::size_t renderLayerCount = 1, bool active = true);

public:

	void resize();

public: // getters(s)

	const std::string&	getUuid() const;
	const std::string&	getId() const;
	bool				isActive() const;
	std::size_t			getRenderLayerCount() const;
	sf::View			getView() const;
	sf::FloatRect		getViewport() const;
	sf::Vector2f		getSize() const;
	sf::Vector2f		getCenter() const;
	sf::Vector2f		getZoom() const;
	sf::Vector2f		getScroll() const;
	float				getRotation() const;
	class Rectangle*	getBackground() const;
	class Rectangle*	getBorder() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setRenderLayerCount(std::size_t renderLayerCount);
	void setView(const sf::View& view);
	void setView(const sf::FloatRect& rectangle);
	void setView(const sf::Vector2f& center, const sf::Vector2f& size);
	void setView(float x, float y, float width, float height);
	void setViewport(const sf::FloatRect& viewport);
	void setViewport(float x, float y, float width, float height);
	void setZoom(float zoom);
	void setZoom(float x, float y);
	void setZoom(const sf::Vector2f& scalar);
	void setScroll(float horizontal, float vertical);
	void setScroll(const sf::Vector2f& scroll);
	void setRotation(float rotation);

};

