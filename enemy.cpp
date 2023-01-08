#include "enemy.h"
#include "sgg/graphics.h"
#include "config.h"
#include "game.h"



void Enemy::update()
{
	pos_x += speed * graphics::getDeltaTime() / 65.0f;	
}

void Enemy::draw()
{
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;

	if (type == 0 )
	{
		if (c < 20)
		{
			brush.texture = std::string(ASSET_PATH) + "Squid1.png";
			c += 1;
		}
		else
		{
			brush.texture = std::string(ASSET_PATH) + "Squid2.png";
			c += 1;
		}
		graphics::drawRect(pos_x, pos_y, SQUID_SIZE, SQUID_SIZE, brush);
	}
	else if (type == 1 || type == 2)
	{
		if (c < 20)
		{
			brush.texture = std::string(ASSET_PATH) + "Crab1.png";
			c += 1;
		}
		else
		{
			brush.texture = std::string(ASSET_PATH) + "Crab2.png";
			c += 1;
		}
		graphics::drawRect(pos_x, pos_y, CRAB_SIZE, CRAB_SIZE, brush);
	}
	else
	{
		if (c < 20)
		{
			brush.texture = std::string(ASSET_PATH) + "Octopus1.png";
			c += 1;
		}
		else
		{
			brush.texture = std::string(ASSET_PATH) + "Octopus2.png";
			c += 1;
		}
		graphics::drawRect(pos_x, pos_y, OCTOPUS_SIZE, OCTOPUS_SIZE, brush);
	}
	if (c > 40)
	{
		c = 2;
	}
}

void Enemy::init()
{
	
}

void Enemy::upSpeed()
{
	speed *= 1.027f;
}

void Enemy::resetSpeed()
{
	speed = 5.0f;
}

void Enemy::transition()
{
	speed *= -1;
	pos_y += 20.0f;
}

Enemy::Enemy(float type, float x, float y)
{
	pos_x = x;
	pos_y = y;
	this->type = type;
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	if (type == 0) {
		disk.radius = SQUID_SIZE * 0.5f;
	}
	else if (type == 1 || type == 2)
	{
		disk.radius = CRAB_SIZE * 0.5f;
	}
	else
	{
		disk.radius = OCTOPUS_SIZE * 0.5f;
	}
	return disk;
}
