#pragma once
#include "gameObject.h"
#include "config.h"


class PlayerProj : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float bullet_speed = 30.0f;

public:

	void update() override;
	void draw() override;
	void init() override;
	float get_y() { return pos_y; }
	PlayerProj(float x, float y);
	~PlayerProj();
	Disk getCollisionHull() const override;
};
