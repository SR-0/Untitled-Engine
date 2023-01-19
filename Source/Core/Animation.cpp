#include "Core/Animation.h"
#include "Asset/Shape.h"



#pragma region CONSTRUCTORS AND DESTRUCTORS

Animation::Animation()
{
}

Animation::Animation(const Shape* shape, sf::Vector2u imageCount, float switchTime, std::size_t activeRow)
{
	this->set(shape, imageCount, switchTime, activeRow);
}

#pragma endregion





#pragma region PRIMARY

void Animation::set(const Shape* shape, sf::Vector2u imageCount, float switchTime, std::size_t activeRow)
{
	this->imageCount.x		= imageCount.x;
	this->imageCount.y		= imageCount.y;
	this->switchTime		= switchTime;
	this->totalTime			= 0.f;
	this->currentImage.x	= 0;
	this->currentImage.y	= 0;
	this->uvRect.width		= shape->getTexture()->getSize().x / imageCount.x;
	this->uvRect.height		= shape->getTexture()->getSize().y / imageCount.y;
	this->activeRow			= activeRow;
}

void Animation::update(float deltaTime)
{
	this->totalTime += deltaTime;

	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		this->currentImage.x++;

		if (this->currentImage.x >= this->imageCount.x)
			this->currentImage.x = 0;
	}

	if (this->currentImage.y >= this->imageCount.y)
		this->currentImage.y = 0;

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top  = this->currentImage.y * this->uvRect.height;

	this->shape->setTextureRect(
	{
		this->uvRect.left,
		this->uvRect.top,
		this->uvRect.width,
		this->uvRect.height
	});
}

const sf::IntRect& Animation::getUvRect() const
{
	return this->uvRect;
}

const sf::Vector2u& Animation::getImageCount() const
{
	return this->imageCount;
}

const sf::Vector2u& Animation::getCurrentImage() const
{
	return this->currentImage;
}

float Animation::getTotalTime() const
{
	return this->totalTime;
}

float Animation::getSwitchTime() const
{
	return this->switchTime;
}

bool Animation::isActive() const
{
	return this->active;
}

std::size_t Animation::getActiveRow() const
{
	return this->activeRow;
}

void Animation::setUvRect(const sf::IntRect& uvRect)
{
	this->uvRect = uvRect;
}

void Animation::setImageCount(const sf::Vector2u& imageCount)
{
	this->imageCount = imageCount;
}

void Animation::setCurrentImage(const sf::Vector2u& currentImage)
{
	this->currentImage = currentImage;
}

void Animation::setTotalTime(float totalTime)
{
	this->totalTime = totalTime;
}

void Animation::setSwitchTime(float switchTime)
{
	this->switchTime = switchTime;
}

void Animation::setActive(bool active)
{
	this->active = active;
}

void Animation::setActiveRow(std::size_t activeRow)
{
	this->activeRow = activeRow;
}

#pragma endregion