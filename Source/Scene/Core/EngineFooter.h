#pragma once

#include "Core/Scene.h"
#include "Asset/Text.h"

class EngineFooter : public Scene
{
private: // data

	Port* port                  = nullptr;
	Text* textTicksPerSecond    = nullptr;
	Text* textFramesPerSecond   = nullptr; // @TODO

public: // ctor(s)/dtor(s)

	EngineFooter() : Scene("sceneEngineFooter", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port* getPort() const;
};