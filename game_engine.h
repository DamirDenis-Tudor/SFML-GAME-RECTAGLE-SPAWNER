#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include<vector>
#include<time.h>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

class Game
{
private:
	//private variables
	sf::RenderWindow* renderWindow;
	sf::Event event;
	sf::VideoMode videoMode;
	
	//mouse position
	sf::Vector2i mousePos;
	sf::Vector2f viewMousePos;
		
	//dynamic objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//game logic
	float spawnTimer;
	float spwnTimerMax;
	unsigned maxEnemies;
	unsigned points;
	unsigned health;
	bool endGame;
	
	//font , text
	sf::Font font;
	sf::Text text;


	//private functions
	void initVariables();
	void initFont();
	void initText();
	void initWindow();
	void initEnemy();

public:
	//controctor and destructor
	Game();
	~Game();

	//bool functioning function
	const bool windowIsOpen();
	const bool isEvent();
	const bool endGameEv();

	//engine 
	void spawnEnemy();

	void poolEvents();
	
	void updateMousePos();
	void updateText();
	void updateEnemies();
	void update();

	void renderText();
	void renderEnemies();
	void render();
};

#endif

