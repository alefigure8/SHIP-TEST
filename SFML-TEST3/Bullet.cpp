#include "Bullet.h"

void Bullet::initSprite()
{
	_shape.setTexture(_texture);
	_shape.setScale(0.1f, 0.1f);
}

void Bullet::initTexture()
{
	//Load Texture
	if (!_texture.loadFromFile("Texture/fire.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Bullet::Bullet()
{
}

Bullet::Bullet(float pos_x, float pos_y, float x, float y)
{
	initTexture();
	initSprite();
	
	_shape.setPosition(pos_x, pos_y);
	_direction.x = x;
	_direction.y = y;
	_movement_speed = 5.0f;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return _shape.getGlobalBounds();
}

void Bullet::update()
{
	_shape.move(_movement_speed * _direction);
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(_shape);
}
