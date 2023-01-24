#pragma once

#include "Core/Scene.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"

class EngineModifier : public Scene
{
private: // data

	Port*		port							= nullptr;
	Rectangle*	rectangleModifierTab1			= nullptr;
	Rectangle*	rectangleModifierTab2			= nullptr;
	Rectangle*	rectangleModifierTab3			= nullptr;
	Rectangle*	rectangleModifierTabConnector	= nullptr;
	Text*		textModifierTab1				= nullptr;
	Text*		textModifierTab2				= nullptr;
	Text*		textModifierTab3				= nullptr;
	ModifierTab modiferTab						= ModifierTab::Tab1;

public: // dtor(s)/ctor(s)

	EngineModifier() : Scene("EngineModifier", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

};