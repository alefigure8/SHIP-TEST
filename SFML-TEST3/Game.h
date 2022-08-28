#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include<map>

class Game
{
private:
	//Objects
	sf::RenderWindow* _window;
	Player* _player;
	std::vector<Bullet*> _bullets;

	// Private Functions
	void initWindow();
	void initPlayer();
	Bullet* initBullet();

	
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

