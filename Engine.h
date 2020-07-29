#pragma once

#include "resource.h"
#include "EngineBase.h"
#include "Level.h"

class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void KeyUp(WPARAM wParam);
	void KeyDown(WPARAM wParam);

	void MouseButtonUp(bool left, bool right) override;

	void Logic(double elapsedTime) override;

private:
	Level* level;

	boolean leftPressed;
	boolean rightPressed;
};

