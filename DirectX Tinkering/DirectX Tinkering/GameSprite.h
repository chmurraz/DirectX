#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <d3dx9.h>
#include <string>

class GameSprite
{
public:
	//	Constructor and Destructor
	GameSprite();
	GameSprite(float x, float y);
	~GameSprite();

	//	Sprite functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);

private:

	//	A sprite in DirectX needs to have a pointer to a texture and to a DirectX sprite
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	D3DXVECTOR3 position;
	D3DCOLOR color;
	bool initialized;

};

#endif