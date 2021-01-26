#include "Settings.h"
#include "Level.h"

Level::Level() {
	
	// Default nothing map
	for (int i = 0; i < LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < LEVEL_WIDTH; j++)
		{
			levelMatrix[i][j] = -1;
		}
	}

	// Load map from file
	std::ifstream myfile("level.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < LEVEL_HEIGHT; i++)
		{
			for (int j = 0; j < LEVEL_WIDTH; j++)
			{
				myfile >> levelMatrix[i][j];
			}
		}
	}

	position.x = 0;
	position.y = 0;
}

Level::~Level() {
}

void Level::Logic(double elapsedTime)
{
	
}

void Level::ChangeTile(double x, double y)
{
	int fx = (x + position.x) / TILE_WIDTH;
	int fy = y / TILE_WIDTH;

	levelMatrix[fy][fx] ++;
}

void Level::ResetTile(double x, double y)
{
	int fx = (x + position.x) / TILE_WIDTH;
	int fy = y / TILE_WIDTH;

	levelMatrix[fy][fx] = -1;
}

void Level::SaveLevel()
{
	FILE* (file);

	std::ofstream myfile("level.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < LEVEL_HEIGHT; i++)
		{
			for (int j = 0; j < LEVEL_WIDTH; j++)
			{
				myfile << levelMatrix[i][j] << " ";
			}
			myfile << "\n";
		}
		myfile.close();
	}
}

void Level::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	if (tileSetImg == NULL)
	{
		tileSetImg = engine->LoadImageW(L"tileset.png");
	}
	if (m_pWhiteBrush == NULL) {
		m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&m_pWhiteBrush
		);
	}

	for (int i = 0; i < LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < LEVEL_WIDTH; j++)
		{
			if ((j + 1) * TILE_WIDTH >= position.x && j * TILE_WIDTH < position.x + RESOLUTION_X) {
				
				D2D1_RECT_F rectangle1 = D2D1::RectF(
					j * TILE_WIDTH - position.x, i * TILE_WIDTH,
					(j + 1) * TILE_WIDTH - position.x, (i + 1) * TILE_WIDTH
				);

				if (levelMatrix[i][j] != -1) {

					int posY = levelMatrix[i][j] / 7;
					int posX = levelMatrix[i][j] % 7;

					D2D1_RECT_F rectangle2 = D2D1::RectF(
						posX * TILE_WIDTH, posY * TILE_WIDTH,
						posX * TILE_WIDTH + TILE_WIDTH - 1, posY * TILE_WIDTH + TILE_WIDTH - 1
					);

					m_pRenderTarget->DrawBitmap(tileSetImg, rectangle1, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rectangle2);
				}
				m_pRenderTarget->DrawRectangle(rectangle1, m_pWhiteBrush);
			}
		}
	}
}

void Level::SetPosition(double x, double y)
{
	position.x = x;
	if (position.x < 0)
		position.x = 0;
	if (position.x > LEVEL_WIDTH * TILE_WIDTH - RESOLUTION_X)
		position.x = LEVEL_WIDTH * TILE_WIDTH - RESOLUTION_X;
	position.y = y;
}