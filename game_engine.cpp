#include "game_engine.h"

//init functions
void Game::initVariables()
{
	this->renderWindow = nullptr;

	//game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->spwnTimerMax = 10.f;
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
void Game::initEnemy()
{
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::Blue);
}

//contructor and destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
	this->initEnemy();
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

	//color and position
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->renderWindow->getSize().x - this->enemy.getSize().x)),
		0.f
		);
	this->enemy.setFillColor(sf::Color::Yellow);

	//update vector elements
	this->enemies.push_back(this->enemy);

	//remove from bottom

}

void Game::poolEvents()
{
	while (this->isEvent())
	{
		//close mecanism
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
		this->enemies[index].move(0.f, 1.f);

		//check if mouse is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[index].getGlobalBounds().contains(this->viewMousePos))
			{
				this->points += 5;
				deleted = true;
			}
		}

		//check if enemy is bellow the screen
		if (this->videoMode.height <= this->enemies[index].getPosition().y)
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
		this->renderWindow->draw(e);
	}
}

void Game::render()
{
	/*
		return void
			->clear old frame
			->draw next one and text
			->display
	*/

	this->renderWindow->clear();

	this->renderEnemies();
	this->renderText();

	this->renderWindow->display();

}