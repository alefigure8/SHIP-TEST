#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
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

	//SPAWN
	float _spawn_timer;
	float _spawn_timer_max;

	// POINST
	unsigned _point;

	//WORLD
	sf::Sprite _world;
	sf::Texture _world_texture;
	
	// GUI
	sf::Font _font;
	sf::Text _text;
	sf::Text _game_over;
	
	sf::RectangleShape _player_bar;
	sf::RectangleShape _player_bar_back;

	// Private Functions
	void initWindow();
	void initPlayer();
	Bullet* initBullet();
	Enemy* initEnemies();
	void initGUI();
	void initWorld();

	
public:
	//Cosntructor & Destructor
	Game();
	~Game();
	
	// Functions
	void run();

	void updatePollevents();
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateWorld();
	void updateCollision();
	void updateEnemies();
	void updateCombat();
	void update();
	
	void renderWorld();
	void renderGUI();
	void render();
};

