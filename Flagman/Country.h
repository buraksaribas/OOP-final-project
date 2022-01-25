#pragma once
#include "World.h"
#include <iostream>
using namespace std;

class Country : public World
{
public:
	Country(string name, string ruler, int gold, int numberOfArmy, Player* player)
		: World(name, player), ruler(ruler), numberOfArmy(numberOfArmy), gold(gold)
	{
		for (int i = 0; i < numberOfArmy; i++)
		{
			int rndm = rand() % 3 + 1;
			if (rndm == 1)
				army.push_back(new Bowman("Enemy Bowman", new Bow));
			if (rndm == 2)
				army.push_back(new Swordsman("Enemy Swordsman", new Sword));
			if (rndm == 3)
				army.push_back(new Cavalry("Enemy Cavalry", new Pillum));
		}
	}

	~Country()
	{
		for (int i = 0; i < army.size(); i++)
			delete army[i];
	}

	void Info()
	{
		cout << "\n ------------------------------------------------------- " << endl;
		cout << " | Welcome to " << name << endl;
		cout << " | Ruler: " << ruler << endl;
		cout << " -------------------------------------------------------" << endl;
		cout << " | Army: " << army.size() << endl;
		cout << " | Gold: " << gold << endl;
		cout << " -------------------------------------------------------" << endl;
		cout << " press Enter to continue" << endl;
		cin.get();
	}

	void Action()
	{
		cout << name << endl;
		cout << "-------------" << endl;
		cout << " Army: " << army.size() << endl;

		if (name == "THE ROMAN EMPIRE")
			cout << "\n [1] - Ask for help" << endl;
		else
			cout << "\n [1] - Attack" << endl;
		cout << " [2] - Trade" << endl;
		if (name == "THE ROMAN EMPIRE")
			cout << " [3] - Give flag" << endl;
		else
			cout << " [3] - Tips" << endl;
		cout << " [4] - Hire soldiers" << endl;
		if (name == "THE ROMAN EMPIRE")
			cout << " [5] - Build an catapult" << endl;
		cout << " >> ";
		int choice;
		cin >> choice;
		cin.ignore();
		if (choice == 1)
		{
			if (name == "THE ROMAN EMPIRE")
				cout << " You dont need help go away!!!" << endl;
			else
			{
				bool combat = true;
				int count = 0;
				while (combat && count < 3 && player->army.size() > 0)
				{
					if (army.size() > 0)
					{
						if (army.size() < player->army.size())
						{
							for (int i = 0; i < army.size(); i++)
							{
								if (player->army.size() < army.size())
									break;
								player->army[i]->Attack(*army[i]);
								army[i]->Attack(*player->army[i]);
								army[i]->RecoveryHP();
								player->army[i]->RecoveryHP();

								if (player->army[i]->GetName() == "Catapult")
								{
									for (int j = 0; j < army.size(); j++)
									{
										player->army[i]->Attack(*army[j]);
										gold -= 10;
										player->resource[3]->SetAmount(player->resource[3]->GetAmount() + 10);
										delete army[i];
										army.erase(army.begin() + i);
									}
								}

								if (!army[i]->IsAlive())
								{
									gold -= 10;
									player->resource[3]->SetAmount(player->resource[3]->GetAmount() + 10);
									delete army[i];
									army.erase(army.begin() + i);
								}
								if (!player->army[i]->IsAlive())
								{
									if (player->army[i]->GetName() == "Bowman")
										Player::bowmans--;
									if (player->army[i]->GetName() == "Swordsman")
										Player::swordsmans--;
									if (player->army[i]->GetName() == "Cavalry")
										Player::cavalries--;
									if (player->army[i]->GetName() == "Catapult")
										Player::catapults--;
									delete player->army[i];
									player->army.erase(player->army.begin() + i);
								}
							}
						}
						else
						{
							for (int i = 0; i < player->army.size(); i++)
							{
								
								if (player->army.size() > army.size())
									break;
								player->army[i]->Attack(*army[i]);
								army[i]->Attack(*player->army[i]);
								army[i]->RecoveryHP();
								player->army[i]->RecoveryHP();

								if (player->army[i]->GetName() == "Catapult")
								{
									for (int j = 0; j < army.size(); j++)
									{
										player->army[i]->Attack(*army[j]);
										gold -= 10;
										player->resource[3]->SetAmount(player->resource[3]->GetAmount() + 10);
										delete army[i];
										army.erase(army.begin() + i);
									}
								}

								if (!army[i]->IsAlive())
								{
									gold -= 10;
									player->resource[3]->SetAmount(player->resource[3]->GetAmount() + 10);
									delete army[i];
									army.erase(army.begin() + i);
								}
								if (!player->army[i]->IsAlive())
								{
									if (player->army[i]->GetName() == "Bowman")
										Player::bowmans--;
									if (player->army[i]->GetName() == "Swordsman")
										Player::swordsmans--;
									if (player->army[i]->GetName() == "Cavalry")
										Player::cavalries--;
									if (player->army[i]->GetName() == "Catapult")
										Player::catapults--;
									delete player->army[i];
									player->army.erase(player->army.begin() + i);
								}
							}
						}

						cout << " press Enter to continue" << endl;
						cin.get();
						system("cls");
						cout << "The state of your army after the combat" << endl;
						cout << "---------------------" << endl;
						for (int i = 0; i < player->army.size(); i++)
							player->army[i]->ShowInfo();
						cout << "---------------------" << endl;

						if (army.size() < 1)
						{
							cout << "You took the flag of " << name << endl;
							player->SetFlag(true);
						}
						count++;
						if (count == 3)
						{
							cout << " It's getting dark, you have to wait for the morning" << endl;
						}
						else
						{
							char c;
							cout << " Atack again? (y or n): ";
							cin >> c;
							cin.ignore();
							if (c == 'n')
								combat = false;
						}
					}
					else
					{
						cout << name << " already destroyed" << endl;
						break;
					}
				}
			}
		}
		else if (choice == 2)
		{
			system("cls");
			int foodOffer = rand() % 10 + 1;
			int waterOffer = rand() % 10 + 1;
			int woodOffer = rand() % 10 + 1;
			while (true)
			{
				cout << " ******************** Market ********************" << endl;
				player->PrintInfo();
				cout << "\n - Market's offer -" << endl;
				cout << "\t-> 1 portion of food: " << foodOffer << endl;
				cout << "\t-> 1 liter of water: " << waterOffer << endl;
				cout << "\t-> 1 ton pf Wood: " << woodOffer << endl;
				cout << " ************************************************" << endl;
				cout << "Sell -> [1] - Food\t[2] - Water\t[3] - Wood\t[0] - Quit\n >> ";
				int sell, amount;
				cin >> sell;
				cin.ignore();
				if (sell == 0)
					break;
				cout << "Enter amount\n >> ";
				cin >> amount;
				cin.ignore();
				if (sell == 1)
				{
					cout << "You earnd " << foodOffer * amount << " gold coins " << endl;
					int dec = player->resource[0]->GetAmount() - amount;
					player->resource[0]->SetAmount(dec);
					int inc = player->resource[3]->GetAmount() + foodOffer * amount;
					player->resource[3]->SetAmount(inc);
				}
				else if (sell == 2)
				{
					cout << "You earnd " << waterOffer * amount << " gold coins " << endl;
					int dec = player->resource[2]->GetAmount() - amount;
					player->resource[2]->SetAmount(dec);
					int inc = player->resource[3]->GetAmount() + waterOffer * amount;
					player->resource[3]->SetAmount(inc);
				}
				else if (sell == 3)
				{
					cout << "You earnd " << woodOffer * amount << " gold coins " << endl;
					int dec = player->resource[1]->GetAmount() - amount;
					player->resource[1]->SetAmount(dec);
					int inc = player->resource[3]->GetAmount() + woodOffer * amount;
					player->resource[3]->SetAmount(inc);
				}
				else
					cout << "Invalid input";
			}
		}
		else if (choice == 3)
		{
			if (name == "THE ROMAN EMPIRE")
			{
				cout << " Did you bring the Flag?" << endl;
				if (!player->GetFlags())
					cout << "\n Do not come back without the flag" << endl;
			}
			else
				cout << tips[rand() % 5];
		}
		else if (choice == 4)
		{
			int bowOffer = rand() % 20 + 1;
			int swordOffer = rand() % 30 + 15;
			int cavalOffer = rand() % 40 + 25;
			int avalBow = rand() % 100 + 1;
			int avalSword = rand() % 100 + 1;
			int avalCaval = rand() % 100 + 1;

			cout << " ******************** Mercenary ********************" << endl;
			cout << " -------------------User Army --------------------------" << endl;
			cout << " | Army      : " << player->army.size() << endl;
			cout << " | Gold      : " << player->resource[3]->GetAmount() << " coins" << endl;
			cout << " ----- Salaries for units ---------Available--------------------" << endl;
			cout << " | Bowman    : " << bowOffer << "\t\t\t" << avalBow << endl;
			cout << " | Swordsman : " << swordOffer << "\t\t\t" << avalSword << endl;
			cout << " | Cavalry   : " << cavalOffer << "\t\t\t" << avalCaval << endl;
			cout << " Hire\n[1] - Bowman\t[2] - Swordsman\t[3] - Cavalry\t[0] - Quit" << endl;
			cout << " >> ";
			int choice;
			cin >> choice;
			cin.ignore();

			cout << " Enter amount of soldiers to hire" << endl;
			cout << " >> ";
			int hire;
			cin >> hire;
			cin.ignore();
			if (choice != 0)
			{
				if (choice == 1 && hire <= avalBow)
				{
					if (player->resource[3]->GetAmount() > (hire * bowOffer))
					{
						cout << "\n You hired " << hire << "bowman " << hire * bowOffer << " gold coins" << endl;
						for (int i = 0; i < hire; i++)
						{
							player->army.push_back(new Bowman("Bowman", new Bow));
							Player::bowmans++;
						}
						player->resource[3]->SetAmount(player->resource[3]->GetAmount() - hire * bowOffer);
					}
					else
						cout << "You don't have enough gold coins" << endl;

				}
				else if (choice == 2 && hire <= avalSword)
				{
					if (player->resource[3]->GetAmount() > (hire * swordOffer))
					{
						cout << "\n You hired " << hire << "swordsman " << hire * swordOffer << " gold coins" << endl;
						for (int i = 0; i < hire; i++)
						{
							Player::swordsmans++;
							player->army.push_back(new Swordsman("Swordsman", new Sword));
						}
						player->resource[3]->SetAmount(player->resource[3]->GetAmount() - hire * cavalOffer);
					}
					else
						cout << "You don't have enough gold coins" << endl;

				}
				else if (choice == 3 && hire <= avalCaval)
				{
					if (player->resource[3]->GetAmount() > (hire * cavalOffer))
					{
						cout << "\n You hired " << hire << "swordsman " << hire * cavalOffer << " gold coins" << endl;
						for (int i = 0; i < hire; i++)
						{
							Player::cavalries++;
							player->army.push_back(new Cavalry("Cavalry", new Pillum));
						}
						player->resource[3]->SetAmount(player->resource[3]->GetAmount() - hire * cavalOffer);
					}
					else
						cout << "You don't have enough gold coins" << endl;

				}
				else
					"Invalid input";
			}
		}
		else if (choice == 5)
		{
			if (player->resource[1]->GetAmount() > 999)
			{
				player->army.push_back(new Catapult("Catapult", new CatapultProjectile));
				player->resource[1]->SetAmount(player->resource[1]->GetAmount() - 1000);
				Player::catapults++;
			}
			else
				cout << "You don't have enough woods. It should be at least 1000";
		}
		else
			cout << " Invalid input!!" << endl;
	}
	string tips[5] = {
		"You can get gold coins by killing soldiers.",
		"Remember to save some gold coins for salaries.",
		"You can get drinkable water from THE DANUBE.",
		"Be careful about your resources, if thy get low some soldiers can leave your army.",
		"You can build catapult only in THE ROMAN EMPIRE."
	};
private:
	vector<Army*> army;
	string ruler;
	int numberOfArmy;
	int gold;
};