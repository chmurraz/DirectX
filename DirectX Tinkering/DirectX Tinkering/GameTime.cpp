#include "GameTime.h"

GameTime::GameTime()
{
}


GameTime::~GameTime()
{
}

bool GameTime::Initialize()
{
	LARGE_INTEGER i;
	
	//	Get frequency from counter.  The frequency cannot change while the system is running, so we only need to do this once.
	if (!QueryPerformanceFrequency(&i))
		return false;

	//	Gives us the number of ticks per second
	frequencySeconds = (float)(i.QuadPart);

	//	Gets the current value of the counter
	QueryPerformanceCounter(&i);
	start = i.QuadPart;
	totalGameTime = 0;
	elapsedGameTime = 0;

	return true;

	return false;
}

void GameTime::Update()
{
	LARGE_INTEGER i;

	QueryPerformanceCounter(&i);
	elapsedGameTime = (float)(i.QuadPart - start) / frequencySeconds;

	start = i.QuadPart;
	totalGameTime += elapsedGameTime;
}
