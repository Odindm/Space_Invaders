#include "barrier.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

void Barrier::update()
{
}

void Barrier::draw()
{
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;

	if ((type1 == 0 && type2 == 1) || (type1 == 1 && type2 == 0))
	{
		brush.texture = std::string(ASSET_PATH) + "tri1.png";
		graphics::drawRect(pos_x, pos_y, BARRIER_PIECE_SIZE, BARRIER_PIECE_SIZE, brush);
	} 
	else if ((type1 == 0 && type2 == 3) || (type1 == 1 && type2 == 4))
	{
		brush.texture = std::string(ASSET_PATH) + "tri2.png";
		graphics::drawRect(pos_x, pos_y, BARRIER_PIECE_SIZE, BARRIER_PIECE_SIZE, brush);
	}
	else if (type1 == 2 && type2 == 1)
	{
		brush.texture = std::string(ASSET_PATH) + "tri3.png";
		graphics::drawRect(pos_x, pos_y, BARRIER_PIECE_SIZE, BARRIER_PIECE_SIZE, brush);
	}
	else if (type1 == 2 && type2 == 3)
	{
		brush.texture = std::string(ASSET_PATH) + "tri4.png";
		graphics::drawRect(pos_x, pos_y, BARRIER_PIECE_SIZE, BARRIER_PIECE_SIZE, brush);
	} 
	else
	{
		brush.texture = std::string(ASSET_PATH) + "BarrierPiece.png";
		graphics::drawRect(pos_x, pos_y, BARRIER_PIECE_SIZE, BARRIER_PIECE_SIZE, brush);
	}

}

void Barrier::init()
{
}

Barrier::Barrier(float type1, float type2, float x, float y)
{
	pos_x = x;
	pos_y = y;
	this->type1 = type1;
	this->type2 = type2;
	init();
}

Barrier::~Barrier()
{
}

Disk Barrier::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 7.5f;
	return disk;
}
