#include "Enemy.h"

void Enemy::initShape()
{
	_shape.setRadius(rand() % 20 + 20);
	_shape.setPointCount(rand() % 20 + 3);
	_shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

Enemy::Enemy(float x, float y)
{
	initShape();
	
	_type	= 0;
	_hp		= 0;
	_hp_max = 10;
	_damage = 5;
	_points = 1;
	_movement_speed = rand() % 10 + 5;

	_shape.setPosition(x, y);
}

Enemy::~Enemy()
{
}

//Functions
void Enemy::update()
{
	_shape.move(0.f, _movement_speed);
}

void Enemy::render(sf::RenderWindow& window)
{
	window.draw(_shape);
}


sf::FloatRect Enemy::getBoundsEnemies()
{
	return _shape.getGlobalBounds();
}

void Enemy::move(float x, float y)
{
	_shape.move(_movement_speed * x, _movement_speed * y);
}