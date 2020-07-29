#include "framework.h"
#include "Settings.h"
#include "EngineBase.h"
#include "Engine.h"
#include "Level.h"

Engine::Engine()
{
    level = new Level();
    AddGameObject(level);

    leftPressed = false;
    rightPressed = false;
}

Engine::~Engine()
{
}

void Engine::MouseButtonUp(bool left, bool right)
{
    if (left) {
        level->ChangeTile(mousePosition.x, mousePosition.y);
    }
    if (right) {
        level->ResetTile(mousePosition.x, mousePosition.y);
    }
}

void Engine::KeyUp(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = false;
    if (wParam == VK_RIGHT)
        rightPressed = false;

    if (wParam == VK_F5)
        level->SaveLevel();

    if (wParam >= '0' && wParam <= '9')
    {
        for (int i = 0; i <= wParam - '0'; i++)
            level->ChangeTile(mousePosition.x, mousePosition.y);
    }
}

void Engine::KeyDown(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = true;
    if (wParam == VK_RIGHT)
        rightPressed = true;
}

void Engine::Logic(double elapsedTime)
{
    EngineBase::Logic(elapsedTime);

    // This is the logic part of the engine. Add your game logic here.
    // It runs every frame and it receives the elapsed time between the last frame and this one, in seconds.
    // Use this value for a smooth and consistent movement, regardless of the CPU or graphics speed

    if (leftPressed) {
        Point2D oldPosition = level->GetPosition();
        level->SetPosition(oldPosition.x - elapsedTime * 200, oldPosition.y);
    }
    if (rightPressed) {
        Point2D oldPosition = level->GetPosition();
        level->SetPosition(oldPosition.x + elapsedTime * 200, oldPosition.y);
    }
}