#ifndef BULLET_H
#define BULLET_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

class Bullet
{
private:
	sf::Sprite _shape;
	sf::Texture _texture;
	sf::Vector2f _direction;
	float _movement_speed;
	
	//Private functions
	void initSprite();
	void initTexture();
	
public:
	//Constructor
	Bullet();
	Bullet(float pos_x, float pos_y, float x, float y);
	virtual ~Bullet();

	//Functions
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderWindow& window);
};

#endif // !BULLET_H