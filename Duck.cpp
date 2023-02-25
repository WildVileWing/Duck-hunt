#include "Duck.h"

Duck::Duck()
{
	this->points = 1;
	this->xSpeed = 1.f;
	this->ySpeed = 0.f;
	this->rotation = -180.f;
}

Duck::Duck(int _points, float _xSpeed, float _ySpeed)
{
	this->points = _points;
	this->xSpeed = _xSpeed;
	this->ySpeed = _ySpeed;
	this->rotation = -180.f;
}

void Duck::setPoints(int _points)
{
	this->points = _points;
}

int Duck::getPoints()
{
	return this->points;
}

void Duck::setXSpeed(float _x)
{
	this->xSpeed = _x;
}

int Duck::getXSpeed()
{
	return xSpeed;
}

void Duck::setYSpeed(float _y)
{
	this->ySpeed = _y;
}

int Duck::getYSpeed()
{
	return ySpeed;
}

void Duck::setPosition(float _x, float _y)
{
	this->sprite.setPosition(_x, _y);
}

sf::Sprite Duck::getSprite()
{
	return this->sprite;
}

void Duck::drawSprite(sf::Texture _tex, sf::RenderTarget& _target)
{
	this->sprite.setScale(.2f, .2f);
	//this->sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->sprite.setTexture(_tex);
	_target.draw(this->sprite);
}

void Duck::moveSprite(float _x, float _y)
{
	this->sprite.move(_x, _y);
}

void Duck::changeDirection()
{
	this->xSpeed = -this->xSpeed;
}