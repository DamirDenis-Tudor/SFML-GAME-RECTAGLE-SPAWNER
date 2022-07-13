#include "game_engine.h"

//init functions
void Game::initVariables()
{
	this->renderWindow = nullptr;

	//game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->spwnTimerMax = 20.f;
	this->spawnTimer = this->spwnTimerMax;
	this->maxEnemies = 5;
}

void Game::initFont()
{
	this->font.loadFromFile("font/OpenSans-Bold.ttf");
}

void Game::initText()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
}

void Game::initWindow()
{
	this->videoMode.width = 1080;
	this->videoMode.height = 720;
	this->renderWindow = new sf::RenderWindow(this->videoMode, "My game");
	this->renderWindow->setFramerateLimit(60);
}

//game dynamic objects
//void Game::initEnemy(sf:)
//{
//	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
//	this->enemy.setFillColor(sf::Color::Red);
//}

//contructor and destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete(this->renderWindow);
}

//bool functions
const bool Game::windowIsOpen()
{
	return this->renderWindow->isOpen() ? true : false ;
}

const bool Game::isEvent()
{
	return this->renderWindow->pollEvent(this -> event) ? true : false;
}

const bool Game::endGameEv()
{
	return this->endGame;
}

//engine functions

void Game::spawnEnemy()
{
	/*
		@return void
		->set random position , color
		->spawn

		-adds enemy to the vector
	*/

	//position
	this->enemy.type.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->renderWindow->getSize().x - this->enemy.type.getSize().x)),
		0.f
		);


	//type selector
	int selector = rand() % 4;

	sf::Vector2f size;
	sf::Color color;
	switch (selector)
	{
	case 0:
		size = sf::Vector2f (100.f, 100.f);
		color = sf::Color::Yellow;
		break;
	case 1:
		size = sf::Vector2f(75.f, 75.f);
		color = sf::Color::Green;
		break;
	case 2:
		size = sf::Vector2f(50.f, 50.f);
		color = sf::Color::Blue;
		break;
	case 3:
		size = sf::Vector2f(25.f, 25.f);
		color = sf::Color::Magenta;
		break;
	default:
		break;
	}

	//set
	this->enemy.setTypeSize(size);
	this->enemy.setTypeColor(color);

	//update vector elements
	this->enemies.push_back(this->enemy);
}

void Game::poolEvents()
{
	/*
		@return void
		->close mecanism - close botton , close exit
	*/
	while (this->isEvent())
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->renderWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->renderWindow->close();
				break;
			}
		}
	}
}

void Game::updateMousePos()
{
	/*
		@return void 
			-> mouse window ponsition
			-> mouse window coordonates;
	*/

	this->mousePos = sf::Mouse::getPosition(*this->renderWindow);
	this->viewMousePos = this->renderWindow->mapPixelToCoords(this->mousePos);
}

void Game::updateText()
{
	std::stringstream displayText;
	displayText << "Points : " << this->points << "\n" << "Health :" << this->health;
	this->text.setString(displayText.str());
}

void Game::updateEnemies()
{
	/*
		@return void 
			-> spawn enemies ;
			-> move enemies ;
			-> delete enemies mecanism 
				{
					- when is bellow the window ;
					- when is clicked ;
				}
	*/

	//spawn enemies
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->spawnTimer >= this->spwnTimerMax)
		{
			this->spawnEnemy();
			this->spawnTimer = 0.f;
		}
		else
		{
			this->spawnTimer += 1.f;
		}
	}

	//move enemies
	for (int index = 0; index < this->enemies.size();++index)
	{
		bool deleted = false;
		this->enemies[index].type.move(0.f, 2.f);

		//check if mouse is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[index].type.getGlobalBounds().contains(this->viewMousePos))
			{
				this->points += 5;
				deleted = true;
			}
		}

		//check if enemy is bellow the screen
		if (this->videoMode.height <= this->enemies[index].type.getPosition().y)
		{
			this->health -= 5;
			deleted = true;
		}

		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + index);
		}
	}
}

void Game::update()
{
	/*
		->queue of evenimets
		->mouse pozition
		->enemies
		->update health , points
	*/
	this->poolEvents();

	if (!this->endGame)
	{
		this->updateMousePos();
		this->updateEnemies();
		this->updateText();
	}

	if (this->health == 0)
	{
		this->endGame = true;
		std::cout << "Stop game ! \n";
	}
}

void Game::renderText()
{
	this->renderWindow->draw(this->text);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->renderWindow->draw(e.type);
	}
}

void Game::render()
{
	/*
		return void
			->clear old frame
			->draw next one and text
e			->display
	*/

	this->renderWindow->clear();

	this->renderEnemies();
	this->renderText();

	this->renderWindow->display();
}


//enemy class
//contructor & destructor 
Enemy::Enemy()
{
	type.setSize(sf::Vector2f (20.f, 20.f) );
	type.setFillColor(sf::Color::Yellow);
}

sf::RectangleShape Enemy::getType()
{
	return type;
}

void Enemy::setTypeSize(sf::Vector2f size)
{
	type.setSize(size);
}

void Enemy::setTypeColor(sf::Color color)
{
	type.setFillColor(color);
}
