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

	auto& window    = *global::getWindow();
	auto& clocks    = *global::getClockManager();
	auto& events    = *global::getEventManager();
	auto& scenes    = *global::getSceneManager();
	auto& assets    = *global::getAssetManager();
	auto& scripts   = *global::getAssetManager();

	/////////////////////////////////////
	// create/reference window port(s) //
	/////////////////////////////////////
	//////
	////
	//
	
	this->port = scenes.getScene(0)->as<EngineSystem>()->getPortEngineModifier();

	//////////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//

	this->rectangleModifierTab1         = assets.createShape<Rectangle>("rectangleModifierTab1");
	this->rectangleModifierTab2         = assets.createShape<Rectangle>("rectangleModifierTab2");
	this->rectangleModifierTab3         = assets.createShape<Rectangle>("rectangleModifierTab3");
	this->rectangleModifierTabConnector = assets.createShape<Rectangle>("rectangleModifierTabConnector");
	this->rectangleModifierHighlighter  = assets.createShape<Rectangle>("rectangleModifierHighlighter");

	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//
	
	this->textModifierTab1 = assets.createText<Text>("textModifierTab1"); // font at index 0 is system regular
	this->textModifierTab2 = assets.createText<Text>("textModifierTab2"); // font at index 0 is system regular
	this->textModifierTab3 = assets.createText<Text>("textModifierTab3"); // font at index 0 is system regular

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

	// rectangle size(s)
	this->rectangleModifierTab1->           setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f));
	this->rectangleModifierTab2->           setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f));
	this->rectangleModifierTab3->           setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f));
	this->rectangleModifierTabConnector->   setSize(this->rectangleModifierTab1->getSize().x - 4,                                        4);
	this->rectangleModifierHighlighter->    setSize(0.f, 0.f);
	
	// rectangle position(s)
	this->rectangleModifierTab1->           setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f),       0.0f);
	this->rectangleModifierTab2->           setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f),       0.0f);
	this->rectangleModifierTab3->           setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f),       0.0f);
	this->rectangleModifierTabConnector->   setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,   this->rectangleModifierTab1->getPosition().y + this->rectangleModifierTab1->getSize().y - 2);
	this->rectangleModifierHighlighter->    setPosition(0.f, 0.f);
	
	// rectangle position(s)
	this->rectangleModifierTab1->           setParentScene(this);
	this->rectangleModifierTab2->           setParentScene(this);
	this->rectangleModifierTab3->           setParentScene(this);
	this->rectangleModifierTabConnector->   setParentScene(this);
	this->rectangleModifierHighlighter->    setParentScene(this);

	// rectangle position(s)
	this->rectangleModifierTab1->           setPort(this->port);
	this->rectangleModifierTab2->           setPort(this->port);
	this->rectangleModifierTab3->           setPort(this->port);
	this->rectangleModifierTabConnector->   setPort(this->port);
	this->rectangleModifierHighlighter->    setPort(this->port);

	// rectangle position(s)
	this->rectangleModifierTab1->           setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTab2->           setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTab3->           setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierTabConnector->   setFillColor(sf::Color(35, 35, 35));
	this->rectangleModifierHighlighter->    setFillColor(sf::Color(35, 35, 35));

	// rectangle position(s)
	this->rectangleModifierTab1->           setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTab2->           setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTab3->           setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleModifierTabConnector->   setOutlineColor(rectangleModifierTabConnector->getFillColor());
	this->rectangleModifierHighlighter->    setOutlineColor(rectangleModifierHighlighter->getFillColor());

	// rectangle position(s)
	this->rectangleModifierTab1->           setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleModifierTab2->           setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleModifierTab3->           setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleModifierTabConnector->   setOutlineThickness(0);
	this->rectangleModifierHighlighter->    setOutlineThickness(0);

	// rectangle position(s)
	this->rectangleModifierTab1->           setRenderLayer(1);
	this->rectangleModifierTab2->           setRenderLayer(1);
	this->rectangleModifierTab3->           setRenderLayer(1);
	this->rectangleModifierTabConnector->   setRenderLayer(1);
	this->rectangleModifierHighlighter->    setRenderLayer(1);

	/*
		it's usually a good idea to leave render
		layer 0 for system/window/port backgrounds
		- (might restrict 0 in future)
	*/

	// rectangle position(s)
	this->rectangleModifierTab1->           setRenderEnabled(true);
	this->rectangleModifierTab2->           setRenderEnabled(true);
	this->rectangleModifierTab3->           setRenderEnabled(true);
	this->rectangleModifierTabConnector->   setRenderEnabled(true);
	this->rectangleModifierHighlighter->    setRenderEnabled(false);

	// rectangle position(s)
	this->rectangleModifierTab1->           setActive(false);
	this->rectangleModifierTab2->           setActive(false);
	this->rectangleModifierTab3->           setActive(false);
	this->rectangleModifierTabConnector->   setActive(false);
	this->rectangleModifierHighlighter->    setActive(false);

	/*
		set true if you want to utilize automated
		lambda/std::function-based funtionality
		- (needs to be set via "setUpdate")
	*/

	//// tab 1
	//this->rectangleModifierTab1->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleModifierTab1->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleModifierTab1->setOutlineThickness(-2);
	//
	//// tab 1 update functionality
	//this->rectangleModifierTab1->setUpdate([&](float)
	//{
	//	if (this->rectangleModifierTab1->isLeftClicked())
	//	{
	//		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
	//			this->rectangleModifierTab1->getPosition().y + this->rectangleModifierTab1->getSize().y - 2
	//		));
	//
	//		this->modiferTab = ModifierTab::Tab1;
	//	}
	//});
	//
	//// tab 2
	//this->rectangleModifierTab2->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleModifierTab2->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleModifierTab2->setOutlineThickness(-2);
	//
	//// tab 2 update functionality
	//this->rectangleModifierTab2->setUpdate([&](float)
	//{
	//	if (this->rectangleModifierTab2->isLeftClicked())
	//	{
	//		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
	//			this->rectangleModifierTab2->getPosition().y + this->rectangleModifierTab2->getSize().y - 2
	//		));
	//
	//		this->modiferTab = ModifierTab::Tab2;
	//	}
	//});
	//
	//// tab 3
	//this->rectangleModifierTab3->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleModifierTab3->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleModifierTab3->setOutlineThickness(-2);
	//
	//// tab 3 update functionality
	//this->rectangleModifierTab3->setUpdate([&](float)
	//{
	//	if (this->rectangleModifierTab3->isLeftClicked())
	//	{
	//		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
	//			this->rectangleModifierTab3->getPosition().y + this->rectangleModifierTab3->getSize().y - 2
	//		));
	//
	//		this->modiferTab = ModifierTab::Tab3;
	//	}
	//});
	//
	//// tab connector rectangle
	//this->rectangleModifierTabConnector->setFillColor(sf::Color(35, 35, 35));

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	// text fonts(s)
	this->textModifierTab1->setFont(*assets.getFont(0)); // font at index 0 is system regular
	this->textModifierTab2->setFont(*assets.getFont(0)); // font at index 0 is system regular
	this->textModifierTab3->setFont(*assets.getFont(0)); // font at index 0 is system regular

	// text parent scene(s)
	this->textModifierTab1->setParentScene(this);
	this->textModifierTab2->setParentScene(this);
	this->textModifierTab3->setParentScene(this);

	// text attached port(s) @TODO let assets have multiple port attachments
	this->textModifierTab1->setPort(this->port);
	this->textModifierTab2->setPort(this->port);
	this->textModifierTab3->setPort(this->port);

	// test string(s)
	this->textModifierTab1->setString("[ Tab 1 ]");
	this->textModifierTab2->setString("[ Tab 2 ]");
	this->textModifierTab3->setString("[ Tab 3 ]");
	
	// test character size(s)
	this->textModifierTab1->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textModifierTab2->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textModifierTab3->setCharacterSize(global::getFontSize() * global::getUiScale());
	
	// text position(s)
	this->textModifierTab1->setPosition(this->rectangleModifierTab1->getPosition().x + ((this->rectangleModifierTab1->getSize().x - this->textModifierTab1->getGlobalBounds().width) / 2), this->rectangleModifierTab1->getPosition().y + ((this->rectangleModifierTab1->getSize().y - this->textModifierTab1->getGlobalBounds().height) / 2));
	this->textModifierTab2->setPosition(this->rectangleModifierTab2->getPosition().x + ((this->rectangleModifierTab2->getSize().x - this->textModifierTab2->getGlobalBounds().width) / 2), this->rectangleModifierTab2->getPosition().y + ((this->rectangleModifierTab2->getSize().y - this->textModifierTab2->getGlobalBounds().height) / 2));
	this->textModifierTab3->setPosition(this->rectangleModifierTab3->getPosition().x + ((this->rectangleModifierTab3->getSize().x - this->textModifierTab3->getGlobalBounds().width) / 2), this->rectangleModifierTab3->getPosition().y + ((this->rectangleModifierTab3->getSize().y - this->textModifierTab3->getGlobalBounds().height) / 2));
	
	// text fill color(s)
	this->textModifierTab1->setFillColor(sf::Color::White);
	this->textModifierTab2->setFillColor(sf::Color::White);
	this->textModifierTab3->setFillColor(sf::Color::White);
	
	// text render layer(s)
	this->textModifierTab1->setRenderLayer(2);
	this->textModifierTab2->setRenderLayer(2);
	this->textModifierTab3->setRenderLayer(2);



	#pragma endregion SETUP
}

void EngineModifier::update(float deltaTime)
{
	#pragma region CREATE/REFERENCE

	////////////////////////////////////////////////////////
	// reference global system/engine window and managers // (each one only needs to be referenced as they are used, this example has them all)
	////////////////////////////////////////////////////////
	//////
	////
	//

	auto& window    = *global::getWindow();
	auto& clocks    = *global::getClockManager();
	auto& events    = *global::getEventManager();
	auto& scenes    = *global::getSceneManager();
	auto& assets    = *global::getAssetManager();
	auto& scripts   = *global::getAssetManager();

	#pragma endregion CREATE/REFERENCE




	
	#pragma region CORE

	///////////////////////////
	// click on tab - events //
	///////////////////////////
	//////
	////
	//

	if (this->rectangleModifierTab1->isLeftClicked())
	{
		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
		(
			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
			this->rectangleModifierTab1->getPosition().y + this->rectangleModifierTab1->getSize().y - 2
		));

		this->modiferTab = ModifierTab::Tab1;
	}

	///////////////////////////
	// click on tab - scenes //
	///////////////////////////
	//////
	////
	//

	if (this->rectangleModifierTab2->isLeftClicked())
	{
		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
		(
			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
			this->rectangleModifierTab2->getPosition().y + this->rectangleModifierTab2->getSize().y - 2
		));

		this->modiferTab = ModifierTab::Tab2;
	}

	///////////////////////////
	// click on tab - assets //
	///////////////////////////
	//////
	////
	//

	if (this->rectangleModifierTab3->isLeftClicked())
	{
		this->rectangleModifierTabConnector->setPosition(sf::Vector2f
		(
			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
			this->rectangleModifierTab3->getPosition().y + this->rectangleModifierTab3->getSize().y - 2
		));

		this->modiferTab = ModifierTab::Tab2;
	}

	#pragma endregion CORE
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