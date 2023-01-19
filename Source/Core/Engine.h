#pragma once

#include "Core/Global.h"

class Engine
	:
	public Window,
	public ClockManager,
	public EventManager,
	public SceneManager,
	public AssetManager
{
private:

	static constexpr std::size_t	minMaxTicksPerSecond	= 24; // limiting user to 0 (no limit) or at least 24 max tick per second
	static constexpr std::size_t	minMaxFramesPerSecond	= 24; // limiting user to 0 (no limit) or at least 24 max frames per second (possible change) 
	static std::size_t				maxTicksPerSecond;
	static std::size_t				maxFramesPerSecond;
	static sf::Time					timeSinceLastUpdate;
	static sf::Time					timeSinceLastRender;
	static sf::Time					deltaTimeBuildUp;
	static bool						updating;
	static bool						rendering;

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

public: // getter(s)

	static std::size_t	getMaxTicksPerSecond();
	static std::size_t	getMaxFramesPerSecond();


public: // setter(s)
	 
	static void setMaxTicksPerSecond(std::size_t maxTicksPerSecond);
	static void setMaxFramesPerSecond(std::size_t maxFramesPerSecond);

};