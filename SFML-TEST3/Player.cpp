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
	_hp_max = 100;
	_hp = _hp_max;
	
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

void Player::setPosition(const sf::Vector2f position)
{
	_sprite.setPosition(position);

}

void Player::setPosition(const float x, const float y)
{
	_sprite.setPosition(x, y);
}

int& Player::getHP()
{
	return _hp;
}

int& Player::getHPMAX()
{
	return _hp_max;
}

void Player::setHP(int hp) {
	_hp = hp;
}

void Player::loseHP(int value){
	_hp -= value;
	if (_hp < 0)
		_hp = 0;
}