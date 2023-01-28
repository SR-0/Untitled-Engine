#pragma once

#include "Core/Scene.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"

class EngineExplorer : public Scene
{
private:

	class ExplorerTab : public Rectangle
	{
	public:

		enum class Type
		{
			Events,
			Scenes,
			Assets
			//Scripts
		}
		explorerTabType;

	public:

		ExplorerTab(const std::string& id, const ExplorerTab::Type& explorerTabType)
			:
			Rectangle(id),
			explorerTabType(explorerTabType)
		{
		}

	};

private: // data

	Port*               port                            = nullptr;
	ExplorerTab*        rectangleExplorerEvents         = nullptr;
	ExplorerTab*        rectangleExplorerScenes         = nullptr;
	ExplorerTab*        rectangleExplorerAssets         = nullptr;
	//ExplorerTab*        rectangleExplorerScripts        = nullptr;
	Rectangle*          rectangleExplorerTabConnector   = nullptr;
	Rectangle*          rectangleExplorerHighlighter    = nullptr;
	Text*               textExplorerEvents              = nullptr;
	Text*               textExplorerScenes              = nullptr;
	Text*               textExplorerAssets              = nullptr;
	Text*               textExplorerTree                = nullptr;
	ExplorerTab::Type   currentExplorerTab              = ExplorerTab::Type::Events;

	// replacement for above tabs
	std::vector<ExplorerTab*> rectangleExplorerTabs   = {};
	std::vector<Text*>        textExplorerTabs        = {};

public: // ctor(s)/dtor(s)

	EngineExplorer() : Scene("sceneEngineExplorer", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

public: // utilitiy

	void updateExplorerTree(float deltaTime);

};