#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include <vector>
#include <functional>
#include "Utility/Utility.h"
#include "Core/CodeUtilization.h"

class Binding
{
private: // data
	
	std::string					uuid					= utility::get_uuid();
	std::string					id						= "unidentified";
	std::vector<int>			types					= {};
	std::vector<int>			keys					= {};
	std::vector<int>			buttons					= {};
	std::vector<int>			modifiers				= {};
	float						mouseScrollDelta		= 0;
	sf::Vector2i				mouseScroll				= {};
	sf::Vector2i				mousePosition			= {};
	sf::Uint32					unicode					= 0;
	bool						active					= false;
	CodeUtilization				codeUtilization			= CodeUtilization::Combination;
	CodeUtilization				priorityCodeUtilization	= CodeUtilization::VirtualOverride;
	bool						focusRequired			= false;
	bool						mouseEnteredRequired	= false;
	class Scene*				parentScene				= nullptr;
	std::function<void(float)>	functionUpdate			= [](float){};

public: // ctor(s)/dtor(s)

	Binding();

	Binding
	(
		const std::string&				id,
		const std::vector<int>&			types,
		bool							active			= false,
		class Scene*					parentScene		= nullptr,
		std::function<void(float)>&&	functionUpdate	= [](float){}
	);

	Binding
	(
		const std::string&				id,
		const std::vector<int>&			types,
		const std::vector<int>&			keys,
		const std::vector<int>&			buttons,
		const std::vector<int>&			modifiers,
		bool							active			= false,
		class Scene*					parentScene		= nullptr,
		std::function<void(float)>&&	functionUpdate	= [](float){}
	);

	virtual ~Binding();

public: // operator overloading

	friend bool operator == (const Binding& first, const Binding& second);
	friend bool operator != (const Binding& first, const Binding& second);

public:

	virtual void update(float deltaTime);

public: // core

	void callUpdate(float deltaTime);

public: // getter(s)

	float					getMouseScrollDelta() const;
	sf::Vector2i			getMouseScroll() const;
	sf::Vector2i			getMousePosition() const;
	std::string				getUuid() const;
	std::string				getId() const;
	std::vector<int>&		getTypes();
	std::vector<int>&		getKeys();
	std::vector<int>&		getButtons();
	std::vector<int>&		getModifiers();
	sf::Uint32				getUnicode() const;
	bool					isActive() const;
	const CodeUtilization&	getCodeUtilization() const;
	const CodeUtilization&	getPriorityCodeUtilization() const;
	bool					isFocusRequired() const;
	bool					isMouseEnteredRequired() const;
	class Scene*			getParentScene() const;

private: // setter(s) (for use in EventManager only)

	void setMouseScrollDelta(float mouseScrollDelta);
	void setMouseScroll(const sf::Vector2i& mouseScroll);
	void setMousePosition(const sf::Vector2i& mousePosition);
	void setUnicode(const sf::Uint32& unicode);

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setCodeUtilization(const CodeUtilization& codeUtilization);
	void setPriorityCodeUtilization(const CodeUtilization& priorityCodeUtilization);
	void setFocusRequired(bool focusRequired); // @TODO make global/window *as well as* local port focus check
	void setMouseEnteredRequired(bool mouseEnteredRequired); // @TODO make global/window *as well as* local port focus check
	void setUpdate(std::function<void(float deltaTime)>&& functionUpdate);
	void setParentScene(class Scene* parentScene);

	void set
	(
		const std::string&				id,
		const std::vector<int>&			types,
		bool							active		= false,
		class Scene*					parentScene = nullptr,
		std::function<void(float)>&&	function	= [](float){}
	);

	void set
	(
		const std::string&				id,
		const std::vector<int>&			types,
		const std::vector<int>&			keys,
		const std::vector<int>&			buttons,
		const std::vector<int>&			modifiers,
		bool							active		= false,
		class Scene*					parentScene = nullptr,
		std::function<void(float)>&&	function	= [](float){}
	);

public: // utility

	template <typename Derived> Derived* as() const;

private: // friend(s)

	friend class EventManager;

};

template<typename Derived>
inline Derived* Binding::as() const
{
	if (std::is_base_of<Binding, Derived>::value)
	{
		return dynamic_cast<Derived*>(const_cast<Binding*>(this));
	}

	return nullptr;
}