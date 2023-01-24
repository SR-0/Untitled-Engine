#pragma once

#include "Core/Script.h"

class ChaiscriptScript : public Script
{
public: // ctor(s)/dtor(s)

	ChaiscriptScript();
	ChaiscriptScript(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~ChaiscriptScript() override = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) override final;
	virtual void update(float deltaTime) override final;

};

