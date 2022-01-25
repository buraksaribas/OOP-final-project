#pragma once
#include <iostream>
#include <string>
#include "Weapon.h"

class Army
{
public:
	virtual ~Army() 
	{
		//std::cout << " ---> Destroy " << weapon->GetName() << std::endl;
		delete weapon;
	};

	void Attack(Army& enemy) 
	{
		if (IsAlive() && enemy.IsAlive())
		{
			std::cout << name << " attacks " << enemy.GetName() << std::endl;
			ApplyDamage(enemy, weapon->CalculateDamage(power));
		}
	}

	void RecoveryHP() 
	{
		if (IsAlive() && hp < 100 && name != "Catapult")
		{
			int recovery = rand() % 10 + 1;
			std::cout << name << " recovers " << recovery << "HP." << std::endl;
			hp += recovery;
		}
	}

	bool IsAlive() { return hp > 0; }

	std::string GetName() { return name; }

	void ShowInfo() 
	{
		std::cout << "Name: " << name << std::endl;
		std::cout << "Health: " << hp << std::endl;
	}

protected:
	Army(std::string name, int hp, int power, Weapon* weapon)
		: name(name), hp(hp), power(power), weapon(weapon)
	{
		std::cout << name << " joined the army" << std::endl;
	}

	void ApplyDamage(Army& enemy, int damage) 
	{
		enemy.hp -= damage;
		if (enemy.hp < 0)
			enemy.hp = 0;

		std::cout << enemy.name << " takes " << damage << " damage." << std::endl;
		if (!enemy.IsAlive())
		{
			std::cout << "------------------------" << std::endl;
			std::cout << "| " << enemy.name << " died" << std::endl;
			std::cout << "------------------------" << std::endl;
		}
	}

	std::string name;
	int hp;
	int power;
	Weapon* weapon;
};

