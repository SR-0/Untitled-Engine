#include "Core/Binding.h"
#include "Core/Scene.h"
#include "Core/Global.h"

Binding::Binding()
{
	//
}

Binding::Binding(
	const std::string&				id,
	const std::vector<int>&			types,
	bool							active,
	Scene*							parentScene,
	std::function<void(float)>&&	function)
{
	this->set
	(
		id,
		types,
		active,
		parentScene,
		std::move(function)
	);
}

Binding::Binding(
	const std::string&				id,
	const std::vector<int>&			types,
	const std::vector<int>&			keys,
	const std::vector<int>&			buttons,
	const std::vector<int>&			modifiers,
	bool							active,
	Scene*							parentScene,
	std::function<void(float)>&&	function)
{
	this->set
	(
		id,
		types,
		keys,
		buttons,
		modifiers,
		active,
		parentScene,
		std::move(function)
	);
}

bool operator == (const Binding& first, const Binding& second)
{
	return bool
	(
		first.types		== second.types		&&
		first.keys		== second.keys		&&
		first.buttons	== second.buttons	&&
		first.modifiers == second.modifiers
	);
}

bool operator != (const Binding& first, const Binding& second)
{
	return !(first == second);
}

void Binding::call()
{
	this->function(global::getClockManager()->getDeltaTime().asSeconds());
}

sf::Vector2i Binding::getMouseScroll() const
{
	return this->mouseScroll;
}

sf::Vector2i Binding::getMousePosition() const
{
	return this->mousePosition;
}

float Binding::getMouseScrollDelta() const
{
	return this->mouseScrollDelta;
}

std::string Binding::getUuid() const
{
	return this->uuid;
}

std::string Binding::getId() const
{
	return this->id;
}

std::vector<int>& Binding::getTypes()
{
	return this->types;
}

std::vector<int>& Binding::getKeys()
{
	return this->keys;
}

std::vector<int>& Binding::getButtons()
{
	return this->buttons;
}

std::vector<int>& Binding::getModifiers()
{
	return this->modifiers;
}

sf::Uint32 Binding::getUnicode() const
{
	return this->unicode;
}

bool Binding::isActive() const
{
	return this->active && (static_cast<bool>(this->getParentScene()) ? this->getParentScene()->isActive() : true);
}

Scene* Binding::getParentScene() const
{
	return this->parentScene;
}

void Binding::setMouseScrollDelta(float mouseScrollDelta)
{
	this->mouseScrollDelta = mouseScrollDelta;
}

void Binding::setMouseScroll(const sf::Vector2i& mouseScroll)
{
	this->mouseScroll = mouseScroll;
}

void Binding::setMousePosition(const sf::Vector2i& mousePosition)
{
	this->mousePosition = mousePosition;
}

void Binding::setUnicode(const sf::Uint32& unicode)
{
	this->unicode = unicode;
}

void Binding::setId(const std::string& id)
{
	this->id = id;
}

void Binding::setActive()
{
	this->active = active;
}

void Binding::setFunction(std::function<void(float)>&& function)
{
	this->function = std::move(function);
}

void Binding::setParentScene(Scene* parentScene)
{
	this->parentScene = parentScene;
}

void Binding::set(
	const std::string&				id,
	const std::vector<int>&			types,
	bool							active,
	Scene*							parentScene,
	std::function<void(float)>&&	function)
{
	this->id			= id;
	this->types			= types;
	this->active		= active;
	this->parentScene	= parentScene;
	this->function		= std::move(function);
}

void Binding::set(
	const std::string&				id,
	const std::vector<int>&			types,
	const std::vector<int>&			keys,
	const std::vector<int>&			buttons,
	const std::vector<int>&			modifiers,
	bool							active,
	Scene*							parentScene,
	std::function<void(float)>&&	function)
{
	this->id			= id;
	this->types			= types;
	this->keys			= keys;
	this->buttons		= buttons;
	this->modifiers		= modifiers;
	this->active		= active;
	this->parentScene	= parentScene;
	this->function		= std::move(function);
}
