#pragma once

#include "Core/Scene.h"
#include "Asset/SoundBuffer.h"
#include "Asset/Font.h"
#include "Asset/Rectangle.h"
#include "Asset/Text.h"

class EngineAuxiliary : public Scene
{
private: // data

	Port*			port							= nullptr;
	Rectangle*		rectangleAuxiliaryConsole		= nullptr;
	Rectangle*		rectangleAuxiliaryWarnings		= nullptr;
	Rectangle*		rectangleAuxiliaryErrors		= nullptr;
	Rectangle*		rectangleAuxiliaryTabConnector	= nullptr;
	Rectangle*		rectangleConsoleCursor			= nullptr;
	Text*			textAuxiliaryConsole			= nullptr;
	Text*			textAuxiliaryWarnings			= nullptr;
	Text*			textAuxiliaryErrors				= nullptr;
	AuxiliaryTab	auxiliaryTab					= AuxiliaryTab::Console;

public: // ctor(s)/dtor(s)

	EngineAuxiliary() : Scene("EngineConsole", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;

};