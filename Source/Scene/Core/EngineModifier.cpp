#include "Scene/Core/EngineModifier.h"
#include "Core/Global.h"

enum class ModifierTab // @TODO update
{
	Tab1,
	Tab2,
	Tab3
};

ModifierTab currentTab = ModifierTab::Tab1;  // @TODO update

EngineModifier::EngineModifier()
	:
	Scene("sceneEngineExplorer", true)
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
		auto& portModifier	= *window.createPort(Port("portModifier", 1.0f - portExplorer.getViewport().width, portExplorer.getViewport().top, portExplorer.getViewport().width, portExplorer.getViewport().height, window.getRenderLayerCount(), true));

		//////////////////////////////
		// create/reference text(s) //
		//////////////////////////////
		//////
		////
		//
	
		auto& textModifierTab1 = *am.createText<Text>("textModifierTab1", &*am.getFont(0), this, &portModifier); // font at index 0 is system regular
		auto& textModifierTab2 = *am.createText<Text>("textModifierTab2", &*am.getFont(0), this, &portModifier); // font at index 0 is system regular
		auto& textModifierTab3 = *am.createText<Text>("textModifierTab3", &*am.getFont(0), this, &portModifier); // font at index 0 is system regular

		///////////////////////////////
		// create/reference shape(s) //
		///////////////////////////////
		//////
		////
		//

		auto& rectangleModifierTab1			= *am.createShape<Rectangle>("rectangleModifierTab1",			sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 0.0f), 0.0f),																				this, &portModifier); // font at index 0 is system regular
		auto& rectangleModifierTab2			= *am.createShape<Rectangle>("rectangleModifierTab2",			sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 1.0f), 0.0f),																				this, &portModifier); // font at index 0 is system regular
		auto& rectangleModifierTab3			= *am.createShape<Rectangle>("rectangleModifierTab3",			sf::Vector2f((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f, (static_cast<float>(window.getSize().y) * 0.025f)),	sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 2.0f), 0.0f),																				this, &portModifier); // font at index 0 is system regular
		auto& rectangleModifierTabConnector = *am.createShape<Rectangle>("rectangleModifierTabConnector",	sf::Vector2f(rectangleModifierTab1.getSize().x - 2, 2),																									sf::Vector2f(((static_cast<float>(window.getSize().x) * portExplorer.getViewport().width) * 0.333f * 0.0f) + 1, rectangleModifierTab1.getPosition().y + rectangleModifierTab1.getSize().y - 1),	this, &portModifier); // font at index 0 is system regular

		#pragma endregion CREATE/REFERENCE
		




		#pragma region SETUP

		//////////
		// port //
		//////////
		//////
		////
		//

		portModifier.getBackground()->setFillColor(sf::Color(35, 35, 35));
		portModifier.getBorder()->setOutlineColor(sf::Color(55, 55, 55));

		//////////////
		// shape(s) //
		//////////////
		//////
		////
		//

		// tab 1
		rectangleModifierTab1.setFillColor(sf::Color(35, 35, 35));
		rectangleModifierTab1.setOutlineColor(sf::Color(55, 55, 55));
		rectangleModifierTab1.setOutlineThickness(-1);

		// tab 1 update functionality
		rectangleModifierTab1.setUpdate([&](float)
		{
			if (rectangleModifierTab1.isLeftClicked())
			{
				rectangleModifierTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portModifier.getViewport().width) * 0.333f * 0.0f) + 1,
					rectangleModifierTab1.getPosition().y + rectangleModifierTab1.getSize().y - 1
				));

				currentTab = ModifierTab::Tab1;
			}
		});

		// tab 2
		rectangleModifierTab2.setFillColor(sf::Color(35, 35, 35));
		rectangleModifierTab2.setOutlineColor(sf::Color(55, 55, 55));
		rectangleModifierTab2.setOutlineThickness(-1);

		// tab 2 update functionality
		rectangleModifierTab2.setUpdate([&](float)
		{
			if (rectangleModifierTab2.isLeftClicked())
			{
				rectangleModifierTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portModifier.getViewport().width) * 0.333f * 1.0f) + 1,
					rectangleModifierTab2.getPosition().y + rectangleModifierTab2.getSize().y - 1
				));

				currentTab = ModifierTab::Tab2;
			}
		});

		// tab 3
		rectangleModifierTab3.setFillColor(sf::Color(35, 35, 35));
		rectangleModifierTab3.setOutlineColor(sf::Color(55, 55, 55));
		rectangleModifierTab3.setOutlineThickness(-1);

		// tab 3 update functionality
		rectangleModifierTab3.setUpdate([&](float)
		{
			if (rectangleModifierTab3.isLeftClicked())
			{
				rectangleModifierTabConnector.setPosition(sf::Vector2f
				(
					((static_cast<float>(window.getSize().x) * portModifier.getViewport().width) * 0.333f * 2.0f) + 1,
					rectangleModifierTab3.getPosition().y + rectangleModifierTab3.getSize().y - 1
				));

				currentTab = ModifierTab::Tab3;
			}
		});

		// tab connector rectangle
		rectangleModifierTabConnector.setFillColor(sf::Color(35, 35, 35));

		/////////////
		// text(s) //
		/////////////
		//////
		////
		//

		constexpr auto characterSizeDivider = 2.0f;

		textModifierTab1.setString("[ Tab 1 ]");
		textModifierTab1.setCharacterSize(rectangleModifierTab1.getSize().y / characterSizeDivider);
		textModifierTab1.setPosition(rectangleModifierTab1.getPosition().x + ((rectangleModifierTab1.getSize().x - textModifierTab1.getGlobalBounds().width) / 2), rectangleModifierTab1.getPosition().y + ((rectangleModifierTab1.getSize().y - textModifierTab1.getGlobalBounds().height) / 2));
		textModifierTab1.setFillColor(sf::Color::White);
		textModifierTab1.setRenderLayer(1);

		textModifierTab2.setString("[ Tab 2 ]");
		textModifierTab2.setCharacterSize(rectangleModifierTab2.getSize().y / characterSizeDivider);
		textModifierTab2.setPosition(rectangleModifierTab2.getPosition().x + ((rectangleModifierTab2.getSize().x - textModifierTab2.getGlobalBounds().width) / 2), rectangleModifierTab2.getPosition().y + ((rectangleModifierTab2.getSize().y - textModifierTab2.getGlobalBounds().height) / 2));
		textModifierTab2.setFillColor(sf::Color::White);
		textModifierTab2.setRenderLayer(1);

		textModifierTab3.setString("[ Tab 3 ]");
		textModifierTab3.setCharacterSize(rectangleModifierTab3.getSize().y / characterSizeDivider);
		textModifierTab3.setPosition(rectangleModifierTab3.getPosition().x + ((rectangleModifierTab3.getSize().x - textModifierTab3.getGlobalBounds().width) / 2), rectangleModifierTab3.getPosition().y + ((rectangleModifierTab3.getSize().y - textModifierTab3.getGlobalBounds().height) / 2));
		textModifierTab3.setFillColor(sf::Color::White);
		textModifierTab3.setRenderLayer(1);

		#pragma endregion SETUP
	});
}