#include "Scene/Core/EngineExplorer.h"
#include "Core/Global.h"

enum class ExplorerTab
{
	Events,
	Scenes,
	Assets
};

ExplorerTab currentTab = ExplorerTab::Events;

EngineExplorer::EngineExplorer()
	:
	Scene("EngineExplorer", true)
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
		auto& portExplorer	= *window.createPort(Port("portExplorer", 0.0f, portMenu.getViewport().height, 0.20f, 1.0f - (portMenu.getViewport().height * 2.0f), window.getRenderLayerCount(), true));

		////////////////////
		// create text(s) //
		////////////////////
		//////
		////
		//
	
		auto& textExplorerEvents = *am.createText<Text>("textExplorerEvents", &*am.getFont(0), this, &portExplorer); // font at index 0 is system regular
		auto& textExplorerScenes = *am.createText<Text>("textExplorerScenes", &*am.getFont(0), this, &portExplorer); // font at index 0 is system regular
		auto& textExplorerAssets = *am.createText<Text>("textExplorerAssets", &*am.getFont(0), this, &portExplorer); // font at index 0 is system regular

		/////////////////////
		// create shape(s) //
		/////////////////////
		//////
		////
		//

		auto& rectangleExplorerEvents		= *am.createShape<Rectangle>("rectangleExplorerEvents", sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 0.0f), 0.0f),																					this, &portExplorer); // font at index 0 is system regular
		auto& rectangleExplorerScenes		= *am.createShape<Rectangle>("rectangleExplorerScenes", sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 1.0f), 0.0f),																					this, &portExplorer); // font at index 0 is system regular
		auto& rectangleExplorerAssets		= *am.createShape<Rectangle>("rectangleExplorerAssets", sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 2.0f), 0.0f),																					this, &portExplorer); // font at index 0 is system regular
		auto& rectangleExplorerTabConnector = *am.createShape<Rectangle>("rectangleExplorerAssets", sf::Vector2f(rectangleExplorerEvents.getSize().x - 2, 2),																								sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 0.0f) + 1, rectangleExplorerEvents.getPosition().y + rectangleExplorerEvents.getSize().y - 1), this, &portExplorer); // font at index 0 is system regular

		#pragma endregion CREATE
		




		#pragma region SETUP

		//////////
		// port //
		//////////
		//////
		////
		//

		portExplorer.getBackground()->setFillColor(sf::Color(35, 35, 35));
		portExplorer.getBorder()->setOutlineColor(sf::Color(55, 55, 55));

		//////////////
		// shape(s) //
		//////////////
		//////
		////
		//

		// events rectangle
		rectangleExplorerEvents.setFillColor(sf::Color(35, 35, 35));
		rectangleExplorerEvents.setOutlineColor(sf::Color(55, 55, 55));
		rectangleExplorerEvents.setOutlineThickness(-1);

		// events rectangle update functionality
		rectangleExplorerEvents.setUpdate([&](float)
		{
			if (rectangleExplorerEvents.isLeftClicked())
			{
				rectangleExplorerTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 0.0f) + 1,
					rectangleExplorerEvents.getPosition().y + rectangleExplorerEvents.getSize().y - 1
				));

				currentTab = ExplorerTab::Events;
			}
		});

		// scenes rectangle
		rectangleExplorerScenes.setFillColor(sf::Color(35, 35, 35));
		rectangleExplorerScenes.setOutlineColor(sf::Color(55, 55, 55));
		rectangleExplorerScenes.setOutlineThickness(-1);

		// scemes rectangle update functionality
		rectangleExplorerScenes.setUpdate([&](float)
		{
			if (rectangleExplorerScenes.isLeftClicked())
			{
				rectangleExplorerTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 1.0f) + 1,
					rectangleExplorerScenes.getPosition().y + rectangleExplorerScenes.getSize().y - 1
				));

				currentTab = ExplorerTab::Scenes;
			}
		});

		// assets rectangle
		rectangleExplorerAssets.setFillColor(sf::Color(35, 35, 35));
		rectangleExplorerAssets.setOutlineColor(sf::Color(55, 55, 55));
		rectangleExplorerAssets.setOutlineThickness(-1);

		// assets rectangle update functionality
		rectangleExplorerAssets.setUpdate([&](float)
		{
			if (rectangleExplorerAssets.isLeftClicked())
			{
				rectangleExplorerTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 2.0f) + 1,
					rectangleExplorerAssets.getPosition().y + rectangleExplorerAssets.getSize().y - 1
				));

				currentTab = ExplorerTab::Assets;
			}
		});

		// tab connector rectangle
		rectangleExplorerTabConnector.setFillColor(sf::Color(35, 35, 35));

		/////////////
		// text(s) //
		/////////////
		//////
		////
		//

		constexpr auto characterSizeDivider = 2.0f;

		textExplorerEvents.setString("[ Events ]");
		textExplorerEvents.setCharacterSize(rectangleExplorerEvents.getSize().y / characterSizeDivider);
		textExplorerEvents.setPosition(rectangleExplorerEvents.getPosition().x + ((rectangleExplorerEvents.getSize().x - textExplorerEvents.getGlobalBounds().width) / 2), rectangleExplorerEvents.getPosition().y + ((rectangleExplorerEvents.getSize().y - textExplorerEvents.getGlobalBounds().height) / 2));
		textExplorerEvents.setFillColor(sf::Color::White);
		textExplorerEvents.setRenderLayer(1);

		textExplorerScenes.setString("[ Scenes ]");
		textExplorerScenes.setCharacterSize(rectangleExplorerScenes.getSize().y / characterSizeDivider);
		textExplorerScenes.setPosition(rectangleExplorerScenes.getPosition().x + ((rectangleExplorerScenes.getSize().x - textExplorerScenes.getGlobalBounds().width) / 2), rectangleExplorerScenes.getPosition().y + ((rectangleExplorerScenes.getSize().y - textExplorerScenes.getGlobalBounds().height) / 2));
		textExplorerScenes.setFillColor(sf::Color::White);
		textExplorerScenes.setRenderLayer(1);

		textExplorerAssets.setString("[ Assets ]");
		textExplorerAssets.setCharacterSize(rectangleExplorerAssets.getSize().y / characterSizeDivider);
		textExplorerAssets.setPosition(rectangleExplorerAssets.getPosition().x + ((rectangleExplorerAssets.getSize().x - textExplorerAssets.getGlobalBounds().width) / 2), rectangleExplorerAssets.getPosition().y + ((rectangleExplorerAssets.getSize().y - textExplorerAssets.getGlobalBounds().height) / 2));
		textExplorerAssets.setFillColor(sf::Color::White);
		textExplorerAssets.setRenderLayer(1);

		#pragma endregion SETUP
	});
}