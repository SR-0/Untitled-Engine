#include "Scene/Core/EngineConsole.h"
#include "Core/Global.h"
#include "Core/Engine.h"

EngineConsole::EngineConsole()
	:
	Scene("sceneEngineConsole", true)
{
	auto& window	= *global::getWindow();
	auto& cm		= *global::getClockManager();
	auto& em		= *global::getEventManager();
	auto& sm		= *global::getSceneManager();
	auto& am		= *global::getAssetManager();

	this->setInitialize([&]
	{
		#pragma region CREATE/REFERENCE

		///////////////////////////////////
		// create/reference general data //
		///////////////////////////////////
		//////
		////
		//

		static std::vector<Text*> lines = std::vector<Text*>();

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

		////////////////////////////////
		// create/reference shapes(s) //
		////////////////////////////////
		//////
		////
		//

		auto& rectangleConsolePanel			= *am.createShape<Rectangle>("rectangleConsolePanel",		sf::Vector2f(window.getWidth() / 1.5, window.getHeight() / 1.5),	sf::Vector2f((window.getWidth() - (window.getWidth() / 1.5)) / 2, (window.getHeight() - (window.getHeight() / 1.5)) / 2),	this, nullptr);
		auto& rectangleConsoleCursor		= *am.createShape<Rectangle>("rectangleConsoleCursor",		sf::Vector2f(window.getHeight() / 256, window.getHeight() / 48),	sf::Vector2f(rectangleConsolePanel.getPosition() + sf::Vector2f(window.getWidth() / 16, window.getWidth() / 16)),			this, nullptr);
		//auto& rectangleConsoleHighlighter	= *am.createShape<Rectangle>("rectangleConsoleHighlighter", sf::Vector2f(window.getHeight() / 96, window.getHeight() / 48),		sf::Vector2f(rectangleConsolePanel.getPosition() + sf::Vector2f(window.getWidth() / 16, window.getWidth() / 16)),			this, nullptr);

		//////////////////////////////
		// create/reference text(s) //
		//////////////////////////////
		//////
		////
		//

		auto& textHeader	= *am.createText<Text>("textHeader",	&fontUnispaceBold, this, nullptr);
		//auto& textDetails	= *am.createText<Text>("textDetails",	&fontUnispaceBold, this, nullptr);
		
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
			&fontUnispace,
			this,
			nullptr
		));

		/////////////////////
		// setup shapes(s) //
		/////////////////////
		//////
		////
		//

		// panel basics
		rectangleConsolePanel.setRenderLayer(window.getRenderLayerCount() - 1);
		rectangleConsolePanel.setFillColor(sf::Color(0, 0, 0, 190));
		rectangleConsolePanel.setOutlineColor(sf::Color(255, 255, 255, 255));
		rectangleConsolePanel.setOutlineThickness(-2);

		// panel auto update
		rectangleConsolePanel.setUpdate([&](float deltaTime)
		{
			auto		modifier	= 96.0f * deltaTime;
			const auto	next		= rectangleConsolePanel.getOutlineColor().a + modifier;

			if (next >= 255.0f)
				modifier = -abs(modifier);
			else if (next <= 0.0f)
				modifier = abs(modifier);

			rectangleConsolePanel.setOutlineColor(sf::Color
			(
				rectangleConsolePanel.getOutlineColor().r,
				rectangleConsolePanel.getOutlineColor().g,
				rectangleConsolePanel.getOutlineColor().b,
				rectangleConsolePanel.getOutlineColor().a + modifier
			));
		});

		// cursor basics
		rectangleConsoleCursor.setRenderLayer(window.getRenderLayerCount() - 1);
		rectangleConsoleCursor.setFillColor(sf::Color(100, 100, 100, 100));

		// cursor auto update
		rectangleConsoleCursor.setUpdate([&](float deltaTime)
		{
			static float		timeSinceLastBlink	= 0.0f;
			static const float	interval			= 0.3f;

			timeSinceLastBlink += deltaTime;

			if (timeSinceLastBlink >= interval)
			{
				if (rectangleConsoleCursor.isTransparent())
					rectangleConsoleCursor.setOpaque();
				else
					rectangleConsoleCursor.setTransparent();
				timeSinceLastBlink = 0.0f;
			}
		});

		///////////////////
		// setup text(s) //
		///////////////////
		//////
		////
		//

		// header
		textHeader.setString("CONSOLE");
		textHeader.setActive(true);
		textHeader.setRenderLayer(window.getRenderLayerCount() - 1);
		textHeader.setCharacterSize(window.getHeight() / 32);
		textHeader.setOrigin(textHeader.getGlobalBounds().width / 2, textHeader.getGlobalBounds().height / 2);
		textHeader.setPosition(rectangleConsolePanel.getPosition().x + (rectangleConsolePanel.getSize().x / 2), rectangleConsolePanel.getPosition().y + (rectangleConsolePanel.getHeight() / 32));
		textHeader.setFillColor(sf::Color(255, 255, 255, 255));

		// user
		lines[lines.size() - 1]->setString("");
		lines[lines.size() - 1]->setActive(true);
		lines[lines.size() - 1]->setRenderLayer(window.getRenderLayerCount() - 1);
		lines[lines.size() - 1]->setCharacterSize(window.getHeight() / 64);
		lines[lines.size() - 1]->setPosition(rectangleConsolePanel.getPosition() + sf::Vector2f(window.getWidth() / 16, window.getWidth() / 16));
		lines[lines.size() - 1]->setFillColor(sf::Color(255, 255, 255, 255));

		// start out with console and input up
		em.setTextInputEnabled(true);

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
			this->setActive(false);
			this->setRenderEnabled(false);
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
				this->setActive(true);
				this->setRenderEnabled(true);
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
					rectangleConsoleCursor.setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
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

							Engine::setMaxTicksPerSecond(std::stoi(command.substr(8, command.size())));
							debug::print("tps = ", Engine::getMaxTicksPerSecond(), "\n");
							debug::print("fps = ", Engine::getMaxFramesPerSecond(), "\n");
						}

						// max frames per second
						else if (command.substr(4, 3) == "fps")
						{
							debug::print("\"", command.substr(4, 3), "\"\n");

							auto fps = std::stoi(command.substr(8, command.size()));
							Engine::setMaxFramesPerSecond(fps);
							debug::print("tps = ", Engine::getMaxTicksPerSecond(), "\n");
							debug::print("fps = ", Engine::getMaxFramesPerSecond(), "\n");
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
						rectangleConsoleCursor.setPosition(text->getPosition().x + text->getGlobalBounds().width, text->getPosition().y);
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
						&fontUnispace,
						this
					));

					// user
					auto& text = *lines[lines.size() - 1];
					text.setString("");
					text.setActive(true);
					text.setRenderLayer(window.getRenderLayerCount() - 1);
					text.setCharacterSize(window.getHeight() / 64);
					text.setPosition(rectangleConsolePanel.getPosition().x + (window.getWidth() / 16), (rectangleConsoleCursor.getPosition().y + rectangleConsoleCursor.getSize().y));
					text.setFillColor(sf::Color(255, 255, 255, 255));
					rectangleConsoleCursor.setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
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
					rectangleConsoleCursor.setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
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
							rectangleConsoleCursor.setPosition(lines[lines.size() - 1]->getPosition().x + lines[lines.size() - 1]->getGlobalBounds().width, lines[lines.size() - 1]->getPosition().y);
						}
						else
						{
							text.setString(text.getString().substring(0, text.getString().getSize() - 1));
							rectangleConsoleCursor.setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y);
						}
					}
				}
			}
		);

		toggleOff();

		#pragma endregion EVENT BINDING(S)
	});
}
