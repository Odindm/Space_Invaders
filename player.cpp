#include "player.h"
#include "graphics.h"
#include "config.h"
#include "game.h"


Player::Player()
{
}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 30.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 30.0f;
	}
	
	if (pos_x < 20) pos_x = 20;
	if (pos_x > CANVAS_WIDTH - 20) pos_x = CANVAS_WIDTH - 20;
}

void Player::draw()
{
	float glow =  0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "Vessel.png";
	graphics::drawRect(pos_x, pos_y, PLAYER_SIZE, PLAYER_SIZE, br);

	br.texture = "";
	br.fill_color[0] = 0.8f;
	br.fill_color[1] = 0.2f + glow * 0.5f;
	br.fill_color[2] = 0.6f;
	br.fill_secondary_color[0] = 0.6f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.3f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
		
	graphics::drawDisk(pos_x, pos_y + 15, 10, br);

}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = PLAYER_SIZE * 0.5f;
	return disk;
}

