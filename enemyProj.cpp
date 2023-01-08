#include "sgg/graphics.h"
#include "enemyProj.h"
#include <random>

void EnemyProj::update()
{
	pos_y += bullet_speed * graphics::getDeltaTime() / 55.0f;

}

void EnemyProj::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;

	if (c < 15)
	{
		brush.texture = std::string(ASSET_PATH) + "enemyProj1.png";		
		c += 1;
	}
	else
	{
		brush.texture = std::string(ASSET_PATH) + "enemyProj2.png";
		c += 1;
	}
	if (c > 30)
	{
		c = 0;
	}
		graphics::drawRect(pos_x, pos_y + 5, 4, 10, brush);
}

void EnemyProj::init()
{
}

EnemyProj::EnemyProj(float x, float y)
{
	pos_x = x;
	pos_y = y;
}

EnemyProj::~EnemyProj()
{
}

Disk EnemyProj::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = PROJ_RADIUS;
	return disk;
}
