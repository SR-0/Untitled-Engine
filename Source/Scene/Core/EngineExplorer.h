#pragma once

#include "Core/Scene.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"

class EngineExplorer : public Scene
{
private: // data

	Port*		port							= nullptr;
	Rectangle*	rectangleExplorerEvents			= nullptr;
	Rectangle*	rectangleExplorerScenes			= nullptr;
	Rectangle*	rectangleExplorerAssets			= nullptr;
	Rectangle*	rectangleExplorerTabConnector	= nullptr;
	Text*		textExplorerEvents				= nullptr;
	Text*		textExplorerScenes				= nullptr;
	Text*		textExplorerAssets				= nullptr;
	ExplorerTab explorerTab						= ExplorerTab::Events;

public: // ctor(s)/dtor(s)

	EngineExplorer() : Scene("sceneEngineExplorer", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

};