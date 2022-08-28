#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	
	float _movement_speed;
	
	sf::Vector2f _last_position;

	float _attack;
	float _attack_max;
	
	//Private Functions
	void initSprite();
	void initTexture();
	
public:
	//Constructir
	Player();
	
	//Function
	sf::Vector2f getPosition();
	const sf::FloatRect getBounds() const;
	void move(float x, float y);
	void rotate(float deg);
	void updateAttack();
	bool canAttack();
	void update();
	void render(sf::RenderWindow& window);
};

