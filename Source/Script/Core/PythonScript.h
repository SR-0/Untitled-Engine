#pragma once

#include "Core/Script.h"

class PythonScript : public Script
{
public: // ctor(s)/dtor(s)

	PythonScript();
	PythonScript(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~PythonScript() override = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) override final;
	virtual void update(float deltaTime) override final;

};

