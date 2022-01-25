#pragma once
#include "World.h"

class Mountain :public World
{
public:
	Mountain(string name, Player* player, int food, int wood, int gold)
		: World(name, player), food(food), wood(wood), gold(gold)
	{
	}
	~Mountain()
	{
	}
	void Info()
	{
		cout << "\n ------------------------------------------------------- " << endl;
		cout << " Welcome to " << name << std::endl;
		cout << " Food resources " << food << std::endl;
		cout << " Wood resources " << wood << std::endl;
		cout << " Gold resources " << gold << std::endl;
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
		cout << " Available gold to dig: " << food << endl;

		cout << "\n [1] - Chop wood" << endl;
		cout << " [2] - Hunt animal " << endl;
		cout << " [3] - Dig gold" << endl;
		cout << " >> ";
		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			int choppedWood = (rand() % 26 + 1);
			wood -= choppedWood;
			cout << "\n You chopped " << choppedWood << " tons of wood" << endl;
			int addWood = player->resource[1]->GetAmount() + choppedWood;
			player->resource[1]->SetAmount(addWood);
		}
		else if (choice == 2)
		{
			int gatheredFood = (rand() % 23 + 12);
			food -= gatheredFood;
			cout << " You gathered " << gatheredFood << " poritons of food" << endl;
			int addFood = player->resource[0]->GetAmount() + gatheredFood;
			player->resource[0]->SetAmount(addFood);
		}
		else if (choice == 3)
		{
			int diggedGold = (rand() % 21 + 12);
			gold -= diggedGold;
			cout << " You digged " << diggedGold << " gold" << endl;
			int addGold = player->resource[3]->GetAmount() + diggedGold;
			player->resource[3]->SetAmount(addGold);
		}
	}
public:
	int gold;
	int wood;
	int food;
};