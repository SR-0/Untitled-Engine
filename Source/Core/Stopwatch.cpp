#include "Core/Stopwatch.h"

Stopwatch::Stopwatch(const std::string& id, bool paused)
{
	this->id        = id;
	this->paused    = paused;
}

void Stopwatch::update(const sf::Time& deltaTime)
{
	if (!this->paused)
		this->elapsedTime += deltaTime;
}

const std::string& Stopwatch::getUuid() const
{
	return this->uuid;
}

const std::string& Stopwatch::getId() const
{
	return this->id;
}

const sf::Time& Stopwatch::getElapsedTime() const
{
	return this->elapsedTime;
}

bool Stopwatch::isPaused() const
{
	return this->paused;
}

void Stopwatch::setId(const std::string& id)
{
	this->id = id;
}

void Stopwatch::pause()
{
	this->paused = true;
}

void Stopwatch::resume()
{
	this->paused = false;
}

void Stopwatch::restart()
{
	this->elapsedTime = sf::Time::Zero;
}
