#pragma once

#include <SFML/System.hpp>

class ClockManager
{
private: // data

	sf::Clock	clock;
	sf::Time	delta;
	sf::Time	total;

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

public: // getter(s)

	const sf::Time&	getDeltaTime() const;
	const sf::Time&	getTotalTime() const;

private: // friend(s)

	friend class Engine;
	friend class AssetManager;
	friend class SceneManager;

};