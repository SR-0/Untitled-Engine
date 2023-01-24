#include "Scene/Core/EngineModifier.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"





#pragma region CORE

void EngineModifier::initialize()
{
	#pragma region CREATE/REFERENCE

	///////////////////////////////////////////////////////////////
	// create/reference global system/engine window and managers //
	///////////////////////////////////////////////////////////////
	//////
	////
	//

	auto& window	= *global::getWindow();
	auto& cm		= *global::getClockManager();
	auto& em		= *global::getEventManager();
	auto& sm		= *global::getSceneManager();
	auto& am		= *global::getAssetManager();

	/////////////////////////////////////
	// create/reference window port(s) //
	/////////////////////////////////////
	//////
	////
	//
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineModifier();

	//////////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//

	this->rectangleModifierTab1			= am.createShape<Rectangle>("rectangleModifierTab1",			sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f), 0.0f),																								this, &*this->port); // font at index 0 is system regular
	this->rectangleModifierTab2			= am.createShape<Rectangle>("rectangleModifierTab2",			sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f), 0.0f),																								this, &*this->port); // font at index 0 is system regular
	this->rectangleModifierTab3			= am.createShape<Rectangle>("rectangleModifierTab3",			sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f), 0.0f),																								this, &*this->port); // font at index 0 is system regular
	this->rectangleModifierTabConnector = am.createShape<Rectangle>("rectangleModifierTabConnector",	sf::Vector2f(this->rectangleModifierTab1->getSize().x - 4, 4),																							sf::Vector2f(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2, this->rectangleModifierTab1->getPosition().y + this->rectangleModifierTab1->getSize().y - 2),	this, &*this->port); // font at index 0 is system regular

	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//
	
	this->textModifierTab1 = am.createText<Text>("textModifierTab1", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular
	this->textModifierTab2 = am.createText<Text>("textModifierTab2", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular
	this->textModifierTab3 = am.createText<Text>("textModifierTab3", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular

	#pragma endregion CREATE/REFERENCE
	




	#pragma region SETUP

	//////////
	// port //
	//////////
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

	// tab 1
	this->rectangleModifierTab1->setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTab1->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTab1->setOutlineThickness(-2);

	// tab 1 update functionality
	this->rectangleModifierTab1->setUpdate([&](float)
	{
		if (this->rectangleModifierTab1->isLeftClicked())
		{
			this->rectangleModifierTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
				this->rectangleModifierTab1->getPosition().y + this->rectangleModifierTab1->getSize().y - 2
			));

			this->modiferTab = ModifierTab::Tab1;
		}
	});

	// tab 2
	this->rectangleModifierTab2->setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTab2->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTab2->setOutlineThickness(-2);

	// tab 2 update functionality
	this->rectangleModifierTab2->setUpdate([&](float)
	{
		if (this->rectangleModifierTab2->isLeftClicked())
		{
			this->rectangleModifierTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
				this->rectangleModifierTab2->getPosition().y + this->rectangleModifierTab2->getSize().y - 2
			));

			this->modiferTab = ModifierTab::Tab2;
		}
	});

	// tab 3
	this->rectangleModifierTab3->setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTab3->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTab3->setOutlineThickness(-2);

	// tab 3 update functionality
	this->rectangleModifierTab3->setUpdate([&](float)
	{
		if (this->rectangleModifierTab3->isLeftClicked())
		{
			this->rectangleModifierTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
				this->rectangleModifierTab3->getPosition().y + this->rectangleModifierTab3->getSize().y - 2
			));

			this->modiferTab = ModifierTab::Tab3;
		}
	});

	// tab connector rectangle
	this->rectangleModifierTabConnector->setFillColor(sf::Color(35, 35, 35));

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	constexpr auto characterSizeDivider = 96.0f;

	this->textModifierTab1->setString("[ Tab 1 ]");
	this->textModifierTab1->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textModifierTab1->setPosition(this->rectangleModifierTab1->getPosition().x + ((this->rectangleModifierTab1->getSize().x - this->textModifierTab1->getGlobalBounds().width) / 2), this->rectangleModifierTab1->getPosition().y + ((this->rectangleModifierTab1->getSize().y - this->textModifierTab1->getGlobalBounds().height) / 2));
	this->textModifierTab1->setFillColor(sf::Color::White);
	this->textModifierTab1->setRenderLayer(1);

	this->textModifierTab2->setString("[ Tab 2 ]");
	this->textModifierTab2->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textModifierTab2->setPosition(this->rectangleModifierTab2->getPosition().x + ((this->rectangleModifierTab2->getSize().x - this->textModifierTab2->getGlobalBounds().width) / 2), this->rectangleModifierTab2->getPosition().y + ((this->rectangleModifierTab2->getSize().y - this->textModifierTab2->getGlobalBounds().height) / 2));
	this->textModifierTab2->setFillColor(sf::Color::White);
	this->textModifierTab2->setRenderLayer(1);

	this->textModifierTab3->setString("[ Tab 3 ]");
	this->textModifierTab3->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textModifierTab3->setPosition(this->rectangleModifierTab3->getPosition().x + ((this->rectangleModifierTab3->getSize().x - this->textModifierTab3->getGlobalBounds().width) / 2), this->rectangleModifierTab3->getPosition().y + ((this->rectangleModifierTab3->getSize().y - this->textModifierTab3->getGlobalBounds().height) / 2));
	this->textModifierTab3->setFillColor(sf::Color::White);
	this->textModifierTab3->setRenderLayer(1);

	#pragma endregion SETUP
}

void EngineModifier::update(float deltaTime)
{
	return;
}

void EngineModifier::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineModifier::getPort() const
{
	return this->port;
}

#pragma endregion GETTER(S)