#pragma once

#include "Core/Scene.h"
#include "Asset/Sound.h"
#include "Asset/Texture.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"
#include "Asset/Tilemap.h"

class EngineEditor : public Scene
{
private: // data

	Port*					port						= nullptr;
	Sound*					soundEditorOk				= nullptr;
	Sound*					soundEditorCancel			= nullptr;
	Texture*				textureEditorTiles			= nullptr;
	Rectangle*				rectangleEditorTileCuller	= nullptr;
	Rectangle*				rectangleEditorTabConnector	= nullptr;
	std::vector<Rectangle*>	rectangleEditorTabs			= std::vector<Rectangle*>{};
	std::vector<Text*>		textEditorTabs				= std::vector<Text*>{};
	Tilemap*				tilemapEditor				= nullptr;

public:  // ctor(s)/dtor(s)

	EngineEditor() : Scene("EngineEditor", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

};