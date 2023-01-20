#pragma once

#include <SFML/Window/Event.hpp>
#include <vector>
#include <functional>
#include <mutex>
#include "Core/Binding.h"

class EventManager
{
private: // data

	std::vector<std::shared_ptr<Binding>>	bindings					= {};
	std::mutex								mutex						= std::mutex{};
	bool									keyPressInhibited			= false;
	bool									mousePressInhibited			= false;
	bool									mouseWheelScrollInhibited	= false;
	bool									autoUninhibited				= false;
	bool									textInputEnabled			= false;

public: // ctor(s)/dtor(s)

	EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	~EventManager();

private: // operator overloading

	EventManager& operator = (const EventManager&) = delete;
	EventManager& operator = (EventManager&&) = delete;

private: // core

	void update(float deltaTime); // for use within Engine.cpp only

public: // bindings

	template <typename Derived, typename ... Args> Derived*	createBinding(Args ... args);
	std::size_t												getBindingCount() const;
	Binding*												getBinding(std::size_t index);
	Binding*												getBinding(const std::string& id);
	Binding*												getBindingFront();
	Binding*												getBindingBack();
	std::vector<std::shared_ptr<Binding>>&					getBindingData();
	void													removeBinding(std::size_t index);
	void													removeBinding(const std::string& id);
	void													removeBindings(class Scene* scene = nullptr);
	void													iterateBindings(const std::function<void(Binding&)>& function, bool reversed = false);

public: // getter(s)

	sf::Vector2i	getLocalMousePosition() const;
	sf::Vector2i	getGlobalMousePosition() const;
	bool			isKeyPressInhibited() const;
	bool			isMousePressInhibited() const;
	bool			isMouseWheelScrollInhibited() const;
	bool			isAutoUninhibited() const;
	bool			isTextInputEnabled() const;

public: // setter(s)

	void setKeyPressInhibited(bool keyPressInhibited);
	void setMousePressInhibited(bool mousePressInhibited);
	void setMouseWheelScrollInhibited(bool mouseWheelScrollInhibited);
	void setAutoUninhibited(bool autoUninhibited);
	void setTextInputEnabled(bool textInputEnabled);

private: // friend(s)

	friend class Engine;

};

template <typename Derived, typename ... Args>
Derived* EventManager::createBinding(Args ... args)
{
	if (std::is_base_of<Binding, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->bindings.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->bindings.back().get()->as<Derived>();
	}

	return nullptr;
}