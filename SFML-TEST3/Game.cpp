#include "Game.h"

// Private functions
void Game::initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game test", sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
	_window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	_player = new Player();
	
}

Enemy* Game::initEnemies()
{
	return new Enemy(rand() % _window -> getSize().x, -100.f);
}

Bullet* Game::initBullet()
{
	return new Bullet(_player->getPosition().x + _player -> getBounds().width / 2.f - 10.f, _player->getPosition().y, 0.f, -1.f);
}

Game::Game()
{
	initWindow();
	initPlayer();
	initGUI();
	initWorld();
	
	_spawn_timer_max = 20.f;
	_spawn_timer = _spawn_timer_max;
	_point = 0;
}

Game::~Game()
{
	delete _window;
	
	delete _player;
	
	for (auto *i : _bullets)
	{
		delete i;
	}

	for (auto enemy : _enemies)
	{
		delete enemy;
	}
}

// Functions
void Game::run()
{
	// GAME LOOP
	while (_window->isOpen())
	{
		updatePollevents();
		
		if(_player -> getHP() > 0)
			update();
		
		render();
	}
}

void Game::updatePollevents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}
}

void Game::updateInput()
{
	//Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_player->move(0, -1);
		_world.move(0, 0.1f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_player->move(0, 1);
		_world.move(0, -0.1f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_player->move(-1, 0);
		_world.move(0.1f, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_player->move(1, 0);
		_world.move(-0.1f, 0);
	}
	
	// Bullets
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->canAttack())
	{
		_bullets.push_back(initBullet());
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : _bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete _bullets.at(counter);
			_bullets.erase(_bullets.begin() + counter);
		}

		counter++;
	}
	
}

void Game::updateEnemies()
{
	//Spawuning enemies
	_spawn_timer += 0.5f;
	if (_spawn_timer >= _spawn_timer_max)
	{
		_enemies.push_back(initEnemies());
		_spawn_timer = 0.f;
	}

	//Updating enemies
	unsigned counter = 0;
	for (auto* enemy : _enemies)
	{
		enemy->update();

		if (enemy->getBoundsEnemies().top + enemy->getBoundsEnemies().height > _window->getSize().y)
		{
			//Delete enemy when step out the screen
			delete _enemies.at(counter);
			_enemies.erase(_enemies.begin() + counter);
		}
		else if (enemy->getBoundsEnemies().intersects(_player->getBounds()))
		{
			//Damage
			_player->loseHP(_enemies.at(counter)->getDamage());
			
			//Delete enemy when crash with the ship
			delete _enemies.at(counter);
			_enemies.erase(_enemies.begin() + counter);
		}
		
		counter++;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update();

		bool enemy_removed = false;

		// bullet collide with enemies
		for (int j = 0; j < _bullets.size() && !enemy_removed; j++)
		{
			if (_bullets[j]->getBounds().intersects(_enemies[i]->getBoundsEnemies()))
			{
				_point+= _enemies[i] -> getPoints();
				
				delete _enemies[i];
				_enemies.erase(_enemies.begin() + i);
				
				delete _bullets[j];
				_bullets.erase(_bullets.begin() + j);
				
				enemy_removed = true;// break;
			}
		}
	}
	
}

void Game::update()
{
	//Inputs
	updateInput();

	//Player
	_player->update();

	//Bullet
	updateBullets();

	//Enemies
	updateEnemies();

	//Combat
	updateCombat();

	//GUI
	updateGUI();

	//Collision
	updateCollision();

}

void Game::render()
{
	// Clear
	_window->clear();
	
	//WORLD
	renderWorld();

	//Player
	_player->render(*_window);

	//Bullets
	for (auto* bullet : _bullets)
	{
		bullet ->render(*_window);
	}
	
	// Enemies
	for (auto* Enemy : _enemies)
	{
		Enemy->render(*_window);
	}
	
	//GUI
	renderGUI();


	//GAME OVER
	if (_player->getHP() <= 0)
		_window->draw(_game_over);

	//Display
	_window->display();
}

void Game::initGUI()
{
	//FONTS
	if(!_font.loadFromFile("Fonts/pixel.ttf"))
		std::cout << "ERROR::GAME::Fail to load font" << std::endl;
	
	//POINTS
	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setFillColor(sf::Color::White);
	_text.setPosition(10.f, 10.f);
	_text.setString("Score: " + std::to_string(_point));

	//GAME OVER
	_game_over.setFont(_font);
	_game_over.setCharacterSize(60);
	_game_over.setFillColor(sf::Color::Red);
	_game_over.setString("GAME OVER");
	_game_over.setPosition(
		_window->getSize().x / 2.f - _game_over.getGlobalBounds().width / 2.f,
		_window->getSize().y / 2.f - _game_over.getGlobalBounds().height / 2.f
		);

	//PLAYER BAR
	_player_bar.setSize(sf::Vector2f(300.f, 20.f));
	_player_bar.setFillColor(sf::Color::Red);
	_player_bar.setPosition(sf::Vector2f(10.f , 40.f));
	
	_player_bar_back = _player_bar;
	_player_bar_back.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::updateGUI() {

	//POINTS
	std::stringstream ss;
	ss << "Score: " << _point;
	_text.setString(ss.str());
	
	//PLAYER
	float hpPercent = static_cast<float>(_player->getHP()) / _player->getHPMAX();
	_player_bar.setSize(sf::Vector2f(300.f * hpPercent, _player_bar.getSize().y));

}

void Game::renderGUI() {
	_window->draw(_text);
	_window->draw(_player_bar_back);
	_window->draw(_player_bar);
}

void Game::initWorld()
{
	if(!_world_texture.loadFromFile("Background/backgroound.png"))
		std::cout << "ERROR::GAME::Fail to load background" << std::endl;
	
	_world.setTexture(_world_texture);
	_world.setPosition(-10.f, -10.f);
	_world.setScale(1.5f, 1.5f);
}

void Game::renderWorld() {
	_window->draw(_world);
}

void Game::updateWorld()
{
	
}

void Game::updateCollision()
{
	// LEFT
	if (_player->getBounds().left < 0.f)
	{
		_player->setPosition(0.f, _player->getBounds().top);
	}
	
	// RIGHT
	else if (_player->getBounds().left + _player->getBounds().width > _window->getSize().x)
	{
		_player->setPosition(_window->getSize().x - _player->getBounds().width, _player->getBounds().top);

	}

	//UP
	if (_player->getBounds().top < 0.f)
	{
		_player->setPosition(_player->getBounds().left, 0.f);
	}

	//DOWN
	else if (_player->getBounds().top + _player->getBounds().height >= _window -> getSize().y)
	{
		_player->setPosition(_player->getBounds().left, _window->getSize().y - _player->getBounds().width);
	}
}