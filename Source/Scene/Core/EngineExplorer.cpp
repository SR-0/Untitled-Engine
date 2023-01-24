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
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineExplorer();

	///////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//

	this->rectangleExplorerEvents		= am.createShape<Rectangle>("this->rectangleExplorerEvents", sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 0.0f), 0.0f),																									this, &*this->port); // font at index 0 is system regular
	this->rectangleExplorerScenes		= am.createShape<Rectangle>("this->rectangleExplorerScenes", sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 1.0f), 0.0f),																									this, &*this->port); // font at index 0 is system regular
	this->rectangleExplorerAssets		= am.createShape<Rectangle>("this->rectangleExplorerAssets", sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 2.0f), 0.0f),																									this, &*this->port); // font at index 0 is system regular
	this->rectangleExplorerTabConnector = am.createShape<Rectangle>("this->rectangleExplorerAssets", sf::Vector2f(this->rectangleExplorerEvents->getSize().x - 4, 4),																						sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 0.0f) + 2, this->rectangleExplorerEvents->getPosition().y + this->rectangleExplorerEvents->getSize().y - 2),	this, &*this->port); // font at index 0 is system regular

	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//
	
	this->textExplorerEvents = am.createText<Text>("textExplorerEvents", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular
	this->textExplorerScenes = am.createText<Text>("textExplorerScenes", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular
	this->textExplorerAssets = am.createText<Text>("textExplorerAssets", &*am.getFont(0), this, &*this->port); // font at index 0 is system regular


	#pragma endregion CREATE/REFERENCE
	




	#pragma region SETUP

	// scene
	this->setCodeUtilization(CodeUtilization::VirtualOverride);

	// port
	this->port->getBackground()->setFillColor(sf::Color(35, 35, 35));
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));

	//////////////
	// shape(s) //
	//////////////
	//////
	////
	//

	// events rectangle
	this->rectangleExplorerEvents->setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerEvents->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerEvents->setOutlineThickness(-2);

	// events rectangle update functionality
	this->rectangleExplorerEvents->setUpdate([&](float)
	{
		if (this->rectangleExplorerEvents->isLeftClicked())
		{
			this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
				this->rectangleExplorerEvents->getPosition().y + this->rectangleExplorerEvents->getSize().y - 2
			));

			this->explorerTab = ExplorerTab::Events;
		}
	});

	// scenes rectangle
	this->rectangleExplorerScenes->setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerScenes->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerScenes->setOutlineThickness(-2);

	// scemes rectangle update functionality
	this->rectangleExplorerScenes->setUpdate([&](float)
	{
		if (this->rectangleExplorerScenes->isLeftClicked())
		{
			this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
				this->rectangleExplorerScenes->getPosition().y + this->rectangleExplorerScenes->getSize().y - 2
			));

			this->explorerTab = ExplorerTab::Scenes;
		}
	});

	// assets rectangle
	this->rectangleExplorerAssets->setFillColor(sf::Color(35, 35, 35));
	this->rectangleExplorerAssets->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleExplorerAssets->setOutlineThickness(-2);

	// assets rectangle update functionality
	this->rectangleExplorerAssets->setUpdate([&](float)
	{
		if (this->rectangleExplorerAssets->isLeftClicked())
		{
			this->rectangleExplorerTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
				this->rectangleExplorerAssets->getPosition().y + this->rectangleExplorerAssets->getSize().y - 2
			));

			this->explorerTab = ExplorerTab::Assets;
		}
	});

	// tab connector rectangle
	this->rectangleExplorerTabConnector->setFillColor(sf::Color(35, 35, 35));

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	constexpr auto characterSizeDivider = 96.0f;

	this->textExplorerEvents->setString("[ Events ]");
	this->textExplorerEvents->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textExplorerEvents->setPosition(this->rectangleExplorerEvents->getPosition().x + ((this->rectangleExplorerEvents->getSize().x - textExplorerEvents->getGlobalBounds().width) / 2), this->rectangleExplorerEvents->getPosition().y + ((this->rectangleExplorerEvents->getSize().y - this->textExplorerEvents->getGlobalBounds().height) / 2));
	this->textExplorerEvents->setFillColor(sf::Color::White);
	this->textExplorerEvents->setRenderLayer(1);

	this->textExplorerScenes->setString("[ Scenes ]");
	this->textExplorerScenes->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textExplorerScenes->setPosition(this->rectangleExplorerScenes->getPosition().x + ((this->rectangleExplorerScenes->getSize().x - this->textExplorerScenes->getGlobalBounds().width) / 2), this->rectangleExplorerScenes->getPosition().y + ((this->rectangleExplorerScenes->getSize().y - this->textExplorerScenes->getGlobalBounds().height) / 2));
	this->textExplorerScenes->setFillColor(sf::Color::White);
	this->textExplorerScenes->setRenderLayer(1);

	this->textExplorerAssets->setString("[ Assets ]");
	this->textExplorerAssets->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textExplorerAssets->setPosition(this->rectangleExplorerAssets->getPosition().x + ((this->rectangleExplorerAssets->getSize().x - this->textExplorerAssets->getGlobalBounds().width) / 2), this->rectangleExplorerAssets->getPosition().y + ((this->rectangleExplorerAssets->getSize().y - this->textExplorerAssets->getGlobalBounds().height) / 2));
	this->textExplorerAssets->setFillColor(sf::Color::White);
	this->textExplorerAssets->setRenderLayer(1);

	#pragma endregion SETUP
}

void EngineExplorer::update(float deltaTime)
{
	return;
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

#pragma endregion GETTER(S)