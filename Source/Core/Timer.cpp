#include "Core/Timer.h"

Timer::Timer(const std::string& id)
{
	this->id = id;
}

Timer::Timer(const std::string& id, const sf::Time& time, bool paused)
{
	this->id			= id;
	this->startingTime	= time;
	this->remainingTime	= time;
	this->paused		= paused;
}

Timer::Timer(const std::string& id, float seconds, bool paused)
{
	this->id			= id;
	this->startingTime	= sf::Time(sf::seconds(seconds));
	this->remainingTime	= sf::Time(sf::seconds(seconds));
	this->paused		= paused;
}

void Timer::update(const sf::Time& deltaTime)
{
	if (!this->isPaused() && !this->isCompleted())
		this->remainingTime -= deltaTime;

}

const std::string& Timer::getUuid() const
{
	return this->uuid;
}

const std::string& Timer::getId() const
{
	return this->id;
}

const sf::Time& Timer::getStartingTime() const
{
	return this->startingTime;
}

const sf::Time& Timer::getRemainingTime() const
{
	return this->remainingTime > sf::Time::Zero ? this->remainingTime : sf::Time::Zero;
}

bool Timer::isPaused() const
{
	return this->paused;
}

bool Timer::isCompleted() const
{
	return this->remainingTime <= sf::Time::Zero;
}

void Timer::setId(const std::string& id)
{
	this->id = id;
}

void Timer::setStartingTime(const sf::Time& startingTime)
{
	this->startingTime = startingTime;
}

void Timer::setStartingTime(float seconds)
{
	this->startingTime = sf::Time(sf::seconds(seconds));
}

void Timer::pause()
{
	this->paused = true;
}

void Timer::resume()
{
	this->paused = false;
}

void Timer::restart(bool paused)
{
	this->remainingTime = this->startingTime;
	this->paused		= paused;
}