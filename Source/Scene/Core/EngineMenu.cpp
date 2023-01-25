#include "Scene/Core/EngineMenu.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"





#pragma region CORE

void EngineMenu::initialize()
{
	#pragma region CREATE/REFERENCE

	///////////////////////////////////////////////////////////////
	// create/reference global system/engine window and managers //
	///////////////////////////////////////////////////////////////
	//////
	////
	//

	auto& window    = *global::getWindow();
	auto& cm        = *global::getClockManager();
	auto& em        = *global::getEventManager();
	auto& sm        = *global::getSceneManager();
	auto& am        = *global::getAssetManager();

	/////////////////////////////////////
	// create/reference window port(s) //
	/////////////////////////////////////
	//////
	////
	//
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineMenu();

	///////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//
	
	this->rectangleMenuClose = am.createShape<Rectangle>("rectangleMenuClose", sf::Vector2f(window.getHeight() * port->getViewport().height * 0.65f, window.getHeight() * port->getViewport().height * 0.65f), sf::Vector2f(0, 0), this, &*this->port);
	
	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//

	this->textMenuClose = am.createText<Text>("textMenuClose", &*am.getFont(0), this, &*this->port); // font at index 2 is system bold

	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	// scene
	//this->setFocusRequired(true);
	this->setCodeUtilization(CodeUtilization::VirtualOverride);

	/////////////
	// port(s) //
	/////////////
	//////
	////
	//

	this->port->getBackground()->setFillColor(sf::Color(35, 35, 35));
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));

	//////////////
	// shape(s) //
	//////////////
	//////
	////
	//

	// menu close
	this->rectangleMenuClose->setPosition(window.getSize().x - this->rectangleMenuClose->getSize().x - (((window.getSize().y * port->getViewport().height) - this->rectangleMenuClose->getSize().y) / 2), ((window.getSize().y * port->getViewport().height) - this->rectangleMenuClose->getSize().y) / 2);
	this->rectangleMenuClose->setRenderLayer(1);

	// menu close update functionality
	this->rectangleMenuClose->setUpdate([&](float)
	{
		if (this->rectangleMenuClose->isLeftClicked())
		{
			window.close();
		}
		else if (this->rectangleMenuClose->isHoveredOver())
		{
			this->rectangleMenuClose->setFillColor(sf::Color(55, 55, 55));
		}
		else if (this->rectangleMenuClose->getFillColor() != sf::Color(35, 35, 35))
		{
			this->rectangleMenuClose->setFillColor(sf::Color(35, 35, 35));
		}
	});

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	// move window
	this->port->getBackground()->setUpdate([&](float)
	{
		static bool         started     = false;
		static bool         set         = false;
		static sf::Vector2i previous    = sf::Vector2i(0, 0);

		if (this->port->getBackground()->isLeftClicked())
			started = true;
		
		if (started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!set)
			{
				previous = sf::Mouse::getPosition();
				set = true;
				return;
			}

			window.setPosition(window.getPosition().x + (sf::Mouse::getPosition().x - previous.x), window.getPosition().y + (sf::Mouse::getPosition().y - previous.y));
			previous = sf::Mouse::getPosition();
			return;
		}

		started	= false;
		set		= false;
	});

	// menu close
	this->textMenuClose->setString("X");
	this->textMenuClose->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textMenuClose->setFillColor(sf::Color::White);
	this->textMenuClose->setPosition(rectangleMenuClose->getPosition().x + ((rectangleMenuClose->getSize().x  - this->textMenuClose->getGlobalBounds().width) / 2), this->rectangleMenuClose->getPosition().y - rectangleMenuClose->getOrigin().y + ((this->rectangleMenuClose->getSize().y - this->textMenuClose->getGlobalBounds().height) / 2) - (this->textMenuClose->getGlobalBounds().height / 8));
	this->textMenuClose->setRenderLayer(1);

	#pragma endregion SETUP
}

void EngineMenu::update(float deltaTime)
{
	return;
}

void EngineMenu::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineMenu::getPort() const
{
	return this->port;
}

#pragma endregion GETTER(S)