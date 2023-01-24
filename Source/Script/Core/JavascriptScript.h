#pragma once

#include "Core/Script.h"

class JavascriptScript : public Script
{
public: // ctor(s)/dtor(s)

	JavascriptScript();
	JavascriptScript(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~JavascriptScript() override = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) override final;
	virtual void update(float deltaTime) override final;

};

