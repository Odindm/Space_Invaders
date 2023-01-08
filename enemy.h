#pragma once
#include "gameObject.h"
#include "graphics.h"


class Enemy : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed = 5.0f;
	int type;
	graphics::Brush brush;
	int c = 2;

public:
	
	void update() override;
	void draw() override;
	void init() override;
	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	void upSpeed();
	void resetSpeed();
	void transition();
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	int getType() { return type; }
	Enemy( float type, float x, float y);
	~Enemy();
	Disk getCollisionHull() const override;
};