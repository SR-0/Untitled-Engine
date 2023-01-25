#pragma once

#include "Core/Scene.h"
#include "Asset/SoundBuffer.h"
#include "Asset/Font.h"
#include "Asset/Text.h"

class EngineSystem : public Scene
{
private: // data

	Port*           portEngineMenu          = nullptr; // global port for engine menu
	Port*           portEngineFooter        = nullptr; // global port for engine footer
	Port*           portEngineExplorer      = nullptr; // global port for engine explorer
	Port*           portEngineModifier      = nullptr; // global port for engine modifier
	Port*           portEngineEditor        = nullptr; // global port for engine editor
	Port*           portEngineAuxiliary     = nullptr; // global port for engine console
	SoundBuffer*    soundBufferEngineOk     = nullptr; // default global sound buffer for ok/good/accepted
	SoundBuffer*    soundBufferEngineCancel = nullptr; // default global sound buffer for cancel/bad/unaccepted
	Font*           fontEngineRegular       = nullptr; // default global font for style type regular
	Font*           fontEngineItalic        = nullptr; // default global font for style type italic
	Font*           fontEngineBold          = nullptr; // default global font for style type bold
	Font*           fontEngineBoldItalic    = nullptr; // default global font for style type italic-bold
	Text*           textEngineResizer       = nullptr; // manipulated angle bracket for resize events

public: // ctor(s)/dtor(s)

	EngineSystem() : Scene("sceneEngineSystem", true, CodeUtilization::VirtualOverride) {}

public: // core

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void terminate() override;

public: // getter(s)

	Port*           getPortEngineMenu() const;
	Port*           getPortEngineFooter() const;
	Port*           getPortEngineExplorer() const;
	Port*           getPortEngineModifier() const;
	Port*           getPortEngineEditor() const;
	Port*           getPortEngineAuxiliary() const;
	SoundBuffer*    getSoundBufferEngineOk() const;
	SoundBuffer*    getSoundBufferEngineCancel() const;
	Font*           getFontEngineRegular() const;
	Font*           getFontEngineItalic() const;
	Font*           getFontEngineBold() const;
	Font*           getFontEngineBoldItalic() const;

};