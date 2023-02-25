#pragma once

#include <sstream>
#include "Player.h"
#include "Duck.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>	

/*
	Game engine class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event events;

	//Mouse positions
	sf::Vector2i mousePositionInWindow;
	sf::Vector2f mousePositionView;

	//Game logic
	bool endGame;
	float duckSpawnTimer;
	float duckSpawnTimerMax;
	int duckMaxCount;

	//Resources
	sf::Texture duckTexture;
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;

	//Text
	sf::Font font;
	sf::Text uiText;

	//Game objects
	std::vector<Duck> allDucks;
	Duck duck;	
	Player player;

	//Private functions
	void initializeVariables();
	void initializeWindow();
	void initializeDucks();
	void initializeText();
	void initializeFont();
	void initializeWorld();

public:
	//Contructors / Destructors 
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnDucks();
	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateDucks();
	void update();

	void renderWorld();
	void renderText(sf::RenderTarget& _target);
	void renderDucks(sf::RenderTarget& _target);
	void render();
};