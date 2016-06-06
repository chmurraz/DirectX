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

	//	Final two arguments are based on number of pixels per second
	player = new GamePlayObject(100, 200, (float)M_PI_4, 90.0f, 90.0f);
	if (!player->Initialize(gDevice->device, "PlayerPaper.png", 58, 86))
	{
		return false;
	}

	player2 = new GamePlayObject(80, 200, 0, 180.0f, 180.0f);
	if (!player2->Initialize(gDevice->device, "PlayerPaper.png", 58, 86))
	{
		return false;
	}

	gameTime = new GameTime();
	if (!gameTime->Initialize())
	{
		return false;
	}
	
	//	If all are successful, return true.  Determines if game is properly initialized
	return true;
}

void Game::Run()
{
	//	Get game time and update + draw.  Will deal with timers later.
	gameTime->Update();

	Update(gameTime->elapsedGameTime);
	Draw(gameTime->elapsedGameTime);
}

void Game::Update(float gameTime)
{
	//	Tutorial 10:  Use GetASyncKeyState in Game::Update() if your game only has a few keys to be pressed (for a simple shooter, for example)
	//	Otherwise, use GetKeyboardState() function for more complicated inputs in its own class
	
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	//	If "c" key was pressed, for example...
	if (GetAsyncKeyState(67))
	{
		std::string message = "C key is pressed";
		MessageBox(NULL, message.c_str(), NULL, NULL);
	}

	//	Get our sprites and other game logic
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
	if (player)
		player->Draw(gameTime);
	if (player2)
		player2->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}
