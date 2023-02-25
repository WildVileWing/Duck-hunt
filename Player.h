#pragma once
class Player
{
private:
	int score;
	int ammoCurrent;
	int ammoMax;
public:
	Player();
	Player(int _ammoMax);

	void addScore(int _points);
	int getScore();
	void setAmmoCurrent(int _ammo);
	int getAmmoCurrent();
	void setAmmoMax(int _ammo);
	int getAmmoMax();

};

