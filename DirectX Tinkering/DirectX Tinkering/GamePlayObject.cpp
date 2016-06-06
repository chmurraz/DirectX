#include "GamePlayObject.h"

GamePlayObject::GamePlayObject(float x, float y, float rotation, float speed, float maxSpeed)
{
	//	M_PI is Pi, M_PI_2 is Pi/2 and MI_PI_4 is Pi/4
	float twoPi = (float)(M_PI * 2);
	position.x = x;
	position.y = y;
	position.z = 0;

	//	Rotation must be between zero and 2PI
	if (rotation > twoPi)
		rotation = twoPi;
	if (rotation < 0)
		rotation = 0;
	if (speed > maxSpeed)
		speed = maxSpeed;
	if (speed < 0)
		speed = 0;

	this->rotation = rotation;
	this->speed = speed;

	velocity.x = cos(rotation) * speed;
	velocity.y = sin(rotation) * speed;
	velocity.z = 0;

	this->maxSpeed = maxSpeed;
}


GamePlayObject::~GamePlayObject()
{
	if (sprite)
	{
		delete sprite;
		sprite = 0;
	}
}

bool GamePlayObject::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	status = ObjectStatus::Active;

	if (!sprite)
	{
		sprite = new GameSprite();
		if (!sprite->Initialize(device, file, width, height))
		{
			return false;
		}
		return true;
	}
}

void GamePlayObject::Update(float gameTime)
{
	if (status == ObjectStatus::Active)
	{
		position.x += velocity.x * gameTime;
		position.y += velocity.y * gameTime;
		position.z = 0;
	}
}

void GamePlayObject::Draw(float gameTime)
{
	if (sprite)
		sprite->Draw(gameTime, position);
}

ObjectStatus GamePlayObject::GetStatus() const
{
	return status;
}

void GamePlayObject::SetSpeed(float speed)
{
	if (speed >= 0 && speed <= maxSpeed)
	{
		this->speed;
		velocity.x = cos(rotation)*speed;
		velocity.y = sin(rotation)*speed;
		velocity.z = 0;
	}
}
