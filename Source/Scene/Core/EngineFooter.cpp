#include "Scene/Core/EngineFooter.h"
#include "Core/Global.h"

EngineFooter::EngineFooter()
	:
	Scene("EngineFooter", true)
{
	auto& window	= *global::getWindow();
	auto& cm		= *global::getClockManager();
	auto& em		= *global::getEventManager();
	auto& sm		= *global::getSceneManager();
	auto& am		= *global::getAssetManager();

	this->setInitialize([&]
	{
		#pragma region CREATE

		///////////////////////////
		// create window port(s) //
		///////////////////////////
		//////
		////
		//
		
		auto& portMenu		= *window.getPort("portMenu");
		auto& portFooter	= *window.createPort(Port("portFooter", 0.0f, 1.f - portMenu.getViewport().height, 1.0f, portMenu.getViewport().height, window.getRenderLayerCount(), true));

		/////////////////////
		// create shape(s) //
		/////////////////////
		//////
		////
		//
	
		//auto& rectangleMenuClose = *am.createShape<Rectangle>("rectangleMenuClose", sf::Vector2f(window.getHeight() * portMenu.getViewport().height * 0.65f, window.getHeight() * portMenu.getViewport().height * 0.65f), sf::Vector2f(0, 0), this, &portMenu);
		
		////////////////////
		// create text(s) //
		////////////////////
		//////
		////
		//

		//auto& textMenuClose = *am.createText<Text>("textMenuClose", &*am.getFont(2), this, &portMenu); // font at index 2 is system bold

		#pragma endregion CREATE





		#pragma region SETUP

		//////////
		// port //
		//////////
		//////
		////
		//

		portFooter.getBackground()->setFillColor(sf::Color(35, 35, 35));
		portFooter.getBorder()->setOutlineColor(sf::Color(55, 55, 55));

		#pragma endregion SETUP
	});
}
