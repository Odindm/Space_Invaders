#include "UFO.h"
#include "sgg/graphics.h"
#include "config.h"
#include <random>

void UFO::update()
{
	pos_x -= speed * graphics::getDeltaTime();
	if (c == 0)
	{
		if (pos_x < -50.0f)
		{
			active = false;
		}
	}
	else
	{
		if (pos_x > CANVAS_WIDTH + 20.0f)
		{
			active = false;
		}
	}	
}

void UFO::draw()
{
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;
	brush.texture = std::string(ASSET_PATH) + "UFO.png";
	graphics::drawRect(pos_x, pos_y, 55.0f, 25.0f, brush);
}

void UFO::init()
{
	if (c == 0) {
		speed = 0.12f;
		pos_x = CANVAS_WIDTH + 40.0f;
	}
	else
	{
		speed = -0.12f;
		pos_x = -40.0f;		
	}
	pos_y = 45.0f;
		
}

UFO::UFO()
{
	init();	
}

UFO::~UFO()
{
}

Disk UFO::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 45 * 0.5f;
	return disk;
}
