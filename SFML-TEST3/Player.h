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

	int _hp;
	int _hp_max;
	
	//Private Functions
	void initSprite();
	void initTexture();
	
public:
	//Constructir
	Player();
	
	//Function
	sf::Vector2f getPosition();
	const sf::FloatRect getBounds() const;
	int& getHP();
	int& getHPMAX();
	
	void move(float x, float y);
	void rotate(float deg);
	bool canAttack();
	
	//modifiers
	void setPosition(const sf::Vector2f position);
	void setPosition(const float x, const float y);
	void setHP(int hp);
	void loseHP(int value);
	
	void updateAttack();
	void update();
	
	void render(sf::RenderWindow& window);
};

