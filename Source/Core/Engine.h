#pragma once

#include "Core/Global.h"

class Engine
{
public: // data

	Window			window			= Window(sf::Vector2u(1920, 1080), "Untitled Engine", sf::Style::None, sf::ContextSettings());
	ClockManager	clockManager	= ClockManager{};
	EventManager	eventManager	= EventManager{};
	SceneManager	sceneManager	= SceneManager{};
	AssetManager	assetManager	= AssetManager{};
	ScriptManager	scriptManager	= ScriptManager{};

public: // ctor(s)/dtor(s)

	Engine();
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	~Engine() = default;

private: // operator overloading

	Engine& operator = (const Engine&) = delete;
	Engine& operator = (Engine&&) = delete;

public: // core

	bool isRunning();
	void update();
	void render();

};