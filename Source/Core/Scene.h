#pragma once

#include "Utility/Utility.h"
#include <functional>
#include <SFML/System/Vector2.hpp>

class Scene // @TODO Scene class needs to have Scene parent and Scene children pointers and functionality
{
public: // enum class(es)

	enum class State
	{
		Initialize,
		Update,
		Terminate,
	};

private: // data

	std::string					uuid					= utility::get_uuid();
	std::string					id						= std::string{};
	bool						active					= false;
	bool						focusRequired			= false;
	bool						mouseEnteredRequired	= false;
	Scene::State				state					= Scene::State::Initialize;
	sf::Vector2f				position				= sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f				size					= sf::Vector2f(0.0f, 0.0f);
	std::size_t					renderLayer				= 0;
	bool						renderEnabled			= true;
	std::function<void()>		functionInitialize		= []{};
	std::function<void(float)>	functionUpdate			= [](float){};
	std::function<void()>		functionTerminate		= []{};

public: // ctor(s)/dtor(s)

	Scene();
	Scene(const std::string& id, bool active = false);
	virtual ~Scene() = default;

public: // core

	void initialize();
	void update(float deltaTime);
	void terminate();

public: // getter(s)

	const std::string&	getUuid() const;
	const std::string&	getId() const;
	bool				isActive() const;
	bool				isFocusRequired() const;
	bool				isMouseEnteredRequired() const;
	const Scene::State& getState() const;
	const sf::Vector2f& getPosition() const;
	std::size_t			getRenderLayer() const;
	bool				isRenderEnabled() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setFocusRequired(bool focusRequired); // @TODO make global/window *as well as* local port focus check
	void setMouseEnteredRequired(bool mouseEnteredRequired); // @TODO make global/window *as well as* local port focus check
	void setState(const Scene::State& state);
	void setInitialize(std::function<void()>&& functionInitialize);
	void setUpdate(std::function<void(float deltaTime)>&& functionUpdate);
	void setTerminate(std::function<void()>&& functionTerminate);
	void setPosition(const sf::Vector2f& position);
	void setRenderLayer(std::size_t renderLayer);
	void setRenderEnabled(bool renderEnabled);

public:

	template <typename Derived> Derived* as() const;

};

template<typename Derived>
inline Derived* Scene::as() const
{
	if (std::is_base_of<Scene, Derived>::value)
	{
		return dynamic_cast<Derived*>(const_cast<Scene*>(this));
	}

	return nullptr;
}