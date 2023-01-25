#include "Scene/Core/EngineFooter.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"





#pragma region CORE

void EngineFooter::initialize()
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
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineFooter();


	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//

	this->textTicksPerSecond = am.createText<Text>("textTicksPerSecond", &*am.getFont(0), nullptr, &*this->port);

	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	// scene
	this->setCodeUtilization(CodeUtilization::VirtualOverride);

	// port
	this->port->getBackground()->setFillColor(sf::Color(35, 35, 35));
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));

	// ticks per second
	this->textTicksPerSecond->setString("TPS: ");
	this->textTicksPerSecond->setCharacterSize(global::getFontSize() * global::getUiScale());
	this->textTicksPerSecond->setPosition(((window.getSize().y * this->port->getViewport().height) - this->textTicksPerSecond->getGlobalBounds().height) / 2, ((window.getSize().y * this->port->getViewport().height) - this->textTicksPerSecond->getGlobalBounds().height) / 2);
	this->textTicksPerSecond->setFillColor(sf::Color::White);
	this->textTicksPerSecond->setRenderEnabled(true);
	this->textTicksPerSecond->setRenderLayer(window.getRenderLayerCount() - 1);
	this->textTicksPerSecond->setActive(true);

	// ticks per second auto update
	this->textTicksPerSecond->setUpdate([&](float deltaTime)
	{
		static auto& timer = cm.createTimer("tps", 0.1f);

		if (timer.isCompleted())
		{
			auto tps = std::roundf(sf::Time(sf::seconds(1)).asSeconds() / deltaTime);
			this->textTicksPerSecond->setString("TPS - " + std::to_string(static_cast<int>(tps)) + "");
			timer.restart();
		}
	});

	#pragma endregion SETUP
}

void EngineFooter::update(float deltaTime)
{
	return;
}

void EngineFooter::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineFooter::getPort() const
{
	return this->port;
}

#pragma endregion GETTER(S)