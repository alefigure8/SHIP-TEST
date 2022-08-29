#include "Player.h"
#include <iostream>

// Private Functons
void Player::initSprite()
{
	_sprite.setTexture(_texture);
	_sprite.setScale(0.8f, 0.8f);
	_sprite.setPosition(200, 200);
}

void Player::initTexture()
{
	//Load Texture
	if (!_texture.loadFromFile("Texture/ship.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

// Constructor
Player::Player()
{
	_movement_speed = 3.f;
	_attack_max = 5.f;
	_attack = _attack_max;
	
	initTexture();
	initSprite();
}

// Functions
sf::Vector2f Player::getPosition()
{
	return _sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void Player::move(float x, float y)
{
	_sprite.move(_movement_speed * x, _movement_speed * y);
}

void Player::rotate(float deg)
{
	_sprite.rotate(deg);
}

void Player::updateAttack()
{
	if (_attack < _attack_max)
		_attack += 0.2f;
}

bool Player::canAttack()
{
	if (_attack >= _attack_max)
	{
		_attack = 0.f;
		return true;
	}

	return false;
}

void Player::update()
{
	updateAttack();
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}