#pragma once
#include "Army.h"
#include "Resource.h"
#include "Food.h"
#include "Bowman.h"
#include "Swordsman.h"
#include "Cavalry.h"
#include "Pillum.h"
#include "Sword.h"
#include "Bow.h"
#include "Catapult.h"
#include "CatapultProjectile.h"
#include <vector>

using namespace std;
class Player
{
public:
	Player(std::string name, int food, int wood, int water, int gold, int numberOfArmy)
		: food(food), wood(wood), water(water), gold(gold), numberOfArmy(numberOfArmy)
	{
		for (int i = 0; i < 5; i++)
			flags[i] = false;
		resource = new Resource * [4];
		resource[0] = new Food("Food", food);
		resource[1] = new Food("Wood", wood);
		resource[2] = new Food("Water", water);
		resource[3] = new Food("Gold", gold);

		cout << "The emperor give you " << numberOfArmy << " soldiers" << endl;
		cout << "You can choose type of soldiers " << endl;

		for (int i = 0; i < numberOfArmy; i++)
		{
			int choice;
			cout << " Remaining choice: " << numberOfArmy - i;
			cout << " Choose your soldier type: " << endl;
			cout << " [1] - Bowman";
			cout << " [2] - Swordsman";
			cout << " [3] - Cavalry";
			cout << " >>";
			cin >> choice;
			cin.ignore();

			if (choice == 1)
			{
				army.push_back(new Bowman("Bowman", new Bow));
				bowmans++;
			}
			else if (choice == 2)
			{
				army.push_back(new Swordsman("Swordsman", new Sword));
				swordsmans++;
			}
			else if (choice == 3)
			{
				army.push_back(new Cavalry("Cavalry", new Pillum));
				cavalries++;
			}
			else
				cout << " Invalid input!!" << endl;
		}
	}

	~Player()
	{
		for (int i = 0; i < army.size(); i++)
			delete army[i];

		for (int i = 0; i < 4; i++)
			delete resource[i];
		delete[] resource;
	}

	bool GetFlags() {
		for (int i = 0; i < 5; i++)
		{
			if (flags[i] == false)
				return false;
		}
		return true; 
	}
	void SetFlag(bool flag) {
		for (int i = 0; i < 5; i++)
		{
			if (flags[i] == true)
				continue;
			flags[i] = true;
			break;
		}
	}

	void PrintInfo()
	{
		cout << " - User Army -" << endl;
		cout << "\t-> Army count: " << army.size() << "  soldiers" << endl;
		cout << "\t-> Bowman: " << bowmans << endl;
		cout << "\t-> Swordman: " << swordsmans << endl;
		cout << "\t-> Cavalry: " << cavalries << endl;
		cout << "\t-> Catapult: " << catapults << endl;
		cout << " - User Resources -" << endl;
		cout << "\t-> " << resource[0]->GetName() << ": " 
					  << resource[0]->GetAmount() << "  portions of food" << endl;
		cout << "\t-> " << resource[2]->GetName() << ": "
					  << resource[2]->GetAmount() << " liters of drinking water" << endl;
		cout << "\t-> " << resource[1]->GetName() << ": "
					  << resource[1]->GetAmount() << "  tons of wood" << endl;
		cout << "\t-> " << resource[3]->GetName() << ": "
					  << resource[3]->GetAmount() << "  gold coins" << endl;
		cout << "\t-> Flags: ";
		for (int i = 0; i < 5; i++)
		{
			if (flags[i])
				cout << " |> ";
		}
	}
	

	vector<Army*> army;
	static int bowmans;
	static int swordsmans;
	static int cavalries;
	static int catapults;
	Resource** resource;
private:
	bool flags[5];
	std::string name;
	int food;
	int wood;
	int water;
	int gold;
	int numberOfArmy;

};

int Player::bowmans = 0;
int Player::swordsmans = 0;
int Player::cavalries = 0;
int Player::catapults = 0;