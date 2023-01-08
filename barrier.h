#pragma once
#include "gameObject.h"
#include "sgg/graphics.h"

class Barrier : public GameObject, public Collidable
{
	float pos_x, pos_y;
	int type1, type2;
	graphics::Brush brush;

public:

	void update() override;
	void draw() override;
	void init() override;
	void setPosX(float x) { x = pos_x; }
	void setPosY(float y) { y = pos_y; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	Barrier(float type1, float type2, float x, float y);
	~Barrier();
	Disk getCollisionHull() const override;
};
