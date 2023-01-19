#include "Scene/Core/EngineEditor.h"
#include "Core/Global.h"

EngineEditor::EngineEditor() // warning, this must be created/initialized after System scene creation/initialization
	:
	Scene("sceneEngineEditor", true)
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
		auto& portExplorer	= *window.getPort("portExplorer");
		auto& portEditor	= *window.createPort(Port("portEditor", portExplorer.getViewport().width, portExplorer.getViewport().top, 1.0f - (portExplorer.getViewport().width * 2), portExplorer.getViewport().height, window.getRenderLayerCount(), true));


		///////////////////////////////
		// create/reference sound(s) //
		///////////////////////////////
		//////
		////
		//

		auto& soundEditorOk		= *am.createSound<Sound>("soundEngineOk",		&*am.getSoundBuffer(0), this); // sound buffer index 0 is always system/engine ok
		auto& soundEditorCancel	= *am.createSound<Sound>("soundEngineCancel",	&*am.getSoundBuffer(1), this); // sound buffer index 1 is always system/engine cancel


		///////////////////////////////////////////////////
		// create/reference global system/engine font(s) //
		///////////////////////////////////////////////////
		//////
		////
		//

		auto& fontUnispace				= *am.getFont(0); // 0 will always be system/engine font unispace regular
		auto& fontUnispaceItalic		= *am.getFont(1); // 0 will always be system/engine font unispace italic
		auto& fontUnispaceBold			= *am.getFont(2); // 0 will always be system/engine font unispace bold
		auto& fontUnispaceBoldItalic	= *am.getFont(3); // 0 will always be system/engine font unispace bold italic

		/////////////////////////////////
		// create/reference texture(s) //
		/////////////////////////////////
		//////
		////
		//

		// temp for testing
		auto&		textureTiles				= *am.createTexture<Texture>("textureTiles", "Resources/Textures/Tiles/wastland_machina_tileset_terrain_63px80py_4c3r.png", this);
		const auto	textureTilesColumnCount		= 4;
		const auto	textureTilesRowCount		= 3;
		const auto	textureTilesStartColumn		= 3;
		const auto	textureTilesStartRow		= 2;
		const auto	textureTilesSelectorColumn	= 0;
		const auto	textureTilesSelectorRow		= 2;

		///////////////////////////////
		// create/reference shape(s) //
		///////////////////////////////
		//////
		////
		//
	
		//auto& rectangleEditorTileSelector	= *am.createShape<Rectangle>("rectangleEditorTileSelector", sf::Vector2f(textureTiles.getSize().x / textureTilesColumnCount, textureTiles.getSize().y / textureTilesRowCount),	sf::Vector2f(0, 0),	this, &portEditor);
		auto& rectangleEditorTileCuller		= *am.createShape<Rectangle>("rectangleEditorTileCuller",	sf::Vector2f(),																										sf::Vector2f(0, 0),	this, &portEditor);
		auto& rectangleEditorSplashScreen	= *am.createShape<Rectangle>("rectangleEditorSplashScreen", sf::Vector2f(window.getWidth(), window.getHeight()),																sf::Vector2f(0, 0),	this, &portEditor);
		
		///////////////////////////////
		// create/reference tilemaps // @TODO temp for testing
		///////////////////////////////
		//////
		////
		//

		auto& tilemapMain = *am.createTilemap<Tilemap>
		(
			"tilemapMain",				// id 
			50,							// columns
			50,							// rows
			5,							// layers
			18,							// depth in pixels
			sf::Vector2f(1.f, 1.f),		// scale
			&textureTiles,				// texture
			textureTilesColumnCount,	// texture columns
			textureTilesRowCount,		// texture rows
			textureTilesStartColumn,	// texture start column
			textureTilesStartRow,		// texture start row
			false,						// centered origin (left-top if false, centered after depth if true)
			Tile::Type::Isometric,		// type 
			this,						// parent scene
			&portEditor					// port
		);

		#pragma endregion CREATE/REFERENCE





		#pragma region SETUP

		////////////////
		// background //
		////////////////
		//////
		////
		//

		portEditor.getBackground()->setRenderEnabled(false);
		portEditor.getBorder()->setOutlineColor(sf::Color(55, 55, 55));
	
		///////////////////
		// tile selector // @TODO
		///////////////////
		//////
		////
		//
		
		//rectangleEditorTileSelector.setRenderLayer(window.getRenderLayerCount() - 2);
		//rectangleEditorTileSelector.setSize(sf::Vector2f(textureTiles.getSize().x / textureTilesColumnCount, textureTiles.getSize().y / textureTilesRowCount));
		//rectangleEditorTileSelector.setTexture(&textureTiles);
		//
		//rectangleEditorTileSelector.setTextureRect(sf::IntRect
		//(
		//	(textureTiles.getSize().x / textureTilesColumnCount) * textureTilesSelectorColumn,
		//	(textureTiles.getSize().y / textureTilesRowCount) * textureTilesSelectorRow,
		//	(textureTiles.getSize().x / textureTilesColumnCount),
		//	(textureTiles.getSize().y / textureTilesRowCount)
		//));

		/////////////////
		// tile culler //
		/////////////////
		//////
		////
		//

		rectangleEditorTileCuller.setFillColor(sf::Color::Transparent);
		rectangleEditorTileCuller.setOutlineColor(sf::Color::Red);
		rectangleEditorTileCuller.setOutlineThickness(-2);
		rectangleEditorTileCuller.setRenderLayer(window.getRenderLayerCount() - 1);
		rectangleEditorTileCuller.setSize((window.getWidth() * portEditor.getViewport().width) / 2/*@TODO testing*/, (window.getHeight()* portEditor.getViewport().height) / 2/*@TODO testing*/);
		rectangleEditorTileCuller.setOrigin(rectangleEditorTileCuller.getSize().x / 2, rectangleEditorTileCuller.getSize().y / 2);
		rectangleEditorTileCuller.setPosition(portEditor.getCenter());// .x* portEditor.getViewport().width, portEditor.getCenter().y* portEditor.getViewport().height);
	
		///////////////////
		// splash screen //
		///////////////////
		//////
		////
		//

		rectangleEditorSplashScreen.setFillColor(sf::Color::Black);
		rectangleEditorSplashScreen.setRenderLayer(window.getRenderLayerCount() - 1);

		// splash screen update
		rectangleEditorSplashScreen.setUpdate([&](float deltaTime)
		{
			if (!rectangleEditorSplashScreen.isTransparent())
				rectangleEditorSplashScreen.fadeOut(1 * deltaTime);
			if (rectangleEditorSplashScreen.getRenderLayer() != (window.getRenderLayerCount() - 1))
				rectangleEditorSplashScreen.setRenderLayer(window.getRenderLayerCount() - 1);
		});

		/////////////
		// tilemap // (temp)
		/////////////
		//////
		////
		//

		// randomize tile texture indexes to random solid/opaque texture indexes
		tilemapMain.iterateTiles([&](Tile& tile)
		{
			auto column = srng<unsigned>::range(0, tilemapMain.getTextureColumnCount() - 1);
			auto row	= srng<unsigned>::range(0, tilemapMain.getTextureRowCount() - 2);
			tile.setTextureIndex(column, row);
		});

		// @TODO temp
		//tilemapMain.updateTilesRenderEnabled();
		
		#pragma endregion SETUP





		#pragma region EVENT BINDING(S)

		///////////////////
		// save and quit //
		///////////////////
		//////
		////
		//
											//////////////////
		em.createBinding(					// explaination //
		{									//////////////////
											//
											//	////////
			"editor-save-and-quit",			//	// id //
											//	////////
											//	//
											//	//	each binding has 'id' and 'uuid' -  
											//	//	'id' can be a duplicate and is 
											//	//	accessable via public member getter
											//	//	and setter, 'uuid' is automatically
											//	//	assigned umique id and is accessable
											//	//	via public member getter
											//
											//	///////////
			{ sf::Event::KeyPressed },		//	// types //
											//	///////////
											//	//
											//	//	containter of events types required
											//	//	to trigger this binding's function
											//	//	on every update/tick, assuming it
											//	//	is active and parental restrictions
											//	//	(or lack there of) allow it (e.g.
											//	//	sf::Event::Closed, sf::Event::-
											//	//	-KeyPressed, sf::Event::-
											//	//	-MouseButtonReleased, etc...)
											//
											//	//////////
			{ sf::Keyboard::Escape },		//	// keys //
											//	//////////
											//	//
											//	//	containter of keyboard keys required
											//	//	to trigger this binding's function
											//	//	on every update/tick, assuming it
											//	//	is active and parental restrictions
											//	//	(or lack there of) allow it (e.g.
											//	//	sf::Keyboard::A, sf::Keyboard::-
											//	//	-T, sf::Keyboard::D, etc...)
											//
											//	/////////////
			{},								//	// buttons //
											//	/////////////
											//	//
											//	//	containter of mouse buttons required
											//	//	to trigger this binding's function
											//	//	on every update/tick, assuming it
											//	//	is active and parental restrictions
											//	//	(or lack there of) allow it (e.g.
											//	//	sf::Mouse::Button::Left, sf::Mouse::-
											//	//	-Button::Middle, sf::Mouse::Button::-
											//	//	Right, etc...) "{}" for no inputs
											//
											//	///////////////
			{ sf::Keyboard::LShift },		//	// modifiers //
											//	///////////////
											//	//
											//	//	containter of modifiers required
											//	//	to trigger this binding's function
											//	//	on every update/tick, assuming it
											//	//	is active and parental restrictions
											//	//	(or lack there of) allow it (e.g. sf::-
											//	//	Keyboard::LShift, sf::Keyboard::-
											//	//	RControl, sf::Keyboard::LAlt,
											//	//  sf::Keyboard::Space etc...) - 
											//	//	tradition modifiers are a smaller
											//	//	subset, this will be fixed soon
											//	//	@TODO
											//
											//	////////////
			true,							//	// active //
											//	////////////
											//	//
											//	//	if active, function will automatically
											//	//	be called each update/tick
											//
											//	//////////////////
			this,							//	// parent scene //
											//	//////////////////
											//	//
											//	//	pointer to parent Scene object, in
											//	//	which case parent scene needs to be
											//	//	active in addition to this binding
											//	//	being active in order to call function
											//	//	automatically each update/tick, leave
											//	//	as nullptr to avoid parental
											//	//	restrictions
											//
											//	//////////////
			[&](float){ window.close(); }	//	// function // @TODO (far from finished)
											//	//////////////
											//	//
											//	//	any functionality/lambda here will do
											//	//	as long as it returns 'void' and has 
											//	//	no parameters (possible expansion in
											//	//	the future but so far I haven't felt
											//	//	a need) - this will get called every
											//	//	update/tick cycle if active and parental
											//	//	restrictions (or lack there of) allow
											//	//	it
		});

		/////////////////
		// scroll/zoom //
		/////////////////
		//////
		////
		//

		static float currentZoomFactor = 1.f;

		// mouse wheel zoom
		auto& bindingSystemMouseWheelZoom = *em.createBinding(
		{
			"bindingSystemMouseWheelZoom",
			{ sf::Event::MouseWheelScrolled },
			{},
			{},
			{ sf::Keyboard::LControl },
			true,
			this,
			[&](float)
			{
				if (auto* binding = em.getBinding("bindingMouseWheelZoom"))
				{
					// zoom in
					if (binding->getMouseScrollDelta() > 0.0f)
					{
						auto view = portEditor.getView();
						currentZoomFactor *= 2.000000f;
						if (currentZoomFactor >= 32.000000f)
						{
							currentZoomFactor = 32.000000f;
						}
						else
						{
							view.setSize(view.getSize().x / 2.000000f, view.getSize().y / 2.000000f);
							view.setCenter(view.getSize().x / 2.000000f, view.getSize().y / 2.0000000f);
							rectangleEditorTileCuller.setSize(rectangleEditorTileCuller.getSize().x / 2.000000f, rectangleEditorTileCuller.getSize().y / 2.000000f);
							rectangleEditorTileCuller.setOrigin(rectangleEditorTileCuller.getSize().x / 2.000000f, rectangleEditorTileCuller.getSize().y / 2.000000f);
						}
						portEditor.setView(view);
						rectangleEditorTileCuller.setPosition(portEditor.getCenter());
					}
					
					// zoom out
					else if (binding->getMouseScrollDelta() < 0.0f)
					{
						auto view = portEditor.getView();
						currentZoomFactor /= 2.000000f;
						if (currentZoomFactor <= 0.062500f)
						{
							currentZoomFactor = 0.062500f;
						}
						else
						{
							view.setSize(view.getSize().x * 2.000000f, view.getSize().y * 2.000000f);
							view.setCenter(view.getSize().x / 2.000000f, view.getSize().y / 2.000000f);
							rectangleEditorTileCuller.setSize(rectangleEditorTileCuller.getSize().x * 2.000000f, rectangleEditorTileCuller.getSize().y * 2.000000f);
							rectangleEditorTileCuller.setOrigin(rectangleEditorTileCuller.getSize().x / 2.000000f, rectangleEditorTileCuller.getSize().y / 2.000000f);
						}
						portEditor.setView(view);
						rectangleEditorTileCuller.setPosition(portEditor.getCenter());
					}
				}
			}
		});

		bindingSystemMouseWheelZoom.setMouseEnteredRequired(true);

		// TEMP
		auto& bindingSystemScrollLeft = *em.createBinding(Binding
		(
			"bindingSystemScrollLeft",
			{ sf::Event::KeyPressed },
			{ sf::Keyboard::Left },
			{},
			{},
			true,
			this,
			[&](float deltaTime)
			{
				const auto modifier = 1200.000f * deltaTime;
				auto viewport = portEditor.getViewport();
				portEditor.setView(portEditor.getCenter().x - modifier, portEditor.getCenter().y, portEditor.getSize().x, portEditor.getSize().y);
				if (portEditor.getCenter().x - (portEditor.getSize().x / 2) < 0)
				{
					portEditor.setView(portEditor.getSize().x / 2, portEditor.getCenter().y, portEditor.getSize().x, portEditor.getSize().y);
					rectangleEditorTileCuller.setPosition(portEditor.getCenter());
				}
				else
					rectangleEditorTileCuller.move(sf::Vector2f(-modifier, 0));
				portEditor.setViewport(viewport);
			}
		));

		bindingSystemScrollLeft.setMouseEnteredRequired(true);

		auto& bindingSystemScrollRight = *em.createBinding(Binding
		(
			"bindingSystemScrollRight",
			{ sf::Event::KeyPressed },
			{ sf::Keyboard::Right },
			{},
			{},
			true,
			this,
			[&](float deltaTime)
			{
				const auto modifier = 1200.000f * deltaTime;
				rectangleEditorTileCuller.move(sf::Vector2f(modifier, 0));
				auto viewport = portEditor.getViewport();
				portEditor.setView(portEditor.getCenter().x + modifier, portEditor.getCenter().y, portEditor.getSize().x, portEditor.getSize().y);
				portEditor.setViewport(viewport);
			}
		));

		bindingSystemScrollRight.setMouseEnteredRequired(true);

		auto& bindingSystemScrollUp = *em.createBinding(Binding
		(
			"bindingSystemScrollUp",
			{ sf::Event::KeyPressed },
			{ sf::Keyboard::Up },
			{},
			{},
			true,
			this,
			[&](float deltaTime)
			{
				const auto modifier = 1200.000f * deltaTime;
				auto viewport = portEditor.getViewport();
				portEditor.setView(portEditor.getCenter().x, portEditor.getCenter().y - modifier, portEditor.getSize().x, portEditor.getSize().y);
				if (portEditor.getCenter().y - (portEditor.getSize().y / 2) < 0)
				{
					portEditor.setView(portEditor.getCenter().x, portEditor.getSize().y / 2, portEditor.getSize().x, portEditor.getSize().y);
					rectangleEditorTileCuller.setPosition(portEditor.getCenter());

				}
				else
					rectangleEditorTileCuller.move(sf::Vector2f(0, -modifier));
				portEditor.setViewport(viewport);
			}
		));

		bindingSystemScrollUp.setMouseEnteredRequired(true);

		auto& bindingSystemScrollDown = *em.createBinding(Binding
		(
			"bindingSystemScrollDown",
			{ sf::Event::KeyPressed },
			{ sf::Keyboard::Down },
			{},
			{},
			true,
			this,
			[&](float deltaTime)
			{
				const auto modifier = 1200.000f * deltaTime;
				rectangleEditorTileCuller.move(sf::Vector2f(0, modifier));
				auto viewport = portEditor.getViewport();
				portEditor.setView(portEditor.getCenter().x, portEditor.getCenter().y + modifier, portEditor.getSize().x, portEditor.getSize().y);
				portEditor.setViewport(viewport);
			}
		));

		bindingSystemScrollDown.setMouseEnteredRequired(true);

		#pragma endregion EVENT BINDING(S)
	});
}
