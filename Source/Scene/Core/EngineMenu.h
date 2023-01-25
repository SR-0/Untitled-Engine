#pragma once

#include "Core/Scene.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"

class EngineMenu : public Scene
{
private: // data

	Port*       port                = nullptr;
	Rectangle*  rectangleMenuClose  = nullptr;
	Text*       textMenuClose       = nullptr;

public: // ctor(s)/dtor(s)

	EngineMenu() : Scene("sceneEngineMenu", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

};