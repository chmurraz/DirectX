#include "GameSprite.h"

GameSprite::GameSprite()
{
	//	When the color is set to white, what you see is exactly what the image looks like
	color = D3DCOLOR_ARGB(255, 255, 255, 255);	//	White and 100% visible

	//	We are not initialized yet
	initialized = false;
}

GameSprite::~GameSprite()
{
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	if (tex)
	{
		tex->Release();
		tex = 0;
	}
}

bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	//	Gonna use an extended function here.  Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
	//	Gonna wrap all this in an "ifsucceeded" call

	//	Default and unknown and managed are the standard stuff when you call the CreateTextureFromFile function
	//	See DirectX Tutorial 3 video @ approx 15:00 for more discussion on this function and its parameters
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		std::string s = "There was an issue creating the texture.  Make sure the requested image is available.  Requested image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL);
		return false;
	}

	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There was an issue creating the sprite.", NULL, NULL);
		return false;
	}

	initialized = true;
	return true;
}

bool GameSprite::IsInitialized()
{
	return initialized;
}

void GameSprite::Draw(float gameTime, D3DXVECTOR3 position)
{
	//	if the pointers for the sprite and texture exist, then
	if (sprite && tex)
	{
		//	Alphablend allows for transparent pixels
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(tex, NULL, NULL, &position, color);
		sprite->End();
	}
}


