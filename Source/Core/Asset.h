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
#include "Utility/Utility.h"
#include "Utility/Debug.h"
#include "Core/Scene.h"
#include "Core/Port.h"
#include "Core/CodeUtilization.h"

#pragma endregion INCLUDE(S)





#pragma region INTERFACE

template <typename Base>
class Asset
{
private: // data

	std::string                 uuid                    = utility::get_uuid();
	std::string                 id                      = std::string{};
	bool                        active                  = false;
	CodeUtilization             codeUtilization         = CodeUtilization::Combination;
	CodeUtilization             priorityCodeUtilization = CodeUtilization::VirtualOverride;
	Base*                       base                    = nullptr;
	Scene*                      parentScene             = nullptr;
	Port*                       port                    = nullptr;
	std::function<void(float)>  functionUpdate          = [](float){};

public: // ctor(s)/dtor(s)

	Asset(Base& base, Scene* parentScene = nullptr);
	Asset(Base& base, const std::string& id, Scene* parentScene = nullptr);

public:

	virtual void update(float deltaTime);

protected: // core

	void callUpdate(float deltaTime); // meant to be used with AssetManager

public: // getter(s)

	const std::string&                      getUuid() const;
	const std::string&                      getId() const;
	bool                                    isActive() const;
	const CodeUtilization&                  getCodeUtilization() const;
	const CodeUtilization&                  getPriorityCodeUtilization() const;
	Scene*                                  getParentScene() const;
	Port*                                   getPort() const;
	template <typename Derived> Derived*    as() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setCodeUtilization(const CodeUtilization& codeUtilization);
	void setPriorityCodeUtilization(const CodeUtilization& priorityCodeUtilization);
	void setParentScene(Scene* parentScene);
	void setPort(Port* port);
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
	this->base          = &base;
	this->parentScene   = parentScene;
}

template<typename Base>
inline Asset<Base>::Asset(Base& base, const std::string& id, Scene* parentScene)
{
	this->base          = &base;
	this->id            = id;
	this->parentScene   = parentScene;
}

template<typename Base>
inline void Asset<Base>::update(float deltaTime)
{
	return;
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

template<typename Base>
inline void Asset<Base>::callUpdate(float deltaTime)
{
	switch (this->codeUtilization)
	{
		case CodeUtilization::DynamicFunction:
		{
			this->functionUpdate(deltaTime);
		}
		break;

		case CodeUtilization::VirtualOverride:
		{
			this->update(deltaTime);
		}
		break;

		case CodeUtilization::Combination:
		{
			switch (this->priorityCodeUtilization)
			{
				case CodeUtilization::DynamicFunction:
				{
					this->functionUpdate(deltaTime);
					this->update(deltaTime);
				}
				break;

				case CodeUtilization::VirtualOverride:
				{
					this->update(deltaTime);
					this->functionUpdate(deltaTime);
				}
				break;
			}
		}
		break;
	}
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
inline const CodeUtilization& Asset<Base>::getCodeUtilization() const
{
	return this->codeUtilization;
}

template<typename Base>
inline const CodeUtilization& Asset<Base>::getPriorityCodeUtilization() const
{
	return this->priorityCodeUtilization;
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
inline void Asset<Base>::setCodeUtilization(const CodeUtilization& codeUtilization)
{
	this->codeUtilization = codeUtilization;
}

template<typename Base>
inline void Asset<Base>::setPriorityCodeUtilization(const CodeUtilization& priorityCodeUtilization)
{
	if (priorityCodeUtilization == Scene::CodeUtilization::Combination)
	{
		this->priorityCodeUtilization = Scene::CodeUtilization::DynamicFunction; // default on "Combination" value attempt

		debug::print
		(
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
			"#\n"
			"#   [ WARNING ]\n"
			"#\n"
			"#   priority scene code utilization must a be value of either\n"
			"#   \"CodeUtilization::DynamicFunction\" or\n"
			"#   \"CodeUtilization::VirtualOverride\" - the value of\n"
			"#   \"CodeUtilization::Combination\" is not accepted as\n"
			"#   a priority code utilization - defaulted to value of\n"
			"#   \"CodeUtilization::DynamicFunction\" - in which case\n"
			"#   virutally overridden functions will automatically be called\n"
			"#   before dynamically set functions of Asset<Base> class instance\n"
			"#   \"", this->getId(), "\"\n"
			"#\n"
			"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n"
		);

		return;
	}

	this->priorityCodeUtilization = priorityCodeUtilization;
}

template<typename Base>
inline void Asset<Base>::setParentScene(Scene* parentScene)
{
	this->parentScene = parentScene;
}

template<typename Base>
inline void Asset<Base>::setPort(Port* port)
{
	this->port = port;
}

template<typename Base>
inline void Asset<Base>::setUpdate(std::function<void(float deltaTime)>&& functionUpdate)
{
	this->functionUpdate = std::move(functionUpdate);
}

#pragma endregion SETTER(S)