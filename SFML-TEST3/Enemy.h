#ifndef ENEMY_H
#define ENEMY_H

#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::CircleShape _shape;
	int _type;
	int _hp;
	int _hp_max;
	int _damage;
	int _points;
	float _movement_speed;

	void initShape();

public:
	Enemy(float x, float y);
	~Enemy();

	void move(float x, float y);
	sf::FloatRect getBoundsEnemies();
	void update();
	void render(sf::RenderWindow& window);

};

#endif // !ENEMY_H

