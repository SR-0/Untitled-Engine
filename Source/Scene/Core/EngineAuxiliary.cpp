#include "Scene/Core/EngineAuxiliary.h"
#include "Scene/Core/EngineSystem.h"
#include "Core/Engine.h"





#pragma endregion CORE

void EngineAuxiliary::initialize()
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

	///////////////////////////////////
	// create/reference general data //
	///////////////////////////////////
	//////
	////
	//

	static std::vector<Text*> lines = std::vector<Text*>();

	/////////////////////////////////////
	// create/reference window port(s) //
	/////////////////////////////////////
	//////
	////
	//
	
	this->port = sm.getScene(0)->as<EngineSystem>()->getPortEngineAuxiliary();

	////////////////////////////////
	// create/reference shapes(s) //
	////////////////////////////////
	//////
	////
	//

	this->rectangleAuxiliaryConsole         = am.createShape<Rectangle>("rectangleAuxiliaryConsole",        sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),   sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 0.0f), 0.0f),                                                                                                     this, &*this->port); // font at index 0 is system regular
	this->rectangleAuxiliaryWarnings        = am.createShape<Rectangle>("rectangleAuxiliaryWarnings",       sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),   sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 1.0f), 0.0f),                                                                                                     this, &*this->port); // font at index 0 is system regular
	this->rectangleAuxiliaryErrors          = am.createShape<Rectangle>("rectangleAuxiliaryErrors",         sf::Vector2f((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),   sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 2.0f), 0.0f),                                                                                                     this, &*this->port); // font at index 0 is system regular
	this->rectangleAuxiliaryTabConnector    = am.createShape<Rectangle>("rectangleAuxiliaryTabConnector",   sf::Vector2f(this->rectangleAuxiliaryConsole->getSize().x - 4, 4),                                                                                      sf::Vector2f(((static_cast<float>(window.getSize().x) * port->getViewport().width) * 0.333f * 0.0f) + 2, this->rectangleAuxiliaryConsole->getPosition().y + this->rectangleAuxiliaryConsole->getSize().y - 2),  this, &*this->port); // font at index 0 is system regular
	this->rectangleConsoleCursor            = am.createShape<Rectangle>("rectangleConsoleCursor",           sf::Vector2f(window.getHeight() / 256, window.getHeight() / 48),                                                                                        sf::Vector2f(global::getFontSize() * global::getUiScale() * 4, global::getFontSize() * global::getUiScale() * 4),                                                                                               this, &*this->port);

	//////////////////////////////
	// create/reference text(s) //
	//////////////////////////////
	//////
	////
	//

	this->textAuxiliaryConsole  = am.createText<Text>("textAuxiliaryConsole",   &*am.getFont(0), this, &*this->port);
	this->textAuxiliaryWarnings = am.createText<Text>("textAuxiliaryWarning",   &*am.getFont(0), this, &*this->port);
	this->textAuxiliaryErrors   = am.createText<Text>("textAuxiliaryErrors",    &*am.getFont(0), this, &*this->port);
	
	#pragma endregion CREATE/REFERENCE





	#pragma region SETUP

	/////////////////////////////////////////
	// setup "lines" with first blank line //
	/////////////////////////////////////////
	//////
	////
	//

	lines.push_back(am.createText<Text>
	(
		"line" + std::to_string(lines.size() + 1),
		&*am.getFont(0),
		this,
		&*this->port
	));

	//////////
	// port //
	//////////
	//////
	////
	//

	this->port->getBackground()->setFillColor(sf::Color(35, 35, 35));
	this->port->getBorder()->setOutlineColor(sf::Color(55, 55, 55));

	this->port->getBackground()->setUpdate([&](float)
	{
		if (this->port->getBackground()->isLeftClicked() && !em.isTextInputEnabled())
		{
			em.setTextInputEnabled(true);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->port->getBackground()->isLeftClicked() && em.isTextInputEnabled())
		{
			em.setTextInputEnabled(false);
		}
	});

	//////////////
	// shape(s) //
	//////////////
	//////
	////
	//

	// events rectangle
	this->rectangleAuxiliaryConsole->setFillColor(sf::Color(35, 35, 35));
	this->rectangleAuxiliaryConsole->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleAuxiliaryConsole->setOutlineThickness(-2);

	// events rectangle update functionality
	this->rectangleAuxiliaryConsole->setUpdate([&](float)
	{
		if (this->rectangleAuxiliaryConsole->isLeftClicked())
		{
			this->rectangleAuxiliaryTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 0.0f) + 2,
				this->rectangleAuxiliaryConsole->getPosition().y + this->rectangleAuxiliaryConsole->getSize().y - 2
			));

			this->auxiliaryTab = AuxiliaryTab::Console;
		}
	});

	// scenes rectangle
	this->rectangleAuxiliaryWarnings->setFillColor(sf::Color(35, 35, 35));
	this->rectangleAuxiliaryWarnings->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleAuxiliaryWarnings->setOutlineThickness(-2);

	// scemes rectangle update functionality
	this->rectangleAuxiliaryWarnings->setUpdate([&](float)
	{
		if (this->rectangleAuxiliaryWarnings->isLeftClicked())
		{
			this->rectangleAuxiliaryTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 1.0f) + 2,
				this->rectangleAuxiliaryWarnings->getPosition().y + this->rectangleAuxiliaryWarnings->getSize().y - 2
			));

			this->auxiliaryTab = AuxiliaryTab::Warnings;
		}
	});

	// assets rectangle
	this->rectangleAuxiliaryErrors->setFillColor(sf::Color(35, 35, 35));
	this->rectangleAuxiliaryErrors->setOutlineColor(sf::Color(55, 55, 55));
	this->rectangleAuxiliaryErrors->setOutlineThickness(-2);

	// assets rectangle update functionality
	this->rectangleAuxiliaryErrors->setUpdate([&](float)
	{
		if (this->rectangleAuxiliaryErrors->isLeftClicked())
		{
			this->rectangleAuxiliaryTabConnector->setPosition(sf::Vector2f
			(
				((static_cast<float>(window.getSize().x) * this->port->getViewport().width) * 0.333f * 2.0f) + 2,
				this->rectangleAuxiliaryErrors->getPosition().y + this->rectangleAuxiliaryErrors->getSize().y - 2
			));

			this->auxiliaryTab = AuxiliaryTab::Errors;
		}
	});

	// tab connector rectangle
	this->rectangleAuxiliaryTabConnector->setFillColor(sf::Color(35, 35, 35));

	// cursor basics
	this->rectangleConsoleCursor->setRenderLayer(window.getRenderLayerCount() - 1);
	this->rectangleConsoleCursor->setFillColor(sf::Color(100, 100, 100, 100));

	// cursor auto update
	this->rectangleConsoleCursor->setUpdate([&](float deltaTime)
	{
		static float		timeSinceLastBlink	= 0.0f;
		static const float	interval			= 0.3f;

		timeSinceLastBlink += deltaTime;

		if (timeSinceLastBlink >= interval)
		{
			if (this->rectangleConsoleCursor->isTransparent())
				this->rectangleConsoleCursor->setOpaque();
			else
				this->rectangleConsoleCursor->setTransparent();
			timeSinceLastBlink = 0.0f;
		}
	});

	///////////////////
	// setup text(s) //
	///////////////////
	//////
	////
	//

	//// header
	//this->textConsoleHeader->setString("CONSOLE");
	//this->textConsoleHeader->setActive(true);
	//this->textConsoleHeader->setRenderLayer(window.getRenderLayerCount() - 1);
	//this->textConsoleHeader->setCharacterSize(window.getHeight() / 32);
	//this->textConsoleHeader->setOrigin(this->textConsoleHeader->getGlobalBounds().width / 2, this->textConsoleHeader->getGlobalBounds().height / 2);
	//this->textConsoleHeader->setPosition((window.getSize().x * this->port->getViewport().width) / 2, (window.getHeight() * this->port->getViewport().height) / 32);
	//this->textConsoleHeader->setFillColor(sf::Color(255, 255, 255, 255));
	//this->textConsoleHeader->setOutlineColor(sf::Color(35, 35, 35, 255));
	//this->textConsoleHeader->setOutlineThickness(4);

	// user
	lines[lines.size() - 1]->setString("");
	lines[lines.size() - 1]->setActive(true);
	lines[lines.size() - 1]->setRenderLayer(window.getRenderLayerCount() - 1);
	lines[lines.size() - 1]->setCharacterSize(global::getFontSize() * global::getUiScale());
	lines[lines.size() - 1]->setPosition(global::getFontSize() * global::getUiScale() * 4, global::getFontSize() * global::getUiScale() * 4);
	lines[lines.size() - 1]->setFillColor(sf::Color(255, 255, 255, 255));
	lines[lines.size() - 1]->setOutlineColor(sf::Color(35, 35, 35, 255));
	lines[lines.size() - 1]->setOutlineThickness(2);

	/////////////
	// text(s) //
	/////////////
	//////
	////
	//

	constexpr auto characterSizeDivider = 96.0f;

	this->textAuxiliaryConsole->setString("[ Console ]");
	this->textAuxiliaryConsole->setCharacterSize(global::getFontSize()* global::getUiScale());
	this->textAuxiliaryConsole->setPosition(this->rectangleAuxiliaryConsole->getPosition().x + ((this->rectangleAuxiliaryConsole->getSize().x - this->textAuxiliaryConsole->getGlobalBounds().width) / 2), this->rectangleAuxiliaryConsole->getPosition().y + ((this->rectangleAuxiliaryConsole->getSize().y - this->textAuxiliaryConsole->getGlobalBounds().height) / 2));
	this->textAuxiliaryConsole->setFillColor(sf::Color::White);
	this->textAuxiliaryConsole->setRenderLayer(1);

	this->textAuxiliaryWarnings->setString("[ Warnings ]");
	this->textAuxiliaryWarnings->setCharacterSize(global::getFontSize()* global::getUiScale());
	this->textAuxiliaryWarnings->setPosition(this->rectangleAuxiliaryWarnings->getPosition().x + ((this->rectangleAuxiliaryWarnings->getSize().x - this->textAuxiliaryWarnings->getGlobalBounds().width) / 2), this->rectangleAuxiliaryWarnings->getPosition().y + ((this->rectangleAuxiliaryWarnings->getSize().y - this->textAuxiliaryWarnings->getGlobalBounds().height) / 2));
	this->textAuxiliaryWarnings->setFillColor(sf::Color::White);
	this->textAuxiliaryWarnings->setRenderLayer(1);

	this->textAuxiliaryErrors->setString("[ Errors ]");
	this->textAuxiliaryErrors->setCharacterSize(global::getFontSize()* global::getUiScale());
	this->textAuxiliaryErrors->setPosition(this->rectangleAuxiliaryErrors->getPosition().x + ((this->rectangleAuxiliaryErrors->getSize().x - this->textAuxiliaryErrors->getGlobalBounds().width) / 2), this->rectangleAuxiliaryErrors->getPosition().y + ((this->rectangleAuxiliaryErrors->getSize().y - this->textAuxiliaryErrors->getGlobalBounds().height) / 2));
	this->textAuxiliaryErrors->setFillColor(sf::Color::White);
	this->textAuxiliaryErrors->setRenderLayer(1);

	// start out with console and input up
	//em.setTextInputEnabled(true);

	#pragma endregion SETUP





	#pragma region EVENT BINDING(S)

	///////////////////////
	// console toggle on //
	///////////////////////
	//////
	////
	//

	static auto toggleOff = [&] // used at end on first setup/initialization
	{
		//this->setActive(false);
		//this->setRenderEnabled(false);
		//this->port->setActive(false);
		em.setTextInputEnabled(false);
	};

	em.createBinding<Binding>
	(
		"conosle-toggle-on",
		std::vector<int>{ sf::Event::KeyPressed },
		std::vector<int>{ sf::Keyboard::Tilde },
		std::vector<int>{},
		std::vector<int>{},
		true,
		nullptr, // this binding will happen rather console scene is active or not
		[&](float)
		{
			//this->setActive(true);
			//this->setRenderEnabled(true);
			//this->port->setActive(true);
			em.setTextInputEnabled(true);
		}
	);

	/////////////////////////////
	// text entered/toggle off //
	/////////////////////////////
	//////
	////
	//

	em.createBinding<Binding>
	(
		"console-text-entered-toggle-off",
		std::vector<int>{ sf::Event::TextEntered },
		std::vector<int>{},
		std::vector<int>{},
		std::vector<int>{},
		true,
		this,
		[&](float)
		{
			if (auto* binding = em.getBinding("console-text-entered-toggle-off"))
			{
				// toggle off and return
				if (binding->getUnicode() == '`')
				{
					toggleOff();
					return;
				}
				
				// handle text entered
				auto& text = *lines[lines.size() - 1];
				text.setString(text.getString() + char(binding->getUnicode()));
				this->rectangleConsoleCursor->setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
			}
		}
	);

	///////////////////////////////////////////
	// console entered input/command parsing //
	///////////////////////////////////////////
	//////
	////
	//

	em.createBinding<Binding>
	(
		"console-input-enter",
		std::vector<int>{ sf::Event::TextEntered },
		std::vector<int>{},
		std::vector<int>{},
		std::vector<int>{ sf::Keyboard::Enter },
		true,
		this,
		[&](float)
		{
			auto command = std::string(lines[lines.size() - 1]->getString());
			auto cleared = false;
			auto invalid = false;

			try
			{
				//////////
				// help //
				//////////
				//////
				////
				//

				if (command.substr(0, 4) == "help")
				{
					// @TODO
				}

				///////////////
				// getter(s) //
				///////////////
				//////
				////
				//

				else if (command.substr(0, 3) == "get")
				{
					// @TODO
				}

				///////////////
				// setter(s) //
				///////////////
				//////
				////
				//

				else if (command.substr(0, 3) == "set")
				{
					// resolution
					if (command.substr(4, 10) == "resolution")
					{
						debug::print("\"", command.substr(4, 10), "\"\n");

						std::string temp = command.substr(14, command.size());

						auto width = std::stoi(temp.substr(0, temp.find('x')));
						auto height = std::stoi(temp.substr(temp.find('x') + 1, temp.size()));
						window.setSize(width, height);
						//window.resizePorts(); @TODO
					}

					// max ticks per second
					else if (command.substr(4, 3) == "tps")
					{
						debug::print("\"", command.substr(4, 3), "\"\n");

						global::setMaxTicksPerSecond(std::stoi(command.substr(8, command.size())));
						debug::print("tps = ", global::getMaxTicksPerSecond(), "\n");
						debug::print("fps = ", global::getMaxFramesPerSecond(), "\n");
					}

					// max frames per second
					else if (command.substr(4, 3) == "fps")
					{
						debug::print("\"", command.substr(4, 3), "\"\n");

						auto fps = std::stoi(command.substr(8, command.size()));
						global::setMaxFramesPerSecond(fps);
						debug::print("tps = ", global::getMaxTicksPerSecond(), "\n");
						debug::print("fps = ", global::getMaxFramesPerSecond(), "\n");
					}

					// invalid input/command
					else
					{
						invalid = true;
					}
				}

				////////////////////////
				// utility/core/other //
				////////////////////////
				//////
				////
				//

				// clear console strings
				else if (command.substr(0, 5) == "clear")
				{
					while (lines.size() != 1)
					{
						auto* text = lines[lines.size() - 1];
						am.removeText(text->getId());
						lines.pop_back();
					}

					auto* text = lines[lines.size() - 1];
					text->setString("");
					rectangleConsoleCursor->setPosition(text->getPosition().x + text->getGlobalBounds().width, text->getPosition().y);
					cleared = true;
				}

				// quit/close/exit engine/game
				else if (command.substr(0, 4) == "quit") // @TODO save condition
				{
					window.close();
				}

				// quit/close/exit engine/game
				else if (command.substr(0, 5) == "close") // @TODO save condition
				{
					window.close();
				}

				// quit/close/exit engine/game
				else if (command.substr(0, 4) == "exit") // @TODO save condition
				{
					window.close();
				}
				
				////////////////////////////////////////
				// anything else besides a blank line //
				////////////////////////////////////////
				//////
				////
				//

				else if (command != "")
				{
					invalid = true;
				}
			}
			catch (const std::exception& exception)
			{
				invalid = true;
				debug::print(exception.what());
			}

			if (invalid)
			{
				lines[lines.size() - 1]->setString(std::string(command + " [INVALID CONSOLE COMMAND] "));
			}

			if (!cleared)
			{
				lines.push_back(am.createText<Text>
				(
					"line" + std::to_string(lines.size() + 1),
					&*am.getFont(0),
					this,
					&*this->port
				));

				// user
				auto& text = *lines[lines.size() - 1];
				text.setString("");
				text.setActive(true);
				text.setRenderLayer(window.getRenderLayerCount() - 1);
				text.setCharacterSize(global::getFontSize()* global::getUiScale());
				text.setPosition(global::getFontSize() * global::getUiScale() * 4, (this->rectangleConsoleCursor->getPosition().y + this->rectangleConsoleCursor->getSize().y));
				text.setFillColor(sf::Color(255, 255, 255, 255));
				text.setOutlineColor(sf::Color(35, 35, 35, 255));
				text.setOutlineThickness(2);
				this->rectangleConsoleCursor->setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
			}
		}
	);

	////////////////////////
	// console input "UP" //
	////////////////////////
	//////
	////
	//

	em.createBinding<Binding>
	(
		"console-input-up",
		std::vector<int>{ sf::Event::TextEntered },
		std::vector<int>{},
		std::vector<int>{},
		std::vector<int>{ sf::Keyboard::Up },
		true,
		this,
		[&](float)
		{
			if (lines.size() >= 2)
			{
				auto& text = *lines[lines.size() - 1];
				text.setString(lines[lines.size() - 2]->getString());
				this->rectangleConsoleCursor->setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
			}
		}
	);

	///////////////////////////////
	// console input "BACKSPACE" //
	///////////////////////////////
	//////
	////
	//

	em.createBinding<Binding>
	(
		"console-input-backspace",
		std::vector<int>{ sf::Event::TextEntered },
		std::vector<int>{},
		std::vector<int>{},
		std::vector<int>{ sf::Keyboard::Backspace },
		true,
		this,
		[&](float)
		{
			if (auto* binding = em.getBinding("console-input-backspace"))
			{
				if (lines.size() > 0)
				{
					auto& text = *lines[lines.size() - 1];

					if ((text.getString().getSize() == 0) && (lines.size() > 1))
					{
						lines.erase(lines.begin() + lines.size() - 1);
						this->rectangleConsoleCursor->setPosition(lines[lines.size() - 1]->getPosition().x + lines[lines.size() - 1]->getGlobalBounds().width, lines[lines.size() - 1]->getPosition().y);
					}
					else
					{
						text.setString(text.getString().substring(0, text.getString().getSize() - 1));
						this->rectangleConsoleCursor->setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
					}
				}
			}
		}
	);

	#pragma endregion EVENT BINDING(S)
}

void EngineAuxiliary::update(float deltaTime)
{
	return;
}

void EngineAuxiliary::terminate()
{
	global::getAssetManager()->removeAssets(this);
}

#pragma endregion CORE





#pragma region GETTER(S)

Port* EngineAuxiliary::getPort() const
{
	return this->port;
}

#pragma endregion GETTER(S)