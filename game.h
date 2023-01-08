#pragma once
#include"player.h"
#include "enemy.h"
#include "enemyProj.h"
#include "UFO.h"
#include "barrier.h"
#include "playerProj.h"
#include "Explosion.h"


class Game
{
	//Game states
	typedef enum {STATUS_START, STATUS_GAMEPLAY, STATUS_GAMEOVER} state_t;
	state_t state = STATUS_START;

	void updateStart();
	void updateGameplay();
	void updateGameOver();
	void drawStart();
	void drawGameplay();
	void drawGameOver();
	//
	Player * player = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	int player_lives = 3;

	PlayerProj* playerProj = nullptr;
	bool pbullet_exists = false;

	Enemy * enemy = nullptr;
	Enemy * enemies[11][5] {};
	bool enemy_transition = false;
	void spawnEnemy();
	void enemyAdjust(int t);
	bool anyEnemiesAlive();
	//enemy death
	Explosion * explosion = nullptr;
	float duration = 1600.0f;
	bool timerstarted = false;
	float start = 0.0f;
	float currenttime = 0.0f;
	//ufo death
	Explosion * ufoexplosion = nullptr;
	float ufoduration = 120.0f;
	bool ufotimerstarted = false;
	float ufostart = 0.0f;
	float ufocurrenttime = 0.0f;
	//EnemyProj and flags
	EnemyProj* enemyProj = nullptr;
	bool ebullet_exists = false;
	int eligible_to_shoot;
	bool found_shooter;	
	//UFO + create + activity checker + score, flags and reset for easter egg
	UFO * ufo = nullptr;
	void spawnUfo();
	void is_ufo_active();
	bool twentythirdshot = false;
	int pbCounter = 0;
	void resetpbCounter() { pbCounter = 0; }
	int bonus;
	//Barriers + flag + create
	Barrier * barrier1[5][4] {};
	Barrier * barrier2[5][4] {};
	Barrier * barrier3[5][4] {};
	Barrier * barrier4[5][4] {};
	bool barriers_initialized = false;
	void createBarriers(); 

	//Collision checks
	bool checkCollisionE_P(Enemy * enemy);			//Collision enemy - player
	bool checkCollisionEB_P();						//enemyProj - player
	bool checkCollisionEB_PB();			  
	bool checkCollisionE_PB(Enemy * enemy);			//enemy - playerProj
	bool checkCollisionUFO_PB();
	bool checkCollisionBP_PB(Barrier * piece);      //barrier piece - playerProj
	bool checkCollisionBP_EB(Barrier * piece);		// -//-	  -//-  - enemyProj
	bool checkCollisionBP_E(Barrier * barrier, Enemy * enemy);
	int score = 0;

	
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() { return debug_mode; }
	void update();
	void draw();
	void init();
	void startgameplayinit();
	void gameoverinit();
	Game();
	~Game();
};
