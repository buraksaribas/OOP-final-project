#pragma once
#include "World.h"
class SeaRiver : public World
{
public:
	SeaRiver(string name, Player* player, int food, int water)
		: World(name, player), food(food), water(water)
	{
	}
	~SeaRiver() {}
	void Info()
	{
		cout << "\n ------------------------------------------------------- " << endl;
		cout << "Welcome to " << name << endl;
		cout << "Food: " << food << endl;
		cout << "Water: " << water << endl;
		cout << " -------------------------------------------------------" << endl;	
		cout << " press Enter to continue" << endl;
		cin.get();
	}
	void Action()
	{
		cout << name << endl;
		cout << "-------------" << endl;
		cout << " Available food to gather: " << food << endl;
		cout << " Available water to gather: " << water << endl;

		cout << "\n [1] - Fishing" << endl;
		cout << " [2] - Get water" << endl;
		cout << " >> " << endl;

		int choice;
		cin >> choice;
		cin.ignore();
		if (choice == 1)
		{
			int gatheredFood = rand() % 250 + 15;
			food -= gatheredFood;
			cout << " You caught " << gatheredFood << " fish" << endl;
			int addFood = player->resource[0]->GetAmount() + gatheredFood;
			player->resource[0]->SetAmount(addFood);
		}
		else if (choice == 2)
		{
			if (name != "THE MEDITARIAN SEA" && name != "THE NORTH SEA")
			{
				int gatheredWater = rand() % 250 + 15;
				water -= gatheredWater;
				cout << " You gathered " << gatheredWater << " liters of water" << endl;
				int addWater = player->resource[2]->GetAmount() + gatheredWater;
				player->resource[2]->SetAmount(addWater);
			}
			else
				cout << " Salt water is not drinkable" << endl;
		}
	}
private:
	int food;
	int water;
};