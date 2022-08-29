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

	int _points;

	//GUI
	sf::Font _font;
	sf::Text _point_text;

	// Private Functions
	void initWindow();
	void initPlayer();
	Bullet* initBullet();
	Enemy* initEnemies();
	void initGUI();
	
public:
	//Cosntructor & Destructor
	Game();
	~Game();
	
	// Functions
	void run();
	void updateGUI();
	void updatePollevents();
	void updateInput();
	void update();
	void renderGUI();
	void render();
};

