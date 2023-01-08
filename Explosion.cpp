#include "Explosion.h"
#include "config.h"

void Explosion::update()
{
}

void Explosion::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;
	brush.texture = std::string(ASSET_PATH) + "explosion.png";
	graphics::drawRect(pos_x, pos_y, CRAB_SIZE * 0.8f, CRAB_SIZE * 0.8f, brush);
}

void Explosion::ufodraw()
{
	graphics::Brush brush1;
	brush1.outline_opacity = 0.0f;
	brush1.fill_opacity = 1.0f;
	brush1.texture = std::string(ASSET_PATH) + "ufoexplosion.png";
	graphics::drawRect(pos_x, pos_y, 55.0f * 0.8f, 25.0f * 0.8f, brush1);
}

void Explosion::init()
{
}

Explosion::Explosion(float x, float y)
{
	pos_x = x;
	pos_y = y;
}

Explosion::~Explosion()
{
}
