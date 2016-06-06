#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "GameSprite.h"

class Game
{
public:
	//	Constructor and Destructor
	Game();
	~Game();

	//	Game Function
	bool Initialize(HWND hWnd);
	void Run();
	void Update(float gameTime);
	void Draw(float gameTime);

private:
	GraphicsDevice *gDevice;
	GameSprite *player;
	GameSprite *player2;
};

#endif	/*	GAME_H	*/