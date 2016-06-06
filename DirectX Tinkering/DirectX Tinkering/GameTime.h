#ifndef GAMETIME_H
#define GAMETIME_H

#include <Windows.h>	//	gives frequency and current value of tick counter from Windows API

class GameTime
{
public:
	GameTime();
	~GameTime();
	float elapsedGameTime;
	float totalGameTime;
	
	bool Initialize();
	void Update();
private:
	LONGLONG start;
	float frequencySeconds;
};

#endif