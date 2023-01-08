#include "game.h"
#include "graphics.h"
#include "config.h"
#include <random>

void Game::spawnUfo()
{
	if (!ufo){
		ufo = new UFO();
		graphics::playSound(std::string(ASSET_PATH) + "ufo.wav", 0.02f, false);
	}
}

void Game::is_ufo_active()
{
	if (ufo && !ufo->isActive())
	{
		delete ufo;
		ufo = nullptr;
	}
}

void Game::createBarriers()
{
	if (!barriers_initialized && graphics::getGlobalTime() > 1000)
	{
		const int distance = 250;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				if (!(x == 0 && y == 0) && !(x == 4 && y == 0) && !(x == 2 && y == 2) && !(x == 1 && y == 3) && !(x == 2 && y == 3) && !(x == 3 && y == 3))
				{
					// Barrier starting pos
					float barrier1X = x * BARRIER_PIECE_SIZE + BARRIER_PIECE_SIZE * 9.6f;
					float barrier2X = barrier1X + distance;
					float barrier3X = barrier1X + distance * 2;
					float barrier4X = barrier1X + distance * 3;
					float barrierY = y * BARRIER_PIECE_SIZE + CANVAS_HEIGHT * 0.82f;			
				
					barrier1[x][y] = new Barrier(y, x, barrier1X, barrierY);
					barrier2[x][y] = new Barrier(y, x, barrier2X, barrierY);
					barrier3[x][y] = new Barrier(y, x, barrier3X, barrierY);
					barrier4[x][y] = new Barrier(y, x, barrier4X, barrierY);									
				}				
			}
		}
		barriers_initialized = true;
	}
}
// Collisions
bool Game::checkCollisionE_P(Enemy * enemy)
{
	if (!player || !enemy)
	{
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionEB_P()
{
	if (!player || !enemyProj)
	{
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = enemyProj->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionEB_PB()
{
	if (!playerProj || !enemyProj)
	{
		return false;
	}
	Disk d1 = playerProj->getCollisionHull();
	Disk d2 = enemyProj->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionE_PB(Enemy * enemy)
{
	if (!playerProj || !enemy)
	{
		return false;
	}
	Disk d1 = playerProj->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionUFO_PB()
{
	if (!playerProj || !ufo) 
	{
		return false;
	}
	Disk d1 = playerProj->getCollisionHull();
	Disk d2 = ufo->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}
//barrier collisions
bool Game::checkCollisionBP_PB(Barrier * piece)
{
	if (!playerProj || !piece)
	{
		return false;
	}
	Disk d1 = playerProj->getCollisionHull();
	Disk d2 = piece->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionBP_EB(Barrier * piece)
{
	if (!enemyProj || !piece)
	{
		return false;
	}
	Disk d1 = enemyProj->getCollisionHull();
	Disk d2 = piece->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::checkCollisionBP_E(Barrier * piece, Enemy * enemy)
{	
	if (!enemy || !piece)
	{
		return false;
	}
	Disk d1 = enemy->getCollisionHull();
	Disk d2 = piece->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx *dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
		
}

//
void Game::spawnEnemy()
{
	if (!/*enemies_initialized*/anyEnemiesAlive() && graphics::getGlobalTime() > 1000)
	{
		const int gap = 4;
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 11; x++)
			{
				// Enemy starting pos
				float enemyX = x * OCTOPUS_SIZE + (gap * x * 3) + OCTOPUS_SIZE + 20.0f;
				float enemyY = y * OCTOPUS_SIZE + (gap * y) + OCTOPUS_SIZE * 4;
				enemies[x][y] = new Enemy(y, enemyX, enemyY);
				enemies[x][y]->resetSpeed();//----
			}
		}
		//enemies_initialized = true;
	}
}

void Game::enemyAdjust(int t)
{
	float adjustment = 5.0f;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (enemies[x][y] != nullptr)
			{
				if (t == 0) {
					enemies[x][y]->setPosX(enemies[x][y]->getPosX() - adjustment);
				}
				else
				{
					enemies[x][y]->setPosX(enemies[x][y]->getPosX() + adjustment);
				}
			}
		}
	}
}

bool Game::anyEnemiesAlive()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (enemies[x][y] != nullptr)
			{
				return true;
				break;
			}
		}
	}
	return false;
}

//Screen updates
void Game::updateStart()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{		
		state = STATUS_GAMEPLAY;
	}
}

void Game::updateGameplay()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player();
		player_initialized = true;
	}

	if (player)
		player->update();

	//Player bullet
	if (player && graphics::getKeyState(graphics::SCANCODE_W))
	{
		if (!pbullet_exists)
		{
			playerProj = new PlayerProj(player->getPosX(), player->getPosY());
			pbullet_exists = true;
			graphics::playSound(std::string(ASSET_PATH) + "shoot.wav", 0.2f, false);
			pbCounter += 1;
		}
	}

	if (playerProj != nullptr)
	{
		playerProj->update();
	}

	if (pbullet_exists)
	{
		if (playerProj->get_y() < 0)
		{
			pbullet_exists = false;
			delete playerProj;
			playerProj = nullptr;
		}
	}
	//
	is_ufo_active();
	// spawnUFO 
	int c = rand() % 6350;
	if (c == 126)
	{
		spawnUfo();
	}
	if (ufo)
		ufo->update();
	//
	//spawn enemy
	if (!anyEnemiesAlive())
	{
		spawnEnemy();
	}
	//
	//Enemy movement
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (enemies[x][y] != nullptr)
			{
				if (enemies[x][y]->getPosX() > CANVAS_WIDTH - 15.0f)
				{
					enemy_transition = true;					
					enemyAdjust(0);
					break;
				}
				if (enemies[x][y]->getPosX() < 15.0f)
				{
					
					enemy_transition = true;
					enemyAdjust(1);
					break;
				}
			}
		}
		if (enemy_transition == true)
		{
			break;
		}
	}
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (enemies[x][y] != nullptr && enemy_transition == true)
			{
				enemies[x][y]->transition();
			}
		}
	}
	enemy_transition = false;

	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (enemies[x][y] != nullptr)
			{
				enemies[x][y]->update();
			}
		}
	}
	//
	//enemy fire
	if (!ebullet_exists && anyEnemiesAlive()) 
	{
		eligible_to_shoot = rand() % 11;

		while (!found_shooter)
		{
			for (int i = 4; i > -1; i--)
			{
				if (enemies[eligible_to_shoot][i] != nullptr)
				{
					//enemy shoots
					if (!ebullet_exists)
					{
						graphics::playSound(std::string(ASSET_PATH) + "shoot.wav", 0.05f, false);
						enemyProj = new EnemyProj(enemies[eligible_to_shoot][i]->getPosX(), enemies[eligible_to_shoot][i]->getPosY());
						ebullet_exists = true;
						found_shooter = true;
					}
				}
			}
			eligible_to_shoot = rand() % 11;
		}
	}

	if (ebullet_exists)
	{
		enemyProj->update();
	}
	if (ebullet_exists)
	{
		if (enemyProj->get_y() > CANVAS_HEIGHT)
		{
			ebullet_exists = false;
			delete enemyProj;
			enemyProj = nullptr;
			found_shooter = false;
		}
	}
	//
	// create barriers
	createBarriers();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (barrier1[x][y] != nullptr)
				barrier1[x][y]->update();

			if (barrier2[x][y] != nullptr)
				barrier2[x][y]->update();

			if (barrier3[x][y] != nullptr)
				barrier3[x][y]->update();

			if (barrier4[x][y] != nullptr)
				barrier4[x][y]->update();
		}
	}
	//
	// Collision checks
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (checkCollisionE_P(enemies[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "player_death.wav", 0.2f, false);
				delete player;
				player = nullptr;
				state = STATUS_GAMEOVER;	
				init();
			}
			currenttime += 2.0f;
			if (checkCollisionE_PB(enemies[x][y]))
			{
				if (explosion && currenttime - start < duration)
				{
					delete explosion;
					explosion = nullptr;
					timerstarted = false;
					currenttime = 0.0f;
				}
				graphics::playSound(std::string(ASSET_PATH) + "ebpbcol.mp3", 0.2f, false);// play enemy death sound <- here
				delete playerProj;
				playerProj = nullptr;
				pbullet_exists = false;
				if (enemies[x][y]->getType() == 0)
				{
					score += 30;
				}
				else if (enemies[x][y]->getType() == 1 || enemies[x][y]->getType() == 2)
				{
					score += 20;
				}
				else
				{
					score += 10;
				}
				if (!timerstarted) 
				{
					start = currenttime;
					timerstarted = true;
				}
				float explox = enemies[x][y]->getPosX();
				float exploy = enemies[x][y]->getPosY();			
				delete enemies[x][y];
				enemies[x][y] = nullptr;
				explosion = new Explosion(explox, exploy);
				//up the speed for the remaining enemies
				for (int y = 0; y < 5; y++)
				{
					for (int x = 0; x < 11; x++)
					{
						if (enemies[x][y] != nullptr)
						{
							enemies[x][y]->upSpeed();
						}
					}
				}//
			}
			if (explosion && currenttime - start > duration)
			{
				delete explosion;
				explosion = nullptr;
				timerstarted = false;
				currenttime = 0.0f;
			}
		}
	}
	//barrier with bullets collisions
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			//bp with player bullet-----------------------
			if (checkCollisionBP_PB(barrier1[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				delete playerProj;
				playerProj = nullptr;
				pbullet_exists = false;

				delete barrier1[x][y];
				barrier1[x][y] = nullptr;
			}
			if (checkCollisionBP_PB(barrier2[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				delete playerProj;
				playerProj = nullptr;
				pbullet_exists = false;

				delete barrier2[x][y];
				barrier2[x][y] = nullptr;
			}
			if (checkCollisionBP_PB(barrier3[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				delete playerProj;
				playerProj = nullptr;
				pbullet_exists = false;

				delete barrier3[x][y];
				barrier3[x][y] = nullptr;
			}
			if (checkCollisionBP_PB(barrier4[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				delete playerProj;
				playerProj = nullptr;
				pbullet_exists = false;

				delete barrier4[x][y];
				barrier4[x][y] = nullptr;
			}
			//bp with enemy bullet-------------------------
			if (checkCollisionBP_EB(barrier1[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				ebullet_exists = false;
				delete enemyProj;
				enemyProj = nullptr;
				found_shooter = false;

				delete barrier1[x][y];
				barrier1[x][y] = nullptr;
			}
			if (checkCollisionBP_EB(barrier2[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				ebullet_exists = false;
				delete enemyProj;
				enemyProj = nullptr;
				found_shooter = false;

				delete barrier2[x][y];
				barrier2[x][y] = nullptr;
			}if (checkCollisionBP_EB(barrier3[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				ebullet_exists = false;
				delete enemyProj;
				enemyProj = nullptr;
				found_shooter = false;

				delete barrier3[x][y];
				barrier3[x][y] = nullptr;
			}if (checkCollisionBP_EB(barrier4[x][y]))
			{
				graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
				ebullet_exists = false;
				delete enemyProj;
				enemyProj = nullptr;
				found_shooter = false;

				delete barrier4[x][y];
				barrier4[x][y] = nullptr;
			}
		}
	}
	//
	//barrier with enemy collision
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 11; l++)
				{
					if (checkCollisionBP_E(barrier1[x][y], enemies[l][k]))
					{
						graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
						delete barrier1[x][y];
						barrier1[x][y] = nullptr;
					}
					if (checkCollisionBP_E(barrier2[x][y], enemies[l][k]))
					{
						graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
						delete barrier2[x][y];
						barrier2[x][y] = nullptr;
					}
					if (checkCollisionBP_E(barrier3[x][y], enemies[l][k]))
					{
						graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
						delete barrier3[x][y];
						barrier3[x][y] = nullptr;
					}
					if (checkCollisionBP_E(barrier4[x][y], enemies[l][k]))
					{
						graphics::playSound(std::string(ASSET_PATH) + "barrier.mp3", 0.1f, false);
						delete barrier4[x][y];
						barrier4[x][y] = nullptr;
					}
				}
			}
		}
	}
	//
	if (checkCollisionEB_P())
	{
		graphics::playSound(std::string(ASSET_PATH) + "player_death.wav", 0.2f, false);// change that to a diff sound and move that to the case where the player dies
		//lose a hit point or kill depending on player life
		if (player_lives > 1)
		{
			delete player;
			player = nullptr;
			player_initialized = false;
			player_lives -= 1;

			ebullet_exists = false;
			delete enemyProj;
			enemyProj = nullptr;
			found_shooter = false;
		}
		else
		{
			delete player;
			player = nullptr;
			player_lives -= 1;
			state = STATUS_GAMEOVER;
			init();
		}
	}

	if (checkCollisionEB_PB())
	{
		graphics::playSound(std::string(ASSET_PATH) + "ebpbcol.mp3", 0.2f, false);
		delete playerProj;
		playerProj = nullptr;
		pbullet_exists = false;

		ebullet_exists = false;
		delete enemyProj;
		enemyProj = nullptr;
		found_shooter = false;
	}
	ufocurrenttime += 2.0f;
	if (checkCollisionUFO_PB())
	{
		if (ufoexplosion && ufocurrenttime - ufostart < ufoduration)
		{
			delete ufoexplosion;
			ufoexplosion = nullptr;
			ufotimerstarted = false;
			ufocurrenttime = 0.0f;
		}
		graphics::playSound(std::string(ASSET_PATH) + "player_death.wav", 0.2f, false);// <-change sound file (optional)
		delete playerProj;
		playerProj = nullptr;
		pbullet_exists = false;

		if (!ufotimerstarted)
		{
			ufostart = ufocurrenttime;
			ufotimerstarted = true;
		}
		float ufoexplox = ufo->getPosX();
		float ufoexploy = ufo->getPosY();
		ufo->notActive();
		delete ufo;
		ufo = nullptr;
		ufoexplosion = new Explosion(ufoexplox, ufoexploy);

		if (pbCounter == 23 && twentythirdshot == false)
		{
			twentythirdshot = true;
			resetpbCounter();
		}
		if ((pbCounter != 23 && twentythirdshot == false) || (pbCounter % 15 != 0 && twentythirdshot == true))
		{
			int roll = rand() % 3;
			if (roll == 0)
			{
				bonus = 50;
			}
			else if (roll == 1)
			{
				bonus = 100;
			}
			else
			{
				bonus = 150;
			}
		}
		if (pbCounter % 15 == 0 && twentythirdshot == true)// Space invaders easter egg.
		{
			bonus = 300;
		}
		score += bonus;
	}
	if (ufoexplosion && ufocurrenttime - ufostart > ufoduration)
	{
		delete ufoexplosion;
		ufoexplosion = nullptr;
		ufotimerstarted = false;
		ufocurrenttime = 0.0f;
	}
}

void Game::updateGameOver()
{
	if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE))
	{
		//reset
		score = 0;
		twentythirdshot = false;
		pbCounter = 0;
		player_lives = 3;
		player_initialized = false;
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 11; x++)
			{
				if (enemies[x][y] != nullptr)
				{
					delete enemies[x][y];
					enemies[x][y] = nullptr;
				}
			}
		}
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				if (barrier1[x][y] != nullptr)
				{
					delete barrier1[x][y];
					barrier1[x][y] = nullptr;
				}
				if (barrier2[x][y] != nullptr)
				{
					delete barrier2[x][y];
					barrier2[x][y] = nullptr;
				}
				if (barrier3[x][y] != nullptr)
				{
					delete barrier3[x][y];
					barrier3[x][y] = nullptr;
				}
				if (barrier4[x][y] != nullptr)
				{
					delete barrier4[x][y];
					barrier1[x][y] = nullptr;
				}
			}
		}
		barriers_initialized = false;
		if (ufo)
		{
			delete ufo;
			ufo = nullptr;
		}
		if (explosion)
		{
			delete explosion;
			explosion = nullptr;
			timerstarted = false;
		}
		if (ufoexplosion)
		{
			delete ufoexplosion;
			ufoexplosion = nullptr;
			ufotimerstarted = false;
		}
		if (playerProj)
		{
			delete playerProj;
			playerProj = nullptr;
			pbullet_exists = false;
		}
		if (enemyProj)
		{
			delete enemyProj;
			enemyProj = nullptr;
			ebullet_exists = false;
			found_shooter = false;
		}
		//
		state = STATUS_START;
		init();
	}
}
void Game::drawStart()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "start.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH * 0.7f, CANVAS_WIDTH * 0.7f, br);
	/*char info[40];
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(CANVAS_WIDTH / 2 - 230.0f, CANVAS_HEIGHT / 2, 25, info, br);*/
}
void Game::drawGameplay()
{
	graphics::Brush br;
	//br.texture = std::string(ASSET_PATH) + "background.png";
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 1.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	// draw player
	if (player)
		player->draw();

	//draw player proj
	if (playerProj != nullptr)
	{
		playerProj->draw();
	}

	// draw ufo
	if (ufo)
		ufo->draw();
	//draw barriers
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (barrier1[x][y] != nullptr)
			{
				barrier1[x][y]->draw();
			}
			if (barrier2[x][y] != nullptr)
			{
				barrier2[x][y]->draw();
			}
			if (barrier3[x][y] != nullptr)
			{
				barrier3[x][y]->draw();
			}
			if (barrier4[x][y] != nullptr)
			{
				barrier4[x][y]->draw();
			}
		}
	}//

	//draw enemies	
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (enemies[x][y] != nullptr)
				enemies[x][y]->draw();
		}
	}

	//draw explosions
	if (explosion)
		explosion->draw();

	if (ufoexplosion)
		ufoexplosion->ufodraw();

	//draw enemy proj
	if (enemyProj != nullptr)
	{
		enemyProj->draw();
	}

	//UI_info
		//score
	graphics::Brush brush1;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	char info[40];
	//sprintf_s(info, "(%5.2f, %5.2f)", player->getPosX(), player->getPosY());
	sprintf_s(info, "SCORE: %d", score);
	graphics::drawText(30, 30, 25, info, brush1);

	//remaining lives
	graphics::Brush brpl;
	brpl.outline_opacity = 0.0f;
	brpl.fill_opacity = 1.0f;
	brpl.texture = std::string(ASSET_PATH) + "Vessel.png";
	for (int i = 0; i < player_lives + 1; i++) {

		if (player_lives > 0)
			graphics::drawRect(1 * PLAYER_SIZE * 0.7 + (10.0 * 1 * 3) + PLAYER_SIZE * 0.7 + 20.0f, CANVAS_HEIGHT * 0.97f, PLAYER_SIZE * 0.7, PLAYER_SIZE * 0.7, brpl);

		if (player_lives > 1)
			graphics::drawRect(2 * PLAYER_SIZE * 0.7 + (10.0 * 2 * 3) + PLAYER_SIZE * 0.7 + 20.0f, CANVAS_HEIGHT * 0.97f, PLAYER_SIZE * 0.7, PLAYER_SIZE * 0.7, brpl);

		if (player_lives > 2)
			graphics::drawRect(3 * PLAYER_SIZE * 0.7 + (10.0 * 3 * 3) + PLAYER_SIZE * 0.7 + 20.0f, CANVAS_HEIGHT * 0.97f, PLAYER_SIZE * 0.7, PLAYER_SIZE * 0.7, brpl);
	}
	/*if (player && debug_mode)
	  {
	  }*/
}

void Game::drawGameOver()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "gameover.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH * 0.7f, CANVAS_WIDTH * 0.7f, br);

	graphics::Brush brush1;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	char info[40];
	sprintf_s(info, "FINAL SCORE: %d", score);
	graphics::drawText(CANVAS_WIDTH/2 - 120.0f, CANVAS_HEIGHT * 0.1f, 25, info, brush1);
}
//
void Game::update()
{
	if (state == STATUS_START)
	{
		updateStart();
	}
	else if (state == STATUS_GAMEPLAY)
	{
		updateGameplay();
	}
	else 
	{
		updateGameOver();
	}
}

	
void Game::draw()
{
	if (state == STATUS_START)
	{
		drawStart();
	}
	else if (state == STATUS_GAMEPLAY)
	{
		drawGameplay();
	}
	else
	{
		drawGameOver();
	}
	
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "font.ttf");
	if (state == STATUS_GAMEOVER)
		gameoverinit();
	else
		startgameplayinit();
}

void Game::startgameplayinit()
{
	graphics::playMusic(std::string(ASSET_PATH) + "start.mp3", 0.4f, true, 4000);
}

void Game::gameoverinit()
{
	graphics::playMusic(std::string(ASSET_PATH) + "gameover.mp3", 0.9f, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
}
