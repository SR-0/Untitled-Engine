#include "Core/Engine.h"

int main()
{
	Engine engine;

	while (engine.isRunning())
	{
		engine.update();
		engine.render();
	}
}