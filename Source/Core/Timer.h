#pragma once

#include <SFML/System.hpp>
#include "Utility/Utility.h"

class Timer
{
private: // data

	std::string	uuid			= utility::get_uuid();
	std::string	id				= std::string{};
	sf::Time	originalTime	= sf::Time::Zero;
	sf::Time	remainingTime	= sf::Time::Zero;
	bool		paused			= false;

public:

	Timer(const std::string& id = "unidentified");
	Timer(const std::string& id, const sf::Time& time, bool paused = false);
	Timer(const std::string& id, float seconds, bool paused = false);

private: // core

	void update(const sf::Time& deltaTime); // for use within ClockManager only

public: // getter(s)

	const std::string&	getUuid() const;
	const std::string&	getId() const;
	const sf::Time&		getOriginalTime() const;
	const sf::Time&		getRemainingTime() const;
	bool				isPaused() const;

public: // setter(s)

	void setId(const std::string& id);

public: // utility

	void pause();
	void resume();
	void restart(const sf::Time& time);
	void restart(float seconds);

private: // friend(s)

	friend class ClockManager;

};

