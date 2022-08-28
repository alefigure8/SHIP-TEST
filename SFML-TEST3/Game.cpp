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
	_player = new Player;
}

Bullet* Game::initBullet()
{
	return new Bullet(_player->getPosition().x + _player -> getBounds().width / 2, _player->getPosition().y, 0.f, -1.f);
}

Game::Game()
{
	initWindow();
	initPlayer();
}

Game::~Game()
{
	delete _window;
	
	delete _player;
	
	for (auto *i : _bullets)
	{
		delete i;
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

}

void Game::render()
{
	// Clear
	_window->clear();

	//Player
	_player->render(*_window);

	//Bullets
	for (auto *bullet : _bullets)
	{
		bullet ->render(*_window);
	}

	//Display
	_window->display();
}
