#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"
#include <Windows.h> // @TODO OS guards and variations - only Windows compatible atm (cannot make shapes do to name clash ... need to fix soon)

EngineSystem::EngineSystem()
	:
	Scene("sceneEngineSystem", true)
{
	auto& window	= *global::getWindow();
	auto& cm		= *global::getClockManager();
	auto& em		= *global::getEventManager();
	auto& sm		= *global::getSceneManager();
	auto& am		= *global::getAssetManager();

	#pragma region CREATE/REFERENCE

	///////////////////////////////////////////////////////////
	// create/reference global system/engine sound buffer(s) //
	///////////////////////////////////////////////////////////
	//////
	////
	//

	auto& soundBufferEngineOk		= *am.createSoundBuffer<SoundBuffer>("soundBufferEngineOk",		"Resources/Sounds/ok1.wav", this);
	auto& soundBufferEngineCancel	= *am.createSoundBuffer<SoundBuffer>("soundBufferEngineCancel",	"Resources/Sounds/ok2.wav", this);


	///////////////////////////////////////////////////
	// create/reference global system/engine font(s) //
	///////////////////////////////////////////////////
	//////
	////
	//

	auto& fontUnispace				= *am.createFont<Font>("fontUnispace",				"Resources/Fonts/Monospaced/unispace.ttf",				this);	// (monospaced)
	auto& fontUnispaceItalic		= *am.createFont<Font>("fontUnispaceItalic",		"Resources/Fonts/Monospaced/unispace_italic.ttf",		this);	// (monospaced)
	auto& fontUnispaceBold			= *am.createFont<Font>("fontUnispaceBold",			"Resources/Fonts/Monospaced/unispace_bold.ttf",			this);	// (monospaced)
	auto& fontUnispaceBoldItalic	= *am.createFont<Font>("fontUnispaceBoldItalic",	"Resources/Fonts/Monospaced/unispace_bold_italic.ttf",	this);	// (monospaced)

	////////////////////////////////////////////////////
	// create/reference global system/engine shape(s) //
	////////////////////////////////////////////////////
	//////
	////
	//
	
	auto& textWindowResizer = *am.createText<Text>("textWindowResizer", &fontUnispaceBold, nullptr);

	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	this->setInitialize([&]
	{
		// window
		window.setRenderLayerCount(24); // assets render layers start at 0 (0 is the "back" layer and the render layer count - 1 (for array purposes) is the "front" layer
		window.setClearColor(sf::Color::Black);

		// event manager
		em.setAutoUninhibited(true);

		// window resizer
		textWindowResizer.setString("<");
		textWindowResizer.setCharacterSize(window.getSize().y / 32);
		textWindowResizer.setFillColor(sf::Color(35, 35, 35));
		textWindowResizer.setOutlineColor(sf::Color(55, 55, 55));
		textWindowResizer.setOutlineThickness(3);
		textWindowResizer.setOrigin(textWindowResizer.getGlobalBounds().width / 2, textWindowResizer.getGlobalBounds().height / 2);
		textWindowResizer.setRenderEnabled(false);
		textWindowResizer.setRenderLayer(window.getRenderLayerCount() - 1);
		textWindowResizer.setActive(true);

		// window resizer update functionality
		textWindowResizer.setUpdate([&](float)
		{
			/*
				@TODO finish variations and fix unwanted
				resolution stretching and/or unwanted
				asset placements within ports and windows
				after resize
			*/

			////////////////////
			// resize anchors //
			////////////////////
			//////
			////
			//

			enum class Anchor
			{
				Left,
				LeftTop,
				LeftBottom,
				Top,
				Right,
				RightTop,
				RightBottom,
				Bottom,
			};

			/////////////////
			// resize data //
			/////////////////
			//////
			////
			//

			static Anchor			anchor			= Anchor::Left;
			static bool				started			= false;
			static bool				set				= false;
			static sf::Vector2i		previous		= sf::Vector2i(0, 0);
			static constexpr auto	marginOfError	= 5;
			static constexpr auto	minWidth		= 1280;
			static constexpr auto	minHeight		= 720;
			const auto				mousePosition	= sf::Mouse::getPosition(*window.getInstance());

			
			/////////////////
			// resize left //
			/////////////////
			//////
			////
			//

			if (
				mousePosition.x >= 0					&&
				mousePosition.y >= 0					&&
				mousePosition.x <= marginOfError		&&
				mousePosition.y <= window.getSize().y	)
			{
				anchor = Anchor::Left;

				if (!started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					started = true;

				if (static_cast<bool>(GetCursor()))
					SetCursor(NULL);

				textWindowResizer.setRenderEnabled(true);
				textWindowResizer.setRotation(0);
				textWindowResizer.setPosition(textWindowResizer.getGlobalBounds().width / 2, mousePosition.y);

				return;
			}

			//////////////////
			// resize Right //
			//////////////////
			//////
			////
			//

			else if (
				mousePosition.x >= window.getSize().x - marginOfError	&&
				mousePosition.y >= 0									&&
				mousePosition.x <= window.getSize().x					&&
				mousePosition.y <= window.getSize().y 					)
			{
				anchor = Anchor::Right;

				if (!started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					started = true;

				if (static_cast<bool>(GetCursor()))
					SetCursor(NULL);

				textWindowResizer.setRenderEnabled(true);
				textWindowResizer.setRotation(180);
				textWindowResizer.setPosition(window.getSize().x - (textWindowResizer.getGlobalBounds().width / 2), mousePosition.y);

				return;
			}

			// @TODO add other resize variations

			//////////////////
			// resize final //
			//////////////////
			//////
			////
			//

			if (started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				textWindowResizer.setRenderEnabled(false);

				if (!set)
				{
					previous = sf::Mouse::getPosition();
					set = true;
					return;
				}
			
				switch (anchor)
				{
					case Anchor::Left:
					{
						// @TODO
					}
					break;
					
					case Anchor::LeftTop:
					{
						// @TODO
					}
					break;
					
					case Anchor::LeftBottom:
					{
						// @TODO
					}
					break;
					
					case Anchor::Top:
					{
						// @TODO
					}
					break;
					
					case Anchor::Right:
					{
						//const auto original = window.getSize();
						auto width = window.getSize().x + (sf::Mouse::getPosition().x - previous.x);

						if (width < minWidth)
							width = minWidth;

						window.setSize(width, window.getSize().y);
					}
					break;
					
					case Anchor::RightTop:
					{
						// @TODO
					}
					break;
					
					case Anchor::RightBottom:
					{
						// @TODO
					}
					break;
					
					case Anchor::Bottom:
					{
						// @TODO
					}
					break;
				}
			
				previous = sf::Mouse::getPosition();
				return;
			}
			
			started	= false;
			set		= false;
			textWindowResizer.setRenderEnabled(false);
			ShowCursor(true);
		});
	});

	#pragma endregion SETUP
}
