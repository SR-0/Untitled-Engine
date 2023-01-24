#include "Scene/Core/EngineEditor.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Global.h"





#pragma region CORE

void EngineEditor::initialize()
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
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineEditor();

	///////////////////////////////
	// create/reference sound(s) //
	///////////////////////////////
	//////
	////
	//

	this->soundEditorOk		= am.createSound<Sound>("soundEngineOk",		&*am.getSoundBuffer(0), this); // sound buffer index 0 is always system/engine ok
	this->soundEditorCancel	= am.createSound<Sound>("soundEngineCancel",	&*am.getSoundBuffer(1), this); // sound buffer index 1 is always system/engine cancel

	/////////////////////////////////
	// create/reference texture(s) //
	/////////////////////////////////
	//////
	////
	//

	// temp for testing
	this->textureEditorTiles = am.createTexture<Texture>("textureEditorTiles", "Resources/Textures/Tiles/tiny_blocks_16w18h6c6r_x8.png", this);

	///////////////////////////////
	// create/reference shape(s) //
	///////////////////////////////
	//////
	////
	//
	
	//auto& rectangleEditorTileSelector	= *am.createShape<Rectangle>("rectangleEditorTileSelector", sf::Vector2f(textureTiles.getSize().x / textureTilesColumnCount, textureTiles.getSize().y / textureTilesRowCount),	sf::Vector2f(0, 0),	this, &*this->port);
	this->rectangleEditorTileCuller		= am.createShape<Rectangle>("rectangleEditorTileCuller",	sf::Vector2f(),																										sf::Vector2f(0, 0),	this, &*this->port);
	
	///////////////////////////////
	// create/reference tilemaps // @TODO temp for testing
	///////////////////////////////
	//////
	////
	//

	const auto textureTilesColumnCount		= 6;
	const auto textureTilesRowCount			= 6;
	const auto textureTilesStartColumn		= 3;
	const auto textureTilesStartRow			= 2;
	const auto textureTilesSelectorColumn	= 0;
	const auto textureTilesSelectorRow		= 2;

	auto& tilemapMain = *am.createTilemap<Tilemap>();

	tilemapMain.setup
	(
		"tilemapMain",				// id 
		50,							// columns
		50,							// rows
		5,							// layers
		10 * 8,						// depth in pixels
		sf::Vector2f(1.f, 1.f),		// scale
		&*this->textureEditorTiles,	// texture
		textureTilesColumnCount,	// texture columns
		textureTilesRowCount,		// texture rows
		textureTilesStartColumn,	// texture start column
		textureTilesStartRow,		// texture start row
		false,						// centered origin (left-top if false, centered after depth if true)
		TileType::Isometric,		// type 
		this,						// parent scene
		&*this->port				// port
	);

	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	////////////////
	// background //
	////////////////
	//////
	////
	//

	this->port->getBackground()->setRenderEnabled(false);
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));
	
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

	this->rectangleEditorTileCuller->setFillColor(sf::Color::Transparent);
	this->rectangleEditorTileCuller->setOutlineColor(sf::Color::Red);
	this->rectangleEditorTileCuller->setOutlineThickness(-2);
	this->rectangleEditorTileCuller->setRenderLayer(window.getRenderLayerCount() - 1);
	this->rectangleEditorTileCuller->setSize((window.getWidth() * port->getViewport().width) / 2/*@TODO testing*/, (window.getHeight()* this->port->getViewport().height) / 2/*@TODO testing*/);
	this->rectangleEditorTileCuller->setOrigin(this->rectangleEditorTileCuller->getSize().x / 2, this->rectangleEditorTileCuller->getSize().y / 2);
	this->rectangleEditorTileCuller->setPosition(this->port->getCenter());// .x* port->getViewport().width, port->getCenter().y* port->getViewport().height);
	
	///////////////////
	// splash screen //
	///////////////////
	//////
	////
	//

	//this->rectangleEditorSplashScreen->setFillColor(sf::Color::Black);
	//this->rectangleEditorSplashScreen->setRenderLayer(window.getRenderLayerCount() - 1);
	//
	//// splash screen update
	//this->rectangleEditorSplashScreen->setUpdate([&](float deltaTime)
	//{
	//	if (!this->rectangleEditorSplashScreen->isTransparent())
	//		this->rectangleEditorSplashScreen->fadeOut(1 * deltaTime);
	//	if (this->rectangleEditorSplashScreen->getRenderLayer() != (window.getRenderLayerCount() - 1))
	//		this->rectangleEditorSplashScreen->setRenderLayer(window.getRenderLayerCount() - 1);
	//});

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
	auto& bindingClose = *em.createBinding<Binding>	// explaination //
	(												//////////////////
													//
													//	////////
		"bindingClose",								//	// id //
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
		std::vector<int>{ sf::Event::KeyPressed },	//	// types //
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
		std::vector<int>{ sf::Keyboard::Escape },	//	// keys //
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
		std::vector<int>{},							//	// buttons //
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
		std::vector<int>{ sf::Keyboard::LShift },	//	// modifiers //
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
		true,										//	// active //
													//	////////////
													//	//
													//	//	if active, function will automatically
													//	//	be called each update/tick
													//
													//	//////////////////
		this,										//	// parent scene //
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
		[&](float){ window.close(); }				//	// function // @TODO (far from finished)
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
	);

	/////////////////
	// scroll/zoom //
	/////////////////
	//////
	////
	//

	static float currentZoomFactor = 1.f;

	// mouse wheel zoom
	auto& bindingSystemMouseWheelZoom = *em.createBinding<Binding>
	(
		"bindingSystemMouseWheelZoom",
		std::vector<int>{ sf::Event::MouseWheelScrolled },
		std::vector<int>{},
		std::vector<int>{},
		std::vector<int>{ sf::Keyboard::LControl },
		true,
		this,
		[&](float)
		{
			if (auto* binding = em.getBinding("bindingMouseWheelZoom"))
			{
				// zoom in
				if (binding->getMouseScrollDelta() > 0.0f)
				{
					auto view = port->getView();
					currentZoomFactor *= 2.000000f;
					if (currentZoomFactor >= 32.000000f)
					{
						currentZoomFactor = 32.000000f;
					}
					else
					{
						view.setSize(view.getSize().x / 2.000000f, view.getSize().y / 2.000000f);
						view.setCenter(view.getSize().x / 2.000000f, view.getSize().y / 2.0000000f);
						this->rectangleEditorTileCuller->setSize(rectangleEditorTileCuller->getSize().x / 2.000000f, this->rectangleEditorTileCuller->getSize().y / 2.000000f);
						this->rectangleEditorTileCuller->setOrigin(rectangleEditorTileCuller->getSize().x / 2.000000f, this->rectangleEditorTileCuller->getSize().y / 2.000000f);
					}
					this->port->setView(view);
					this->rectangleEditorTileCuller->setPosition(port->getCenter());
				}
				
				// zoom out
				else if (binding->getMouseScrollDelta() < 0.0f)
				{
					auto view = port->getView();
					currentZoomFactor /= 2.000000f;
					if (currentZoomFactor <= 0.062500f)
					{
						currentZoomFactor = 0.062500f;
					}
					else
					{
						view.setSize(view.getSize().x * 2.000000f, view.getSize().y * 2.000000f);
						view.setCenter(view.getSize().x / 2.000000f, view.getSize().y / 2.000000f);
						this->rectangleEditorTileCuller->setSize(this->rectangleEditorTileCuller->getSize().x * 2.000000f, this->rectangleEditorTileCuller->getSize().y * 2.000000f);
						this->rectangleEditorTileCuller->setOrigin(this->rectangleEditorTileCuller->getSize().x / 2.000000f, this->rectangleEditorTileCuller->getSize().y / 2.000000f);
					}
					this->port->setView(view);
					this->rectangleEditorTileCuller->setPosition(port->getCenter());
				}
			}
		}
	);

	bindingSystemMouseWheelZoom.setMouseEnteredRequired(true);

	// TEMP
	auto& bindingSystemScrollLeft = *em.createBinding<Binding>
	(
		"bindingSystemScrollLeft",
		std::vector<int>{ sf::Event::KeyPressed },
		std::vector<int>{ sf::Keyboard::Left },
		std::vector<int>{},
		std::vector<int>{},
		true,
		this,
		[&](float deltaTime)
		{
			const auto modifier = 1200.000f * deltaTime;
			auto viewport = port->getViewport();
			this->port->setView(this->port->getCenter().x - modifier, this->port->getCenter().y, this->port->getSize().x, this->port->getSize().y);
			if (this->port->getCenter().x - (this->port->getSize().x / 2) < 0)
			{
				this->port->setView(port->getSize().x / 2, this->port->getCenter().y, this->port->getSize().x, this->port->getSize().y);
				this->rectangleEditorTileCuller->setPosition(port->getCenter());
			}
			else
				this->rectangleEditorTileCuller->move(sf::Vector2f(-modifier, 0));
			this->port->setViewport(viewport);
		}
	);

	bindingSystemScrollLeft.setMouseEnteredRequired(true);

	auto& bindingSystemScrollRight = *em.createBinding<Binding>
	(
		"bindingSystemScrollRight",
		std::vector<int>{ sf::Event::KeyPressed },
		std::vector<int>{ sf::Keyboard::Right },
		std::vector<int>{},
		std::vector<int>{},
		true,
		this,
		[&](float deltaTime)
		{
			const auto modifier = 1200.000f * deltaTime;
			this->rectangleEditorTileCuller->move(sf::Vector2f(modifier, 0));
			auto viewport = this->port->getViewport();
			this->port->setView(this->port->getCenter().x + modifier, this->port->getCenter().y, this->port->getSize().x, this->port->getSize().y);
			this->port->setViewport(viewport);
		}
	);

	bindingSystemScrollRight.setMouseEnteredRequired(true);

	auto& bindingSystemScrollUp = *em.createBinding<Binding>
	(
		"bindingSystemScrollUp",
		std::vector<int>{ sf::Event::KeyPressed },
		std::vector<int>{ sf::Keyboard::Up },
		std::vector<int>{},
		std::vector<int>{},
		true,
		this,
		[&](float deltaTime)
		{
			const auto modifier = 1200.000f * deltaTime;
			auto viewport = this->port->getViewport();
			this->port->setView(this->port->getCenter().x, this->port->getCenter().y - modifier, this->port->getSize().x, this->port->getSize().y);
			if (this->port->getCenter().y - (this->port->getSize().y / 2) < 0)
			{
				this->port->setView(this->port->getCenter().x, this->port->getSize().y / 2, this->port->getSize().x, this->port->getSize().y);
				this->rectangleEditorTileCuller->setPosition(this->port->getCenter());

			}
			else
				this->rectangleEditorTileCuller->move(sf::Vector2f(0, -modifier));
			this->port->setViewport(viewport);
		}
	);

	bindingSystemScrollUp.setMouseEnteredRequired(true);

	auto& bindingSystemScrollDown = *em.createBinding<Binding>
	(
		"bindingSystemScrollDown",
		std::vector<int>{ sf::Event::KeyPressed },
		std::vector<int>{ sf::Keyboard::Down },
		std::vector<int>{},
		std::vector<int>{},
		true,
		this,
		[&](float deltaTime)
		{
			const auto modifier = 1200.000f * deltaTime;
			this->rectangleEditorTileCuller->move(sf::Vector2f(0, modifier));
			auto viewport = this->port->getViewport();
			this->port->setView(this->port->getCenter().x, this->port->getCenter().y + modifier, this->port->getSize().x, this->port->getSize().y);
			this->port->setViewport(viewport);
		}
	);

	bindingSystemScrollDown.setMouseEnteredRequired(true);

	#pragma endregion EVENT BINDING(S)
}

void EngineEditor::update(float deltaTime)
{
	return;
}

void EngineEditor::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineEditor::getPort() const
{
	return nullptr;
}

#pragma endregion GETTER(S)