#include "Scene/Core/EngineFooter.h"
#include "Core/Global.h"

EngineFooter::EngineFooter()
	:
	Scene("sceneEngineFooter", true)
{
	auto& window	= *global::getWindow();
	auto& cm		= *global::getClockManager();
	auto& em		= *global::getEventManager();
	auto& sm		= *global::getSceneManager();
	auto& am		= *global::getAssetManager();

	this->setInitialize([&]
	{
		#pragma region CREATE/REFERENCE

		/////////////////////////////////////
		// create/reference window port(s) //
		/////////////////////////////////////
		//////
		////
		//
		
		auto& portMenu		= *window.getPort("portMenu");
		auto& portFooter	= *window.createPort(Port("portFooter", 0.0f, 1.f - portMenu.getViewport().height, 1.0f, portMenu.getViewport().height, window.getRenderLayerCount(), true));

		///////////////////////////////////////////////////
		// create/reference global system/engine font(s) //
		///////////////////////////////////////////////////
		//////
		////
		//

		auto& fontUnispace				= *am.getFont("fontUnispace");
		auto& fontUnispaceItalic		= *am.getFont("fontUnispaceItalic");
		auto& fontUnispaceBold			= *am.getFont("fontUnispaceBold");
		auto& fontUnispaceBoldItalic	= *am.getFont("fontUnispaceBoldItalic");

		//////////////////////////////
		// create/reference text(s) //
		//////////////////////////////
		//////
		////
		//

		auto& textTicksPerSecond	= *am.createText<Text>("textTicksPerSecond",	&fontUnispaceBold, nullptr, &portFooter);
		//auto& textFramesPerSecond	= *am.createText<Text>("textFramesPerSecond",	&fontUnispaceBold, nullptr, &portFooter);

		#pragma endregion CREATE/REFERENCE





		#pragma region SETUP

		//////////
		// port //
		//////////
		//////
		////
		//

		portFooter.getBackground()->setFillColor(sf::Color(35, 35, 35));
		portFooter.getBorder()->setOutlineColor(sf::Color(55, 55, 55));

		// ticks per second
		textTicksPerSecond.setString("TPS: ");
		textTicksPerSecond.setCharacterSize(window.getSize().y / 48);
		textTicksPerSecond.setPosition(10, 0);
		textTicksPerSecond.setFillColor(sf::Color::Yellow);
		textTicksPerSecond.setOutlineColor(sf::Color(55, 55, 55));
		textTicksPerSecond.setOutlineThickness(3);
		textTicksPerSecond.setRenderEnabled(true);
		textTicksPerSecond.setRenderLayer(window.getRenderLayerCount() - 1);
		textTicksPerSecond.setActive(true);

		// ticks per second auto update
		textTicksPerSecond.setUpdate([&](float deltaTime)
		{
			static sf::Time		second				= sf::Time(sf::seconds(1));
			static sf::Time		timeSinceLastSecond = sf::Time::Zero;
			static std::size_t	counter				= 0;
		
			timeSinceLastSecond += sf::Time(sf::seconds(deltaTime));
			counter++;
		
			if (timeSinceLastSecond >= second)
			{
				textTicksPerSecond.setString("TPS: " + std::to_string(counter));
				timeSinceLastSecond = sf::Time::Zero;
				counter = 0;
			}
		});

		//// frames per second
		//textFramesPerSecond.setString("TPS: ");
		//textFramesPerSecond.setCharacterSize(window.getSize().y / 48);
		//textFramesPerSecond.setPosition(10, 0);
		//textFramesPerSecond.setFillColor(sf::Color::Yellow);
		//textFramesPerSecond.setOutlineColor(sf::Color(55, 55, 55));
		//textFramesPerSecond.setOutlineThickness(3);
		//textFramesPerSecond.setRenderEnabled(true);
		//textFramesPerSecond.setRenderLayer(window.getRenderLayerCount() - 1);
		//textFramesPerSecond.setActive(true);
		//
		//// frames per second auto update
		//textFramesPerSecond.setUpdate([&](float deltaTime)
		//{
		//});

		#pragma endregion SETUP
	});
}
