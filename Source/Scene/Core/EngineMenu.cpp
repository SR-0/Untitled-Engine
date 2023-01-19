#include "Scene/Core/EngineMenu.h"
#include "Core/Global.h"

EngineMenu::EngineMenu()
	:
	Scene("EngineMenu", true)
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
		
		auto& portMenu = *window.createPort(Port("portMenu", 0.0f, 0.0f, 1.0f, 0.025f, window.getRenderLayerCount(), true));

		/////////////////////
		// create shape(s) //
		/////////////////////
		//////
		////
		//
	
		auto& rectangleMenuClose = *am.createShape<Rectangle>("rectangleMenuClose", sf::Vector2f(window.getHeight() * portMenu.getViewport().height * 0.65f, window.getHeight() * portMenu.getViewport().height * 0.65f), sf::Vector2f(0, 0), this, &portMenu);
		
		////////////////////
		// create text(s) //
		////////////////////
		//////
		////
		//

		auto& textMenuClose = *am.createText<Text>("textMenuClose", &*am.getFont(2), this, &portMenu); // font at index 2 is system bold

		#pragma endregion CREATE





		#pragma region SETUP

		//////////
		// port //
		//////////
		//////
		////
		//

		portMenu.getBackground()->setFillColor(sf::Color(35, 35, 35));
		portMenu.getBorder()->setOutlineColor(sf::Color(55, 55, 55));

		//////////////
		// shape(s) //
		//////////////
		//////
		////
		//

		// menu close
		rectangleMenuClose.setPosition(window.getSize().x - rectangleMenuClose.getSize().x - (((window.getSize().y * portMenu.getViewport().height) - rectangleMenuClose.getSize().y) / 2), ((window.getSize().y * portMenu.getViewport().height) - rectangleMenuClose.getSize().y) / 2);
		rectangleMenuClose.setRenderLayer(1);

		// menu close update functionality
		rectangleMenuClose.setUpdate([&](float)
		{
			if (rectangleMenuClose.isLeftClicked())
			{
				window.close();
			}
			else if (rectangleMenuClose.isHoveredOver())
			{
				rectangleMenuClose.setFillColor(sf::Color(55, 55, 55));
			}
			else if (rectangleMenuClose.getFillColor() != sf::Color(35, 35, 35))
			{
				rectangleMenuClose.setFillColor(sf::Color(35, 35, 35));
			}
		});

		/////////////
		// text(s) //
		/////////////
		//////
		////
		//

		// move window
		portMenu.getBackground()->setUpdate([&](float)
		{
			static bool			started		= false;
			static bool			set			= false;
			static sf::Vector2i previous	= sf::Vector2i(0, 0);

			if (portMenu.getBackground()->isLeftClicked())
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
		textMenuClose.setString("X");
		textMenuClose.setCharacterSize(rectangleMenuClose.getWidth() * 0.75f);
		textMenuClose.setFillColor(sf::Color::White);
		textMenuClose.setPosition(rectangleMenuClose.getPosition().x + ((rectangleMenuClose.getSize().x - textMenuClose.getLocalBounds().width) / 2), rectangleMenuClose.getPosition().y + (static_cast<float>(rectangleMenuClose.getSize().y - textMenuClose.getLocalBounds().height) / 5.f));
		textMenuClose.setRenderLayer(1);

		#pragma endregion SETUP
	});
}
