#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include<map>

class Game
{
private:
	//Objects
	sf::RenderWindow* _window;
	Player* _player;
	std::vector<Enemy*> _enemies;
	std::vector<Bullet*> _bullets;

	float _spawn_timer;
	float _spawn_timer_max;

	// Private Functions
	void initWindow();
	void initPlayer();
	Bullet* initBullet();
	Enemy* initEnemies();

	
public:
	//Cosntructor & Destructor
	Game();
	~Game();
	
	// Functions
	void run();
	
	void updatePollevents();
	void updateInput();
	void update();
	void render();
};

