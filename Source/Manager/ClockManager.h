#pragma once

#include "Core/Timer.h"
#include "Core/Stopwatch.h"
#include <mutex>
#include <functional>

class ClockManager
{
private: // data

	sf::Clock				clock			= sf::Clock{};
	sf::Time				deltaTime		= sf::Time::Zero;
	sf::Time				totalTime		= sf::Time::Zero;
	std::vector<Timer>		timers			= std::vector<Timer>{};
	std::vector<Stopwatch>	stopwatches		= std::vector<Stopwatch>{};
	std::mutex				mutex			= std::mutex{};

public: // ctor(s)/dtor(s)

	ClockManager() = default;
	ClockManager(const ClockManager&) = delete;
	ClockManager(ClockManager&&) = delete;
	~ClockManager() = default;

private: // operator overloading

	ClockManager& operator = (const ClockManager&) = delete;
	ClockManager& operator = (ClockManager&&) = delete;

private: // core

	void update(); // for use within Engine.cpp only

public: // timers

	Timer&				createTimer(const std::string& id = "unidentified");
	Timer&				createTimer(const std::string& id, const sf::Time& time, bool paused = false);
	Timer&				createTimer(const std::string& id, float seconds, bool paused = false);
	std::size_t			getTimerCount() const;
	Timer&				getTimer(std::size_t index);
	Timer*				getTimer(const std::string& id);
	Timer&				getTimerFront();
	Timer&				getTimerBack();
	std::vector<Timer>&	getTimerData();
	void				removeTimer(std::size_t index);
	void				removeTimer(const std::string& id);
	void				removeTimer(Timer* Timer);
	void				removeTimers();
	void				iterateTimers(const std::function<void(Timer&)>& function, bool reversed = false);

public: // stopwatches

	Stopwatch&				createStopwatch(const std::string& id = "unidentified", bool paused = false);
	std::size_t				getStopwatchCount() const;
	Stopwatch&				getStopwatch(std::size_t index);
	Stopwatch*				getStopwatch(const std::string& id);
	Stopwatch&				getStopwatchFront();
	Stopwatch&				getStopwatchBack();
	std::vector<Stopwatch>&	getStopwatchData();
	void					removeStopwatch(std::size_t index);
	void					removeStopwatch(const std::string& id);
	void					removeStopwatch(Stopwatch* Stopwatch);
	void					removeStopwatches();
	void					iterateStopwatches(const std::function<void(Stopwatch&)>& function, bool reversed = false);

public: // getter(s)

	const sf::Time&	getDeltaTime() const;
	const sf::Time&	getTotalTime() const;

private: // friend(s)

	friend class Engine;
	friend class AssetManager;
	friend class SceneManager;

};