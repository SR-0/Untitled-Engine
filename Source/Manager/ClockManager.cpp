#include "Manager/ClockManager.h"





#pragma region CORE

void ClockManager::update()
{
	this->delta = this->clock.restart();
	this->total += this->delta;
}

#pragma endregion CORE





#pragma region GETTTER(S)

const sf::Time& ClockManager::getDeltaTime() const
{
	return this->delta;
}

const sf::Time& ClockManager::getTotalTime() const
{
	return this->total;
}

#pragma endregion GETTTER(S)