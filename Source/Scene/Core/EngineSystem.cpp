#include "Scene/Core/EngineSystem.h"
#include "Core/Engine.h"
#include <Windows.h> // @TODO OS guards and variations - only Windows compatible atm (cannot make shapes do to name clash ... need to fix soon)





#pragma region CORE

void EngineSystem::initialize()
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

	this->portEngineMenu        = window.createPort("portEngineMenu",       0.0f,                                                   0.0f,                                                                                       1.0f,                                                       0.035f,                                                     window.getRenderLayerCount(), true);
	this->portEngineFooter      = window.createPort("portEngineFooter",     0.0f,                                                   1.f - this->portEngineMenu->getViewport().height,                                           1.0f,                                                       this->portEngineMenu->getViewport().height,                 window.getRenderLayerCount(), true);
	this->portEngineExplorer    = window.createPort("portEngineExplorer",   0.0f,                                                   this->portEngineMenu->getViewport().height,                                                 0.20f,                                                      1.0f - (this->portEngineMenu->getViewport().height * 2.0f), window.getRenderLayerCount(), true);
	this->portEngineModifier    = window.createPort("portEngineModifier",   1.0f - this->portEngineExplorer->getViewport().width,   this->portEngineExplorer->getViewport().top,                                                this->portEngineExplorer->getViewport().width,              this->portEngineExplorer->getViewport().height,             window.getRenderLayerCount(), true);
	this->portEngineEditor      = window.createPort("portEngineEditor",     this->portEngineExplorer->getViewport().width,          this->portEngineExplorer->getViewport().top,                                                1.0f - (this->portEngineExplorer->getViewport().width * 2), this->portEngineExplorer->getViewport().height * 0.750f,    window.getRenderLayerCount(), true);
	this->portEngineAuxiliary   = window.createPort("portEngineAxuiliary",  this->portEngineExplorer->getViewport().width,          this->portEngineEditor->getViewport().top + this->portEngineEditor->getViewport().height,   1.0f - (this->portEngineExplorer->getViewport().width * 2), this->portEngineExplorer->getViewport().height * 0.250f,    window.getRenderLayerCount(), true);

	///////////////////////////////////////////////////////////
	// create/reference global system/engine sound buffer(s) //
	///////////////////////////////////////////////////////////
	//////
	////
	//

	this->soundBufferEngineOk       = am.createSoundBuffer<SoundBuffer>("soundBufferEngineOk",      "Resources/Sounds/ok1.wav", this);
	this->soundBufferEngineCancel   = am.createSoundBuffer<SoundBuffer>("soundBufferEngineCancel",  "Resources/Sounds/ok2.wav", this);


	///////////////////////////////////////////////////
	// create/reference global system/engine font(s) //
	///////////////////////////////////////////////////
	//////
	////
	//

	this->fontEngineRegular     = am.createFont<Font>("fontEngineRegular",      "Resources/Fonts/Monospaced/unispace.ttf",              this);	// (monospaced)
	this->fontEngineItalic      = am.createFont<Font>("fontEngineItalic",       "Resources/Fonts/Monospaced/unispace_italic.ttf",       this);	// (monospaced)
	this->fontEngineBold        = am.createFont<Font>("fontEngineBold",         "Resources/Fonts/Monospaced/unispace_bold.ttf",         this);	// (monospaced)
	this->fontEngineBoldItalic  = am.createFont<Font>("fontEngineBoldItalic",   "Resources/Fonts/Monospaced/unispace_bold_italic.ttf",  this);	// (monospaced)

	////////////////////////////////////////////////////
	// create/reference global system/engine shape(s) //
	////////////////////////////////////////////////////
	//////
	////
	//
	
	this->textEngineResizer = am.createText<Text>("textWindowResizer", &*this->fontEngineBold, nullptr);

	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	// global
	global::setPositiveOutlineThickness(2);
	global::setUiScale(1.f);
	global::setMaxTicksPerSecond(200);
	global::setMaxFramesPerSecond(30);

	// debug
	debug::setReportingEventFocus(true);
	debug::setReportingEventMouseEntered(true);
	//debug::setReportingScriptUpdates(true);

	// scene
	this->setCodeUtilization(CodeUtilization::VirtualOverride);

	// window
	window.setRenderLayerCount(24); // assets render layers start at 0 (0 is the "back" layer and the render layer count - 1 (for array purposes) is the "front" layer
	window.setClearColor(sf::Color::Black);

	// event manager
	em.setAutoUninhibited(true);

	// window resizer
	this->textEngineResizer->setCodeUtilization(CodeUtilization::VirtualOverride);
	this->textEngineResizer->setString("<");
	this->textEngineResizer->setCharacterSize(window.getSize().y / 32);
	this->textEngineResizer->setFillColor(sf::Color(35, 35, 35));
	this->textEngineResizer->setOutlineColor(sf::Color(55, 55, 55));
	this->textEngineResizer->setOutlineThickness(3);
	this->textEngineResizer->setOrigin(this->textEngineResizer->getGlobalBounds().width / 2, this->textEngineResizer->getGlobalBounds().height / 2);
	this->textEngineResizer->setRenderEnabled(false);
	this->textEngineResizer->setRenderLayer(window.getRenderLayerCount() - 1);
	this->textEngineResizer->setActive(true);

	// window resizer update functionality
	this->textEngineResizer->setUpdate([&](float)
	{
		/*
			@TODO finish variations and fix unwanted
			resolution stretching and/or unwanted
			asset placements within ports and windows
			after resize
		*/

		/////////////////
		// resize data //
		/////////////////
		//////
		////
		//

		static AnchorResize     resizeAnchor    = AnchorResize::Left;
		static bool             started         = false;
		static bool             set             = false;
		static sf::Vector2i     previous        = sf::Vector2i(0, 0);
		static constexpr auto   marginOfError   = 5;
		static constexpr auto   minWidth        = 1280;
		static constexpr auto   minHeight       = 720;
		const auto              mousePosition   = sf::Mouse::getPosition(*window.getInstance());

		
		/////////////////
		// resize left //
		/////////////////
		//////
		////
		//

		if (mousePosition.x >= 0                    &&
			mousePosition.y >= 0                    &&
			mousePosition.x <= marginOfError        &&
			mousePosition.y <= window.getSize().y   )
		{
			resizeAnchor = AnchorResize::Left;

			if (!started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				started = true;

			if (static_cast<bool>(GetCursor()))
				SetCursor(NULL);

			this->textEngineResizer->setRenderEnabled(true);
			this->textEngineResizer->setRotation(0);
			this->textEngineResizer->setPosition(this->textEngineResizer->getGlobalBounds().width / 2, mousePosition.y);

			return;
		}

		//////////////////
		// resize Right //
		//////////////////
		//////
		////
		//

		else if (
			mousePosition.x >= window.getSize().x - marginOfError   &&
			mousePosition.y >= 0                                    &&
			mousePosition.x <= window.getSize().x                   &&
			mousePosition.y <= window.getSize().y                   )
		{
			resizeAnchor = AnchorResize::Right;

			if (!started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				started = true;

			if (static_cast<bool>(GetCursor()))
				SetCursor(NULL);

			this->textEngineResizer->setRenderEnabled(true);
			this->textEngineResizer->setRotation(180);
			this->textEngineResizer->setPosition(window.getSize().x - (this->textEngineResizer->getGlobalBounds().width / 2), mousePosition.y);

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
			this->textEngineResizer->setRenderEnabled(false);

			if (!set)
			{
				previous = sf::Mouse::getPosition();
				set = true;
				return;
			}
		
			switch (resizeAnchor)
			{
				case AnchorResize::Left:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::Top:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::Right:
				{
					auto width = window.getSize().x + (sf::Mouse::getPosition().x - previous.x);

					if (width < minWidth)
						width = minWidth;

					window.setSize(width, window.getSize().y);
				}
				break;
				
				case AnchorResize::Bottom:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::LeftTop:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::LeftBottom:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::RightTop:
				{
					// @TODO
				}
				break;
				
				case AnchorResize::RightBottom:
				{
					// @TODO
				}
				break;
			}
		
			previous = sf::Mouse::getPosition();
			return;
		}
		
		started = false;
		set     = false;
		this->textEngineResizer->setRenderEnabled(false);
		ShowCursor(true);
	});

	#pragma endregion SETUP
}

void EngineSystem::update(float deltaTime)
{
	return; // @TODO
}

void EngineSystem::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineSystem::getPortEngineMenu() const
{
	return this->portEngineMenu;
}

Port* EngineSystem::getPortEngineFooter() const
{
	return this->portEngineFooter;
}

Port* EngineSystem::getPortEngineExplorer() const
{
	return this->portEngineExplorer;
}

Port* EngineSystem::getPortEngineModifier() const
{
	return this->portEngineModifier;
}

Port* EngineSystem::getPortEngineEditor() const
{
	return this->portEngineEditor;
}

Port* EngineSystem::getPortEngineAuxiliary() const
{
	return this->portEngineAuxiliary;
}

SoundBuffer* EngineSystem::getSoundBufferEngineOk() const
{
	return this->soundBufferEngineOk;
}

SoundBuffer* EngineSystem::getSoundBufferEngineCancel() const
{
	return this->soundBufferEngineCancel;
}

Font* EngineSystem::getFontEngineRegular() const
{
	return this->fontEngineRegular;
}

Font* EngineSystem::getFontEngineItalic() const
{
	return this->fontEngineItalic;
}

Font* EngineSystem::getFontEngineBold() const
{
	return this->fontEngineBold;
}

Font* EngineSystem::getFontEngineBoldItalic() const
{
	return this->fontEngineBoldItalic;
}

#pragma endregion GETTER(S)