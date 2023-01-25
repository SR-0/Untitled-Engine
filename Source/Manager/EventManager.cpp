#include "Manager/EventManager.h"
#include "Core/Global.h"
#include "Core/Scene.h"





#pragma region CTOR(S)/DTOR(S)

EventManager::~EventManager()
{
	this->removeBindings();
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void EventManager::update(float deltaTime)
{
	auto&   window  = *global::getWindow();
	auto    event   = sf::Event{};
	auto    local   = Binding{};

	while (window.pollEvent(event))

	{
		///////////////////////////////////
		// poll types, keys, and buttons //
		///////////////////////////////////
		//////
		////
		//

		switch (event.type)
		{
			case sf::Event::Closed:
			{
				local.getTypes().push_back(sf::Event::Closed);
			}
			break;

			case sf::Event::Resized: // @TODO resize with scaling
			{
				//window.resizePorts();
			}
			break;

			case sf::Event::GainedFocus:
			{
				window.setFocused(true);

				#ifndef NDEBUG
				if (debug::isReportingEventFocus())
					debug::print("focus gained\n");
				#endif//NDEBUG
			}
			break;

			case sf::Event::LostFocus:
			{
				window.setFocused(false);

				#ifndef NDEBUG
				if (debug::isReportingEventFocus())
					debug::print("focus lost\n");
				#endif//NDEBUG
			}
			break;

			case sf::Event::MouseEntered:
			{
				window.setMouseEntered(true);

				#ifndef NDEBUG
				if (debug::isReportingEventMouseEntered())
					debug::print("mouse entered window\n");
				#endif//NDEBUG
			}
			break;

			case sf::Event::MouseLeft:
			{
				window.setMouseEntered(false);

				#ifndef NDEBUG
				if (debug::isReportingEventMouseEntered())
					debug::print("mouse left window\n");
				#endif//NDEBUG
			}
			break;
			
			case sf::Event::KeyPressed:
			{
				if (!this->isKeyPressInhibited() && !this->isTextInputEnabled())
				{
					local.getTypes().push_back(sf::Event::KeyPressed);
					local.getKeys().push_back(event.key.code);
				}
			}
			break;
			
			case sf::Event::KeyReleased:
			{
				if (this->isAutoUninhibited())
					this->setKeyPressInhibited(false);
				local.getTypes().push_back(sf::Event::KeyReleased);
				local.getKeys().push_back(event.key.code);
			}
			break;

			case sf::Event::TextEntered:
			{
				if (!this->isKeyPressInhibited() && this->isTextInputEnabled())
				{
					local.getTypes().push_back(sf::Event::TextEntered);
					local.setUnicode(event.text.unicode);
				}
			}
			break;
			
			case sf::Event::MouseButtonPressed:
			{
				if (!this->isMousePressInhibited())
				{
					local.getTypes().push_back(sf::Event::MouseButtonPressed);
					local.getButtons().push_back(event.mouseButton.button);
				}
			}
			break;
			
			case sf::Event::MouseButtonReleased:
			{
				if (this->isAutoUninhibited())
					this->setMousePressInhibited(false);
				local.getTypes().push_back(sf::Event::MouseButtonReleased);
				local.getButtons().push_back(event.mouseButton.button);
			}
			break;

			case sf::Event::MouseWheelScrolled:
			{
				if (!this->isMouseWheelScrollInhibited())
				{
					local.getTypes().push_back(sf::Event::MouseWheelScrolled);
					local.setMouseScrollDelta(event.mouseWheelScroll.delta);
					local.setMouseScroll(sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
					local.setMousePosition(sf::Mouse::getPosition(*window.getInstance()));
				}
			}
			break;
		}
	}

	///////////////////////////////////////
	// auto uninhibit mouse wheel scroll // (@TODO untested)
	///////////////////////////////////////
	//////
	////
	//

	if (this->isAutoUninhibited() && this->isMouseWheelScrollInhibited() &&
			!std::count(local.getTypes().begin(), local.getTypes().end(), sf::Event::MouseWheelScrolled))
	{
		this->setMouseWheelScrollInhibited(false);
	}

	/////////////////////////
	// check for modifiers // not all conventional modifiers @TODO fix soon
	/////////////////////////
	//////
	////
	//

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !this->isTextInputEnabled())
		local.getModifiers().push_back(sf::Keyboard::LShift);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		local.getModifiers().push_back(sf::Keyboard::LControl);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		local.getModifiers().push_back(sf::Keyboard::LAlt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && !this->isTextInputEnabled())
		local.getModifiers().push_back(sf::Keyboard::RShift);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		local.getModifiers().push_back(sf::Keyboard::RControl);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
		local.getModifiers().push_back(sf::Keyboard::RAlt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		local.getModifiers().push_back(sf::Keyboard::Backspace);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		local.getModifiers().push_back(sf::Keyboard::Enter);

	///////////////////////////////////////////////////
	// call matching Binding object functions if any //
	///////////////////////////////////////////////////
	//////
	////
	//

	for (auto& binding : this->bindings)
	{
		if (binding->isActive() && (*binding == local))
		{
			for (auto& type : binding->getTypes())
			{
				if (type == sf::Event::MouseWheelScrolled)
				{
					binding->setMouseScrollDelta(local.getMouseScrollDelta());
					binding->setMouseScroll(local.getMouseScroll());
					binding->setMousePosition(local.getMousePosition());
					break;
				}

				if (type == sf::Event::TextEntered)
				{
					binding->setUnicode(local.getUnicode());
					break;
				}
			}

			binding->callUpdate(deltaTime);
		}
	}
}

#pragma endregion CORE





#pragma region BINDINGS

std::size_t EventManager::getBindingCount() const
{
	return this->bindings.size();
}

Binding* EventManager::getBinding(std::size_t index)
{
	return this->bindings[index].get();
}

Binding* EventManager::getBinding(const std::string& id)
{
	for (std::size_t index = 0; index < this->bindings.size(); index++)
	{
		if (this->bindings[index]->getId() == id)
		{
			return this->bindings[index].get();
		}
	}

	return nullptr;
}

Binding* EventManager::getBindingFront()
{
	return this->bindings.front().get();
}

Binding* EventManager::getBindingBack()
{
	return this->bindings.back().get();
}

std::vector<std::shared_ptr<Binding>>& EventManager::getBindingData()
{
	return this->bindings;
}

void EventManager::removeBinding(std::size_t index)
{
	this->bindings.erase(this->bindings.begin() + index);
}

void EventManager::removeBinding(const std::string& id)
{
	for (std::size_t index = 0; index < this->bindings.size(); index++)
	{
		if (this->bindings[index]->getId() == id)
		{
			this->bindings.erase(this->bindings.begin() + index);
			index--;
		}
	}
}

void EventManager::removeBindings(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->bindings.size(); index++)
		{
			if (static_cast<bool>(this->bindings[index]->getParentScene())			&&
				static_cast<bool>(this->bindings[index]->getParentScene() == scene)	)
			{
				this->bindings.erase(this->bindings.begin() + index);
				index--;
			}
		}

		return;
	}

	this->bindings.clear();
}

void EventManager::iterateBindings(const std::function<void(Binding&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->bindings.rbegin(); iter != this->bindings.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->bindings.begin(); iter != this->bindings.end(); iter++)
		return function(*iter->get());
}

#pragma endregion BINDINGS





#pragma region GETTER(S)

sf::Vector2i EventManager::getLocalMousePosition() const
{
	return sf::Mouse::getPosition(*global::getWindow()->getInstance());
}

sf::Vector2i EventManager::getGlobalMousePosition() const
{
	return sf::Mouse::getPosition();
}

bool EventManager::isKeyPressInhibited() const
{
	return this->keyPressInhibited;
}

bool EventManager::isMousePressInhibited() const
{
	return this->mousePressInhibited;
}

bool EventManager::isMouseWheelScrollInhibited() const
{
	return this->mouseWheelScrollInhibited;
}

bool EventManager::isAutoUninhibited() const
{
	return this->autoUninhibited;
}

bool EventManager::isTextInputEnabled() const
{
	return this->textInputEnabled;
}

#pragma endregion GETTER(S)





#pragma region SETTER(S)

void EventManager::setKeyPressInhibited(bool keyPressInhibited)
{
	this->keyPressInhibited = keyPressInhibited;
}

void EventManager::setMousePressInhibited(bool mousePressInhibited)
{
	this->mousePressInhibited = mousePressInhibited;
}

void EventManager::setMouseWheelScrollInhibited(bool mouseWheelScrollInhibited)
{
	this->mouseWheelScrollInhibited = mouseWheelScrollInhibited;
}

void EventManager::setAutoUninhibited(bool autoUninhibited)
{
	this->autoUninhibited = autoUninhibited;
}

void EventManager::setTextInputEnabled(bool textInputEnabled)
{
	this->textInputEnabled = textInputEnabled;
}

#pragma endregion SETTER(S)