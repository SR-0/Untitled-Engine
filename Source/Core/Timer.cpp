#include "Core/Timer.h"

Timer::Timer(const std::string& id)
{
	this->id = id;
}

Timer::Timer(const std::string& id, const sf::Time& time, bool paused)
{
	this->id			= id;
	this->originalTime	= time;
	this->remainingTime	= time;
	this->paused		= paused;
}

Timer::Timer(const std::string& id, float seconds, bool paused)
{
	this->id			= id;
	this->originalTime	= sf::Time(sf::seconds(seconds));
	this->remainingTime	= sf::Time(sf::seconds(seconds));
	this->paused		= paused;
}

void Timer::update(const sf::Time& deltaTime)
{
	if (!this->paused)
		if (this->remainingTime > sf::Time::Zero)
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

const sf::Time& Timer::getOriginalTime() const
{
	return this->originalTime;
}

const sf::Time& Timer::getRemainingTime() const
{
	return this->remainingTime > sf::Time::Zero ? this->remainingTime : sf::Time::Zero;
}

bool Timer::isPaused() const
{
	return this->paused;
}

void Timer::setId(const std::string& id)
{
	this->id = id;
}

void Timer::pause()
{
	this->paused = true;
}

void Timer::resume()
{
	this->paused = false;
}

void Timer::restart(const sf::Time& time)
{
	this->originalTime	= time;
	this->remainingTime	= time;
}

void Timer::restart(float seconds)
{
	this->originalTime	= sf::Time(sf::seconds(seconds));
	this->remainingTime	= sf::Time(sf::seconds(seconds));
}
