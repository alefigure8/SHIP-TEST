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
	
	_spawn_timer_max = 20.f;
	_spawn_timer = _spawn_timer_max;
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
		_player->move(0, -1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_player->move(0, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_player->move(-1, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player->move(1, 0);
	
	// Bullets
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->canAttack())
	{
		_bullets.push_back(initBullet());
	}
}


void Game::update()
{
	//PollEvents
	updatePollevents();

	//Inputs
	updateInput();

	//Player
	_player->update();

	//Bullet
	unsigned counter = 0;
	for (auto* bullet : _bullets)
	{
		bullet->update();
		
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete _bullets.at(counter);
			_bullets.erase(_bullets.begin() + counter);
			--counter;
		}
		
		counter++;
	}

	//Enemies
	_spawn_timer += 0.5f;

	if (_spawn_timer >= _spawn_timer_max)
	{
		_enemies.push_back(initEnemies());
		_spawn_timer = 0.f;
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update();

		bool enemy_removed = false;

		// bullet collide with enemies
		for (int j = 0; j < _bullets.size() && !enemy_removed; j++)
		{
			if (_bullets[j]->getBounds().intersects(_enemies[i]->getBoundsEnemies()))
			{
				// TODO: SACAR VIDA A LOS ENEMIGOS
				//IF VIDA ENEMIGO = 0
				delete _enemies[i];
				_enemies.erase(_enemies.begin() + i);

				delete _bullets[j];
				_bullets.erase(_bullets.begin() + j);

				enemy_removed = true;
			}
		}

		// enemies step out screen
		if (_enemies[i]->getBoundsEnemies().top > _window -> getSize().y && !enemy_removed)
		{
			delete _enemies[i];
			_enemies.erase(_enemies.begin() + i);
			std::cout << "Erase: " << _enemies.size() << std::endl;
		}

	}

}

void Game::render()
{
	// Clear
	_window->clear();

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

	//Display
	_window->display();
}
