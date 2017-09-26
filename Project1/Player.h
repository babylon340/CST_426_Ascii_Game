#pragma once
#include "Renderable.h"
#include "Vector.h"

class Player : public Renderable
{
public:
	enum {MOVE_LEFT = 1, MOVE_DOWN = 2, MOVE_RIGHT = 4, MOVE_UP = 8};
private:
	Vector pos;
	float speed;
	unsigned int moveFlags;
public:
	Player(Vector pos, float speed) : pos(pos),
		speed(speed), moveFlags(0)
	{
	}

	void SetMovement(UINT moveFlag)
	{
		moveFlags |= moveFlag;
	}
	void ClearMovement(UINT moveFlag)
	{
		moveFlags &= ~moveFlag;
	}

	void Update()
	{
		Vector dir;

		if (moveFlags & MOVE_LEFT)
		{
			if (!(moveFlags & MOVE_RIGHT))
			{
				dir += Vector(-1, 0);
			}
		}
		else if (moveFlags & MOVE_RIGHT)
		{
			dir += Vector(1, 0);
		}

		if (moveFlags & MOVE_UP)
		{
			if (!(moveFlags & MOVE_DOWN))
			{
				dir += Vector(0, -1);
			}
		}
		else if (moveFlags & MOVE_DOWN)
		{
			dir += Vector(0, 1);
		}

		dir = speed * Vector::Normalize(dir);

		pos += dir;
	}

	void Render(Screen& screen) const
	{
		Renderable::RenderCharacter(screen, 'P', pos.x, pos.y);
	}
};