#include "Game.h"
#include <ctime>
//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->player = Player(1);
	this->duckSpawnTimerMax = 40.f;
	this->duckSpawnTimer = this->duckSpawnTimerMax;
	this->duckMaxCount = 3;
}

void Game::initializeWindow()
{
	//Initialize window resolution
	this->videoMode.height = 600.f;
	this->videoMode.width = 800.f;
	this->window = new sf::RenderWindow(this->videoMode, "Duck Hunt", sf::Style::Titlebar | sf::Style::Close);
	
	//Application icon
	sf::Image windowIcon = sf::Image();
	windowIcon.loadFromFile("img/duckHunt.jpg");
	this->window->setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
	this->window->setFramerateLimit(60);
}

void Game::initializeDucks()
{
	//Create new object with parameters
	this->duck = Duck(1.f, 5.f, -2.f);
}

void Game::initializeFont()
{
	//Load fonts from directory
	if (!this->font.loadFromFile("Fonts/OpenSans-Light.ttf"))
		std::cout << "Failed to load font!" << "\n";
}

void Game::initializeText()
{
	//Create UI texts
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initializeWorld()
{
	//Initialize background
	if(!this->worldBackgroundTexture.loadFromFile("img/background.png"))
		std::cout << "Failed to load background!" << "\n";
	this->worldBackground.setTexture(this->worldBackgroundTexture);
	this->worldBackground.setScale(
		this->window->getSize().x / this->worldBackground.getLocalBounds().width,
		this->window->getSize().y / this->worldBackground.getLocalBounds().height);
}

//Contructors / Destructors 
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeFont();
	this->initializeWorld();
	this->initializeText();
	this->initializeDucks();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::spawnDucks()
{
	//Spawning ducks and sets position, color, adds to vector 
	this->duck.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->duck.getSprite().getTextureRect().width))/1.5,
		this->window->getSize().y+100);
	if(static_cast<int>(rand() % 2) == 1)
		this->duck.changeDirection();

	//Spawn the duck
	this->allDucks.push_back(this->duck);
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->events))
	{
		switch (this->events.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->events.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (this->events.key.code == sf::Keyboard::R)
			{
				if(this->player.getAmmoCurrent() < this->player.getAmmoMax())
					this->player.setAmmoCurrent(this->player.getAmmoMax());
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		Update mouse positions, relative to window 
	*/

	this->mousePositionInWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(this->mousePositionInWindow);
}

void Game::updateText()
{
	//Update UI Text
	std::stringstream ss;

	ss << "Score: " << this->player.getScore() << "\n"
	   << "Ammo: " << this->player.getAmmoCurrent() << " / " << this->player.getAmmoMax() << "\n";

	this->uiText.setString(ss.str());
}

void Game::updateDucks()
{
	//Updating the timer for ducks spawn
	if (this->allDucks.size() < this->duckMaxCount)
	{
		if (this->duckSpawnTimer >= this->duckSpawnTimerMax)
		{
			//Spawn duck and reset timer
			this->spawnDucks();
			this->duckSpawnTimer = 0.f;
		}
		else
		{
			this->duckSpawnTimer += 1.f;
		}
	}

	//Move and updating ducks
	for (int i = 0; i < this->allDucks.size(); i++)
	{
		bool deleted = false;

		this->allDucks[i].moveSprite(this->allDucks[i].getXSpeed(), this->allDucks[i].getYSpeed());

		if (this->allDucks[i].getSprite().getPosition().x >
			(this->window->getSize().x - this->allDucks[i].getSprite().getTextureRect().width * .2f))
		{
			this->allDucks[i].changeDirection();
		}
		else if (this->allDucks[i].getSprite().getPosition().x < 0)
		{
			this->allDucks[i].changeDirection();
		}

		if (this->allDucks[i].getSprite().getPosition().y  + this->allDucks[i].getSprite().getTextureRect().height * .2f <= 0)
		{
			this->allDucks.erase(this->allDucks.begin() + i);
		}
	}

	//Check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->player.getAmmoCurrent() > 0)
		{
				bool deleted = false;
				for (size_t i = 0; i < this->allDucks.size() && deleted == false; i++)
				{

					if (this->allDucks[i].getSprite().getGlobalBounds().contains(this->mousePositionView))
					{
						deleted = true;
						this->player.setAmmoCurrent(this->player.getAmmoCurrent() - 1);
						this->player.addScore(this->allDucks[i].getPoints());
						this->allDucks.erase(this->allDucks.begin() + i);
					}

				}
			
		}
	}
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();
	
	this->updateText();

	this->updateDucks();
}

//забилдить проект и скомплирировать

void Game::renderDucks(sf::RenderTarget& _target)
{
	sf::Texture duckObjectTexture;
	duckObjectTexture.loadFromFile("img/duck.png");
	
	//Rendering ducks
	for (auto& e : this->allDucks)
	{
		e.drawSprite(duckObjectTexture, _target);
		//_target.draw(e.getSprite());
	}
}

void Game::renderText(sf::RenderTarget& _target)
{
	_target.draw(this->uiText);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	/*
		Renders all game objects
	*/

	this->window->clear();
	
	//Draw background
	this->renderWorld();

	//Draw game
	this->renderDucks(*this->window);

	this->renderText(*this->window);

	this->window->display();
}