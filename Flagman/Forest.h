#pragma once
#include "World.h"
class Forest : public World
{
public:
	Forest(string name, Player* player, int food, int wood) 
		: World(name, player), food(food), wood(wood)
	{
	}
	~Forest()
	{
	}

	void Info()
	{
		cout << "\n ------------------------------------------------------- " << endl;
		cout << " Welcome to " << name << std::endl;
		cout << " Food resources " << food << std::endl;
		cout << " Wood resources " << wood << std::endl;
		cout << " -------------------------------------------------------" << endl;
		cout << " press Enter to continue" << endl;
		cin.get();
	}

	void Action()
	{
		cout << name << endl;
		cout << "-------------" << endl;
		cout << " Available wood to chop: " << wood << endl;
		cout << " Available food to gather: " << food << endl;
		cout << "\n [1] - Chop wood" << endl;
		cout << " [2] - Gather food" << endl;
		cout << " >> ";
		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			int choppedWood = (rand() % 250 + 10);
			wood -= choppedWood;
			cout << "\n Your party chopped " << choppedWood << " tons of wood" << endl;
			int addWood = player->resource[1]->GetAmount() + choppedWood;
			player->resource[1]->SetAmount(addWood);
		}
		else if (choice == 2)
		{
			int gatheredFood = (rand() % 120 + 12);
			food -= gatheredFood;
			cout << " Your party gathered " << gatheredFood << " portions of food" << endl;
			int addFood = player->resource[0]->GetAmount() + gatheredFood;
			player->resource[0]->SetAmount(addFood);
		}
	}
private:
	int food;
	int wood;
};