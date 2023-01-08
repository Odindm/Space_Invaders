#pragma once
#include "gameObject.h"
#include "config.h"


class EnemyProj : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float bullet_speed = 20.0f;
	int c = 0;

public:

	void update() override;
	void draw() override;
	void init() override;
	float get_y() { return pos_y; }
	float get_x() { return pos_x; }
	EnemyProj(float x, float y);
	~EnemyProj();
	Disk getCollisionHull() const override;
};
