#include "Manager/ClockManager.h"





#pragma region CORE

void ClockManager::update()
{
	this->deltaTime = this->clock.restart();
	this->totalTime += this->deltaTime;

	for (auto& timer : this->timers)
		timer.update(this->deltaTime);

	for (auto& stopwatch : this->stopwatches)
		stopwatch.update(this->deltaTime);
}

#pragma endregion CORE





#pragma region TIMER(S)

Timer& ClockManager::createTimer(const std::string& id)
{
	std::lock_guard<std::mutex> _{ this->mutex };
	this->timers.push_back(Timer(id));
	return this->timers.back();
}

Timer& ClockManager::createTimer(const std::string& id, const sf::Time& time, bool paused)
{
	std::lock_guard<std::mutex> _{ this->mutex };
	this->timers.push_back(Timer(id, time, paused));
	return this->timers.back();
}

Timer& ClockManager::createTimer(const std::string& id, float seconds, bool paused)
{
	std::lock_guard<std::mutex> _{ this->mutex };
	this->timers.push_back(Timer(id, seconds, paused));
	return this->timers.back();
}

std::size_t ClockManager::getTimerCount() const
{
	return this->timers.size();
}

Timer& ClockManager::getTimer(std::size_t index)
{
	return this->timers[index];
}

Timer* ClockManager::getTimer(const std::string& id) // has to be pointer is no id is matched
{
	for (std::size_t index = 0; index < this->timers.size(); index++)
	{
		if (this->timers[index].getId() == id)
		{
			return &this->timers[index];
		}
	}

	return nullptr;
}

Timer& ClockManager::getTimerFront()
{
	return this->timers.front();
}

Timer& ClockManager::getTimerBack()
{
	return this->timers.back();
}

std::vector<Timer>& ClockManager::getTimerData()
{
	return this->timers;
}

void ClockManager::removeTimer(std::size_t index)
{
	this->timers.erase(this->timers.begin() + index);
}

void ClockManager::removeTimer(const std::string& id)
{
	for (std::size_t index = 0; index < this->timers.size(); index++)
	{
		if (this->timers[index].getId() == id)
		{
			this->timers.erase(this->timers.begin() + index);
			index--;
		}
	}
}

void ClockManager::removeTimer(Timer* timer)
{
	for (std::size_t i = 0; i < this->timers.size(); i++)
	{
		if (&this->timers[i] == timer)
		{
			this->timers.erase(this->timers.begin() + i);
			break;
		}
	}
}

void ClockManager::removeTimers()
{
	this->timers.clear();
}

void ClockManager::iterateTimers(const std::function<void(Timer&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->timers.rbegin(); iter != this->timers.rend(); iter++)
			return function(*iter);

	for (auto iter = this->timers.begin(); iter != this->timers.end(); iter++)
		return function(*iter);
}

#pragma endregion TIMER(S)





#pragma region STOPWATCH(ES)

Stopwatch& ClockManager::createStopwatch(const std::string& id, bool paused)
{
	std::lock_guard<std::mutex> _{ this->mutex };
	this->stopwatches.push_back(Stopwatch(id, paused));
	return this->stopwatches.back();
}

std::size_t ClockManager::getStopwatchCount() const
{
	return this->stopwatches.size();
}

Stopwatch& ClockManager::getStopwatch(std::size_t index)
{
	return this->stopwatches[index];
}

Stopwatch* ClockManager::getStopwatch(const std::string& id) // has to be pointer is no id is matched
{
	for (std::size_t index = 0; index < this->stopwatches.size(); index++)
	{
		if (this->stopwatches[index].getId() == id)
		{
			return &this->stopwatches[index];
		}
	}

	return nullptr;
}

Stopwatch& ClockManager::getStopwatchFront()
{
	return this->stopwatches.front();
}

Stopwatch& ClockManager::getStopwatchBack()
{
	return this->stopwatches.back();
}

std::vector<Stopwatch>& ClockManager::getStopwatchData()
{
	return this->stopwatches;
}

void ClockManager::removeStopwatch(std::size_t index)
{
	this->stopwatches.erase(this->stopwatches.begin() + index);
}

void ClockManager::removeStopwatch(const std::string& id)
{
	for (std::size_t index = 0; index < this->stopwatches.size(); index++)
	{
		if (this->stopwatches[index].getId() == id)
		{
			this->stopwatches.erase(this->stopwatches.begin() + index);
			index--;
		}
	}
}

void ClockManager::removeStopwatch(Stopwatch* Stopwatch)
{
	for (std::size_t i = 0; i < this->stopwatches.size(); i++)
	{
		if (&this->stopwatches[i] == Stopwatch)
		{
			this->stopwatches.erase(this->stopwatches.begin() + i);
			break;
		}
	}
}

void ClockManager::removeStopwatches()
{
	this->stopwatches.clear();
}

void ClockManager::iterateStopwatches(const std::function<void(Stopwatch&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->stopwatches.rbegin(); iter != this->stopwatches.rend(); iter++)
			return function(*iter);

	for (auto iter = this->stopwatches.begin(); iter != this->stopwatches.end(); iter++)
		return function(*iter);
}

#pragma endregion STOPWATCH(ES)





#pragma region GETTTER(S)

const sf::Time& ClockManager::getDeltaTime() const
{
	return this->deltaTime;
}

const sf::Time& ClockManager::getTotalTime() const
{
	return this->totalTime;
}

#pragma endregion GETTTER(S)
