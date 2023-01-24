#pragma once

#include "Core/Script.h"

class CSharpScript : public Script
{
public: // ctor(s)/dtor(s)

	CSharpScript();
	CSharpScript(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~CSharpScript() override = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) override final;
	virtual void update(float deltaTime) override final;

};