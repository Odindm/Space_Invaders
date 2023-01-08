#include "sgg/graphics.h"
#include "playerProj.h"


void PlayerProj::update()
{
	pos_y -= bullet_speed * graphics::getDeltaTime() / 45.0f;
}

void PlayerProj::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;

	brush.fill_opacity = 1.0f;
	brush.texture = std::string(ASSET_PATH) + "playerProj.png";
	graphics::drawRect(pos_x, pos_y -13, 4, 10, brush);
}

void PlayerProj::init()
{
}

PlayerProj::PlayerProj(float x, float y) {
	pos_x = x;
	pos_y = y;
}

PlayerProj::~PlayerProj()
{
}

Disk PlayerProj::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = PROJ_RADIUS;
	return disk;
}
