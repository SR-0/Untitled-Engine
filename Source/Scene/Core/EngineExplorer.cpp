#include "Scene/Core/EngineExplorer.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"





#pragma region CORE

void EngineExplorer::initialize()
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
	
	this->port = scenes.getScene(0)->as<EngineSystem>()->getPortEngineExplorer();

	///////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//

	this->rectangleExplorerTabs = std::vector<ExplorerTab*> // does not own rectangles, only pointers to them, asset manager handles destruction without custom deleter (too lazy @TODO)
	{
		this->rectangleExplorerEvents   = assets.createShape<ExplorerTab>("rectangleExplorerEvents", ExplorerTab::Type::Events),
		this->rectangleExplorerScenes   = assets.createShape<ExplorerTab>("rectangleExplorerScenes", ExplorerTab::Type::Scenes),	
		this->rectangleExplorerAssets   = assets.createShape<ExplorerTab>("rectangleExplorerAssets", ExplorerTab::Type::Assets),
		//this->rectangleExplorerScripts  = assets.createShape<ExplorerTab>("rectangleExplorerAssets", ExplorerTab::Type::Scripts)
	};

	this->rectangleExplorerTabConnector = assets.createShape<Rectangle>("rectangleExplorerTabConnector");
	this->rectangleExplorerHighlighter  = assets.createShape<Rectangle>("rectangleExplorerHighlighter");

	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//
	
	this->textExplorerTabs = std::vector<Text*> // does not own rectangles, only pointers to them, asset manager handles destruction without custom deleter (too lazy @TODO)
	{
		this->textExplorerEvents = assets.createText<Text>("textExplorerEvents"),
		this->textExplorerScenes = assets.createText<Text>("textExplorerScenes"),
		this->textExplorerAssets = assets.createText<Text>("textExplorerAssets"),
	};

	this->textExplorerTree      = assets.createText<Text>("textExplorerTree");

	#pragma endregion CREATE/REFERENCE
	




	#pragma region SETUP

	// scene
	this->setCodeUtilization(CodeUtilization::VirtualOverride);

	// port background and border
	this->port->getBackground()->setFillColor(sf::Color(35, 35, 35));
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));

	//////////////
	// shape(s) //
	//////////////
	//////
	////
	//

	// rectangle size(s)
	this->rectangleExplorerEvents->         setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size())), static_cast<float>(window.getSize().y) * 0.025f);
	this->rectangleExplorerScenes->         setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size())), static_cast<float>(window.getSize().y) * 0.025f);
	this->rectangleExplorerAssets->         setSize((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size())), static_cast<float>(window.getSize().y) * 0.025f);
	this->rectangleExplorerTabConnector->   setSize(this->rectangleExplorerEvents->getSize().x - (global::getPositiveOutlineThickness() * 2),                                                     global::getPositiveOutlineThickness() * 2);
	this->rectangleExplorerHighlighter->    setSize(0.f, 0.f);
	
	// rectangle position(s)
	this->rectangleExplorerEvents->         setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size()))) * 0.0f,                                         0.0f);
	this->rectangleExplorerScenes->         setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size()))) * 1.0f,                                         0.0f);
	this->rectangleExplorerAssets->         setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size()))) * 2.0f,                                         0.0f);
	this->rectangleExplorerTabConnector->   setPosition(((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size()))) * 0.0f + global::getPositiveOutlineThickness(), this->rectangleExplorerEvents->getPosition().y + this->rectangleExplorerEvents->getSize().y - global::getPositiveOutlineThickness());
	this->rectangleExplorerHighlighter->    setPosition(0.f, 0.f);
	
	// rectangle parent scene attachment(s)
	this->rectangleExplorerEvents->         setParentScene(this);
	this->rectangleExplorerScenes->         setParentScene(this);
	this->rectangleExplorerAssets->         setParentScene(this);
	this->rectangleExplorerTabConnector->   setParentScene(this);
	this->rectangleExplorerHighlighter->    setParentScene(this);
	
	// rectangle port attachment(s)
	this->rectangleExplorerEvents->         setPort(this->port);
	this->rectangleExplorerScenes->         setPort(this->port);
	this->rectangleExplorerAssets->         setPort(this->port);
	this->rectangleExplorerTabConnector->   setPort(this->port);
	this->rectangleExplorerHighlighter->    setPort(this->port);

	// rectangle fill color(s)
	this->rectangleExplorerEvents->         setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerScenes->         setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerAssets->         setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerTabConnector->   setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerHighlighter->    setFillColor(sf::Color(35, 35, 35));

	// rectangle outline color(s)
	this->rectangleExplorerEvents->         setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerScenes->         setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerAssets->         setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerTabConnector->   setOutlineColor(rectangleExplorerTabConnector->getFillColor());
	this->rectangleExplorerHighlighter->    setOutlineColor(rectangleExplorerHighlighter->getFillColor());

	// rectangle outline thickness(es)
	this->rectangleExplorerEvents->         setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleExplorerScenes->         setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleExplorerAssets->         setOutlineThickness(-global::getPositiveOutlineThickness());
	this->rectangleExplorerTabConnector->   setOutlineThickness(0);
	this->rectangleExplorerHighlighter->    setOutlineThickness(0);

	// rectangle render layer(s)
	this->rectangleExplorerEvents->         setRenderLayer(1);
	this->rectangleExplorerScenes->         setRenderLayer(1);
	this->rectangleExplorerAssets->         setRenderLayer(1);
	this->rectangleExplorerTabConnector->   setRenderLayer(1);
	this->rectangleExplorerHighlighter->    setRenderLayer(1);

	/*
		it's usually a good idea to leave render
		layer 0 for system/window/port backgrounds
		- (might restrict 0 in future)
	*/

	// rectangle render enabled state(s)
	this->rectangleExplorerEvents->         setRenderEnabled(true);
	this->rectangleExplorerScenes->         setRenderEnabled(true);
	this->rectangleExplorerAssets->         setRenderEnabled(true);
	this->rectangleExplorerTabConnector->   setRenderEnabled(true);
	this->rectangleExplorerHighlighter->    setRenderEnabled(false);

	// rectangle active state(s)
	this->rectangleExplorerEvents->         setActive(false);
	this->rectangleExplorerScenes->         setActive(false);
	this->rectangleExplorerAssets->         setActive(false);
	this->rectangleExplorerTabConnector->   setActive(false);
	this->rectangleExplorerHighlighter->    setActive(false);

	/*
		set true if you want to utilize automated
		lambda/std::function-based funtionality
		- (needs to be set via "setUpdate")
	*/

	//this->rectangleExplorerEvents->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleExplorerEvents->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleExplorerEvents->setOutlineThickness(-2);
	//this->rectangleExplorerEvents->setActive(true); // must be active to call its update function
	//
	//// events rectangle update functionality
	//this->rectangleExplorerEvents->setUpdate([&](float)
	//{
	//	if (this->rectangleExplorerEvents->isLeftClicked())
	//	{
	//		this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
	//			this->rectangleExplorerEvents->getPosition().y + this->rectangleExplorerEvents->getSize().y - 2
	//		));
	//
	//		this->explorerTab = ExplorerTab::Events;
	//	}
	//});
	//
	// scenes rectangle
	//this->rectangleExplorerScenes->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleExplorerScenes->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleExplorerScenes->setOutlineThickness(-2);
	//this->rectangleExplorerScenes->setActive(true); // must be active to call its update function
	//
	//// scemes rectangle update functionality
	//this->rectangleExplorerScenes->setUpdate([&](float)
	//{
	//	if (this->rectangleExplorerScenes->isLeftClicked())
	//	{
	//		this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
	//			this->rectangleExplorerScenes->getPosition().y + this->rectangleExplorerScenes->getSize().y - 2
	//		));
	//
	//		this->explorerTab = ExplorerTab::Scenes;
	//	}
	//});
	//
	// assets rectangle
	//this->rectangleExplorerAssets->setFillColor(sf::Color(35, 35, 35));
	//this->rectangleExplorerAssets->setOutlineColor(sf::Color(55, 55, 55));
	//this->rectangleExplorerAssets->setOutlineThickness(-2);
	//this->rectangleExplorerAssets->setActive(true); // must be active to call its update function
	//
	//// assets rectangle update functionality
	//this->rectangleExplorerAssets->setUpdate([&](float)
	//{
	//	if (this->rectangleExplorerAssets->isLeftClicked())
	//	{
	//		this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
	//		(
	//			((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
	//			this->rectangleExplorerAssets->getPosition().y + this->rectangleExplorerAssets->getSize().y - 2
	//		));
	//
	//		this->explorerTab = ExplorerTab::Assets;
	//	}
	//});
	//
	// tab connector rectangle
	//this->rectangleExplorerTabConnector->setFillColor(sf::Color(35, 35, 35));

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	// text fonts(s)
	this->textExplorerEvents->setFont(*assets.getFont(0)); // font at index 0 is system regular
	this->textExplorerScenes->setFont(*assets.getFont(0)); // font at index 0 is system regular
	this->textExplorerAssets->setFont(*assets.getFont(0)); // font at index 0 is system regular

	// text parent scene(s)
	this->textExplorerEvents->setParentScene(this);
	this->textExplorerScenes->setParentScene(this);
	this->textExplorerAssets->setParentScene(this);

	// text attached port(s) @TODO let assets have multiple port attachments
	this->textExplorerEvents->setPort(this->port);
	this->textExplorerScenes->setPort(this->port);
	this->textExplorerAssets->setPort(this->port);

	// test string(s)
	this->textExplorerEvents->setString("[ Events ]");
	this->textExplorerScenes->setString("[ Scenes ]");
	this->textExplorerAssets->setString("[ Assets ]");
	
	// test character size(s)
	this->textExplorerEvents->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textExplorerScenes->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textExplorerAssets->setCharacterSize(global::getFontSize() * global::getUiScale());
	
	// text position(s)
	this->textExplorerEvents->setPosition(this->rectangleExplorerEvents->getPosition().x + ((this->rectangleExplorerEvents->getSize().x - this->textExplorerEvents->getGlobalBounds().width) / 2), this->rectangleExplorerEvents->getPosition().y + ((this->rectangleExplorerEvents->getSize().y - this->textExplorerEvents->getGlobalBounds().height) / 2));
	this->textExplorerScenes->setPosition(this->rectangleExplorerScenes->getPosition().x + ((this->rectangleExplorerScenes->getSize().x - this->textExplorerScenes->getGlobalBounds().width) / 2), this->rectangleExplorerScenes->getPosition().y + ((this->rectangleExplorerScenes->getSize().y - this->textExplorerScenes->getGlobalBounds().height) / 2));
	this->textExplorerAssets->setPosition(this->rectangleExplorerAssets->getPosition().x + ((this->rectangleExplorerAssets->getSize().x - this->textExplorerAssets->getGlobalBounds().width) / 2), this->rectangleExplorerAssets->getPosition().y + ((this->rectangleExplorerAssets->getSize().y - this->textExplorerAssets->getGlobalBounds().height) / 2));
	
	// text fill color(s)
	this->textExplorerEvents->setFillColor(sf::Color::White);
	this->textExplorerScenes->setFillColor(sf::Color::White);
	this->textExplorerAssets->setFillColor(sf::Color::White);
	
	// text render layer(s)
	this->textExplorerEvents->setRenderLayer(2);
	this->textExplorerScenes->setRenderLayer(2);
	this->textExplorerAssets->setRenderLayer(2);

	#pragma endregion SETUP
}

void EngineExplorer::update(float deltaTime)
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

	for (std::size_t i = 0; i < this->rectangleExplorerTabs.size(); i++)
	{
		auto& rectangle = *this->rectangleExplorerTabs[i];

		if (rectangle.isLeftClicked())
		{
			this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * (1.0f / static_cast<float>(this->rectangleExplorerTabs.size())) * static_cast<float>(i)) + global::getPositiveOutlineThickness(),
				rectangle.getPosition().y + rectangle.getSize().y - global::getPositiveOutlineThickness()
			));

			switch (rectangle.explorerTabType)
			{
				case ExplorerTab::Type::Events:
				{
					currentExplorerTab = ExplorerTab::Type::Events;
				}
				break;

				case ExplorerTab::Type::Scenes:
				{
					currentExplorerTab = ExplorerTab::Type::Scenes;
				}
				break;

				case ExplorerTab::Type::Assets:
				{
					currentExplorerTab = ExplorerTab::Type::Assets;
				}
				break;
			}
			//this->explorerTab = ExplorerTab::Events;
		}
	}

	#pragma endregion CORE
}

void EngineExplorer::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineExplorer::getPort() const
{
	return nullptr;
}

void EngineExplorer::updateExplorerTree(float deltaTime)
{

}

#pragma endregion GETTER(S)