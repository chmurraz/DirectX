#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "GamePlayObject.h"

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
	GamePlayObject *player;
	GamePlayObject *player2;
};

#endif	/*	GAME_H	*/