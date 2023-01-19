#pragma once

#include <SFML/System.hpp>
#include "Utility/Utility.h"

class Stopwatch
{
private: // data

	std::string	uuid		= utility::get_uuid();
	std::string	id			= std::string{};
	sf::Time	elapsedTime	= sf::Time::Zero;
	bool		paused		= false;

public:

	Stopwatch(const std::string& id = "unidentified", bool paused = false);

private: // core

	void update(const sf::Time& deltaTime); // for use within ClockManager only

public: // getter(s)

	const std::string&	getUuid() const;
	const std::string&	getId() const;
	const sf::Time&		getElapsedTime() const;
	bool				isPaused() const;

public: // setter(s)

	void setId(const std::string& id);

public: // utility

	void pause();
	void resume();
	void restart();

private: // friend(s)

	friend class ClockManager;

};