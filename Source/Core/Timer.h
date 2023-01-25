#pragma once

#include <SFML/System.hpp>
#include "Utility/Utility.h"

class Timer
{
private: // data

	std::string uuid            = utility::get_uuid();
	std::string id              = std::string{};
	sf::Time    startingTime    = sf::Time::Zero;
	sf::Time    remainingTime   = sf::Time::Zero;
	bool        paused          = false;

public:

	Timer(const std::string& id = "unidentified");
	Timer(const std::string& id, const sf::Time& time, bool paused = false);
	Timer(const std::string& id, float seconds, bool paused = false);

private: // core

	void update(const sf::Time& deltaTime); // for use within ClockManager only

public: // getter(s)

	const std::string&  getUuid() const;
	const std::string&  getId() const;
	const sf::Time&     getStartingTime() const;
	const sf::Time&     getRemainingTime() const;
	bool                isPaused() const;
	bool                isCompleted() const;

public: // setter(s)

	void setId(const std::string& id);
	void setStartingTime(const sf::Time& startingTime);
	void setStartingTime(float seconds);

public: // utility

	void pause();
	void resume();
	void restart(bool paused = false);

private: // friend(s)

	friend class ClockManager;

};

