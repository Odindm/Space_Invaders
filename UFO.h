#pragma once
#include "gameObject.h"
#include "sgg/graphics.h"

class UFO : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	bool active = true;
	graphics::Brush brush;
	int c = rand() % 2;

public:

	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; };
	void notActive() { active = false; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	UFO();
	~UFO();
	Disk getCollisionHull() const override;
};
