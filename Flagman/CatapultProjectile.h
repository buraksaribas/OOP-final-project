#pragma once
#include "Weapon.h"
class CatapultProjectile : public Weapon
{
public:
	CatapultProjectile() : Weapon("CatapultProjectile")
	{
	}
	~CatapultProjectile()
	{
		//std::cout << " ------>Destroy CatapultProjectile\n";
	}
	virtual int CalculateDamage(int power)
	{
		return power * 5 / (rand() % 20 + 10);
	}
};