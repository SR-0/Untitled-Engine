#pragma once





#pragma region INCLUDE(S)

#include <string>
#include <type_traits>
#include <functional>
#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Utility//Utility.h"
#include "Core/Scene.h"
#include "Core/Port.h"

#pragma endregion INCLUDE(S)





#pragma region INTERFACE

template <typename Base>
class Asset
{
private: // data

	std::string					uuid			= utility::get_uuid();
	std::string					id				= std::string{};
	bool						active			= false;
	bool						timeScaled		= false; // not sure I like time scale
	float						timeScale		= 1.0f;
	Base*						base			= nullptr;
	Scene*						parentScene		= nullptr;
	Port*						port			= nullptr;
	std::function<void(float)>	functionUpdate	= [](float){};

public: // ctor(s)/dtor(s)

	Asset(Base& base, Scene* parentScene = nullptr);
	Asset(Base& base, const std::string& id, Scene* parentScene = nullptr);

protected: // core

	void callUpdate(float deltaTime); // meant to be used with AssetManager

public: // getter(s)

	const std::string&						getUuid() const;
	const std::string&						getId() const;
	bool									isActive() const;
	bool									isTimeScaled() const;
	float									getTimeScale() const;
	Scene*									getParentScene() const;
	Port*									getPort() const;
	template <typename Derived> Derived*	as() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setTimeScaled(bool timeScaled);
	void setTimeScale(float timeScale);
	void setParentScene(Scene* parentScene);
	void setPort(Port& port);
	void setUpdate(std::function<void(float deltaTime)>&& functionUpdate);

private: // friend(s)

	friend class Shape;
	friend class AssetManager;

};

#pragma endregion INTERFACE





#pragma region CTOR(S)/DTOR(S)

template<typename Base>
inline Asset<Base>::Asset(Base& base, Scene* parentScene)
{
	this->base			= &base;
	this->parentScene	= parentScene;
}

template<typename Base>
inline Asset<Base>::Asset(Base& base, const std::string& id, Scene* parentScene)
{
	this->base			= &base;
	this->id			= id;
	this->parentScene	= parentScene;
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

template<typename Base>
inline void Asset<Base>::callUpdate(float deltaTime)
{
	this->functionUpdate(deltaTime);
}

#pragma endregion CORE





#pragma region GETTER(S)

template<typename Base>
inline const std::string& Asset<Base>::getUuid() const
{
	return this->uuid;
}

template<typename Base>
inline const std::string& Asset<Base>::getId() const
{
	return this->id;
}

template<typename Base>
inline bool Asset<Base>::isActive() const
{
	return this->active && (static_cast<bool>(this->parentScene) ? this->parentScene->isActive() : true);
}

template<typename Base>
inline bool Asset<Base>::isTimeScaled() const
{
	return this->timeScaled;
}

template<typename Base>
inline float Asset<Base>::getTimeScale() const
{
	return this->timeScale;
}

template<typename Base>
inline Scene* Asset<Base>::getParentScene() const
{
	return this->parentScene;
}

template<typename Base>
inline Port* Asset<Base>::getPort() const
{
	return this->port;
}

template<typename Base>
template<typename Derived>
inline Derived* Asset<Base>::as() const
{
	if (std::is_base_of<Base, Derived>::value)
	{
		return dynamic_cast<Derived*>(this->base);
	}

	return nullptr;
}

#pragma endregion GETTER(S)





#pragma region SETTER(S)

template<typename Base>
inline void Asset<Base>::setId(const std::string& id)
{
	this->id = id;
}

template<typename Base>
inline void Asset<Base>::setActive(bool active)
{
	this->active = active;
}

template<typename Base>
inline void Asset<Base>::setTimeScaled(bool timeScaled)
{
	this->timeScaled = timeScaled;
}

template<typename Base>
inline void Asset<Base>::setTimeScale(float timeScale)
{
	this->timeScale = timeScale;
}

template<typename Base>
inline void Asset<Base>::setParentScene(Scene* parentScene)
{
	this->parentScene = parentScene;
}

template<typename Base>
inline void Asset<Base>::setPort(Port& port)
{
	this->port = &port;
}

template<typename Base>
inline void Asset<Base>::setUpdate(std::function<void(float deltaTime)>&& functionUpdate)
{
	this->functionUpdate = std::move(functionUpdate);
}

#pragma endregion SETTER(S)