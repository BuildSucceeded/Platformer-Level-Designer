#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObjectBase.h"

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 12
#define TILE_WIDTH 50

class Level : public GameObjectBase
{
public:
	Level();
	~Level();

	void Logic(double elapsedTime) override;
	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget) override;

	void SetPosition(double x, double y);

	void ChangeTile(double x, double y);
	void ResetTile(double x, double y);
	void SaveLevel();

private:
	int levelMatrix[LEVEL_HEIGHT][LEVEL_WIDTH];

	ID2D1Bitmap* tileSetImg;
	ID2D1SolidColorBrush* m_pWhiteBrush;
};

