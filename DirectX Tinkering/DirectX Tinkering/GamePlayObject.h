#ifndef GAMEPLAYOBJECT_H
#define GAMEPLAYOBJECT_H

#define _USE_MATH_DEFINES	//	this is needed when you include cmath
#include <cmath>
#include "GameSprite.h"		//	need access to the sprite and texture data
#include <string>			//	for informational data

enum class ObjectStatus { Active, Dying, Dead };

class GamePlayObject
{
public:
	GamePlayObject(float x, float y, float rotation, float speed, float maxSpeed);
	~GamePlayObject();

	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);

	ObjectStatus GetStatus() const;		//	This is the correct way to use getters... why const?

	void SetSpeed(float speed);

//	Protected means we have access to it when we override the virtuals
protected:	
	
	//	Informational data
	std::string Name;
	std::string Description;

	//	Physics data
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	float rotation;
	float speed;

private:
	ObjectStatus status;
	GameSprite *sprite;
	float maxSpeed;
};

#endif	/*	GAMEPLAYOBJECT_H	*/

