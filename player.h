#pragma once
#include "gameObject.h"
#include "config.h"

class Player : public GameObject, public Collidable
{
	float speed = 10.f;
	float pos_x = CANVAS_WIDTH/2 - 200 , pos_y = CANVAS_HEIGHT * 0.93f;
	
public:
	Player();
	void update() override;
	void draw() override;
	void init() override;
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	Disk getCollisionHull() const override;
};
