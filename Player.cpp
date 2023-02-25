#include "Player.h"

Player::Player()
{
    this->ammoMax = 2;
    this->ammoCurrent = this->ammoMax;
    this->score = 0;
}

Player::Player(int _ammoMax)
{
    this->ammoMax = _ammoMax;
    this->ammoCurrent = this->ammoMax;
    this->score = 0;
}

void Player::addScore(int _points)
{
    this->score += _points;
}

int Player::getScore()
{
    return this->score;
}

void Player::setAmmoCurrent(int _ammo)
{
    this->ammoCurrent = _ammo;
}

int Player::getAmmoCurrent()
{
    return this->ammoCurrent;
}

void Player::setAmmoMax(int _ammo)
{
    this->ammoMax = _ammo;
}

int Player::getAmmoMax()
{
    return this->ammoMax;
}