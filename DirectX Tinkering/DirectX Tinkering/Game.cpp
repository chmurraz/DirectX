#include "Game.h"



Game::Game()
{
	//	Constructor
}


Game::~Game()
{
	//	Destructor
	if (player)	{ delete player; player = 0; }
	if (player2) { delete player2; player2 = 0; }
	if (gDevice) { delete gDevice; gDevice = 0; }
}

bool Game::Initialize(HWND hWnd)
{
	gDevice = new GraphicsDevice();
	if (!gDevice->Initialize(hWnd, true))
	{
		return false;
	}

	player = new GameSprite(100, 200);
	if (!player->Initialize(gDevice->device, "PlayerPaper.png", 58, 86))
	{
		return false;
	}

	player->velocity.x = 2;
	player->velocity.y = 1;

	player2 = new GameSprite(80, 200);
	if (!player2->Initialize(gDevice->device, "PlayerPaper.png", 58, 86))
	{
		return false;
	}

	player2->velocity.x = 4;
	player2->velocity.y = -1;

	//	If all are successful, return true.  Determines if game is properly initialized
	return true;
}

void Game::Run()
{
	//	Get game time and update + draw.  Will deal with timers later.
	float gameTime = 0;

	Update(gameTime);
	Draw(gameTime);
}

void Game::Update(float gameTime)
{
	if (player)
		player->Update(gameTime);
	if (player2)
		player2->Update(gameTime);
}

void Game::Draw(float gameTime)
{
	//	Simple RGB value for the background so use XRGB instead ARGB
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();

	//	Draw logic here
	if (player && player->IsInitialized())
		player->Draw(gameTime);
	if (player2 && player2->IsInitialized())
		player2->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}
