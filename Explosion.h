#pragma once
#include "gameObject.h"
#include "graphics.h"


class Explosion : public GameObject
{
	float pos_x, pos_y;

public:

	void update() override;
	void draw() override;
	void ufodraw();
	void init() override;
	Explosion(float x, float y);
	~Explosion();
};