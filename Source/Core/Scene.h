#pragma once

#include "Utility/Utility.h"
#include <functional>
#include <SFML/System/Vector2.hpp>
#include "Core/CodeUtilization.h"
#include "Core/Common.h"
#include "Core/Port.h"

class Scene // @TODO Scene class needs to have Scene parent and Scene children pointers and functionality
{
private: // data

	std::string					uuid					= utility::get_uuid();
	std::string					id						= std::string{};
	bool						active					= false;
	bool						focusRequired			= false;
	bool						mouseEnteredRequired	= false;
	SceneState					sceneState				= SceneState::Initialize;
	CodeUtilization				codeUtilization			= CodeUtilization::Combination;
	CodeUtilization				priorityCodeUtilization	= CodeUtilization::VirtualOverride;
	sf::Vector2f				position				= sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f				size					= sf::Vector2f(0.0f, 0.0f);
	std::size_t					renderLayer				= 0;
	bool						renderEnabled			= true;
	std::function<void()>		functionInitialize		= []{};
	std::function<void(float)>	functionUpdate			= [](float){};
	std::function<void()>		functionTerminate		= []{};

public: // ctor(s)/dtor(s)

	Scene();
	Scene(const std::string& id, bool active = false, const CodeUtilization& codeUtilization = CodeUtilization::Combination);
	virtual ~Scene() = default;

public: // core

	virtual void initialize();				// only used with code utilization of "VirtualOverride/Combination"
	virtual void update(float deltaTime);	// only used with code utilization of "VirtualOverride/Combination"
	virtual void terminate();				// only used with code utilization of "VirtualOverride/Combination"

private: // core

	void callInitialize();
	void callUpdate(float deltaTime);
	void callTerminate();

public: // getter(s)

	const std::string&		getUuid() const;
	const std::string&		getId() const;
	bool					isActive() const;
	bool					isFocusRequired() const;
	bool					isMouseEnteredRequired() const;
	const SceneState&		getSceneState() const;
	const CodeUtilization&	getCodeUtilization() const;
	const CodeUtilization&	getPriorityCodeUtilization() const;
	const sf::Vector2f&		getPosition() const;
	std::size_t				getRenderLayer() const;
	bool					isRenderEnabled() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setFocusRequired(bool focusRequired); // @TODO make global/window *as well as* local port focus check
	void setMouseEnteredRequired(bool mouseEnteredRequired); // @TODO make global/window *as well as* local port focus check
	void setSceneState(const SceneState& sceneState);
	void setCodeUtilization(const CodeUtilization& codeUtilization);
	void setPriorityCodeUtilization(const CodeUtilization& priorityCodeUtilization);
	void setInitialize(std::function<void()>&& functionInitialize); // only used with code utilization of "DynamicFunction/Combination"
	void setUpdate(std::function<void(float deltaTime)>&& functionUpdate); // only used with code utilization of "DynamicFunction/Combination"
	void setTerminate(std::function<void()>&& functionTerminate); // only used with code utilization of "DynamicFunction/Combination"
	void setPosition(const sf::Vector2f& position);
	void setRenderLayer(std::size_t renderLayer);
	void setRenderEnabled(bool renderEnabled);

public: // utility

	template <typename Derived> Derived* as() const;

private: // friend(s)

	friend class SceneManager;

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