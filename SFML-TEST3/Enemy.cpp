#include "Enemy.h"


void Enemy::initVariables()
{
	_point_count = rand() % 8 + 3; // 3 to 10
	_type = 0;
	_hp_max = static_cast<int>(_point_count);
	_hp = _hp_max;
	_damage = _point_count;
	_points = _point_count;
	_movement_speed = static_cast<float>(_point_count) / 2.f;

}


void Enemy::initShape()
{
	_shape.setRadius(static_cast<float>(_point_count) + 5.f);
	_shape.setPointCount(_point_count);
	_shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

Enemy::Enemy(float x, float y)
{

	initVariables();
	initShape();
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

int& Enemy::getPoints()
{
	return _points;
}

int& Enemy::getDamage()
{
	return _damage;
}
