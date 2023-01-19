#pragma once

#include <SFML/Graphics/Rect.hpp>

// to do inplement row stop

class Animation
{
private:

	sf::IntRect		uvRect			= sf::IntRect{};
	sf::Vector2u	imageCount		= sf::Vector2u{};
	sf::Vector2u	currentImage	= sf::Vector2u{};
	float			totalTime		= float{};
	float			switchTime		= float{};
	bool			active			= false;
	std::size_t		activeRow		= 0;
	class Shape*	shape			= nullptr;

public:

	Animation();
	Animation(const Shape* shape, sf::Vector2u imageCount, float switchTime, std::size_t activeRow = 0);

public:

	void set(const Shape* shape, sf::Vector2u imageCount, float switchTime, std::size_t activeRow = 0);
	void update(float deltaTime);

public:

	const sf::IntRect&	getUvRect() const;
	const sf::Vector2u&	getImageCount() const;
	const sf::Vector2u&	getCurrentImage() const;
	float				getTotalTime() const;
	float				getSwitchTime() const;
	bool				isActive() const;
	std::size_t			getActiveRow() const;

public:

	void setUvRect(const sf::IntRect& uvRect);
	void setImageCount(const sf::Vector2u& imageCount);
	void setCurrentImage(const sf::Vector2u& currentImage);
	void setTotalTime(float totalTime);
	void setSwitchTime(float switchTime);
	void setActive(bool active);
	void setActiveRow(std::size_t activeRow);

};