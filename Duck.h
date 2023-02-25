#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Duck
{
private:
	//Variables
	sf::Sprite sprite;
	sf::Texture tex;
	int points;
	float xSpeed;
	float ySpeed;
	float rotation;

public:
	Duck();
	Duck(int _points, float _xSpeed, float _ySpeed);
	void setPoints(int _points);
	int getPoints();
	void setXSpeed(float _x);
	int getXSpeed();
	void setYSpeed(float _y);
	int getYSpeed();
	void setPosition(float _x, float _y);
	sf::Sprite getSprite();
	void drawSprite(sf::Texture _tex, sf::RenderTarget& _target);
	void moveSprite(float _x, float _y);
	void changeDirection();
};

