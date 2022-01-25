#pragma once
#include "World.h"
#include "Country.h"
#include "Mountain.h"
#include "SeaRiver.h"
#include "Forest.h"
#include <ctime>
class Game
{
private:
	int day;
	int remainingDays;
	int direction;
	bool gameOver;
	string username;

	World* location;
	World* germans;
	World* francia;
	World* roman;
	World* norse;
	World* persian;
	World* barbarian;
	World* alps;
	World* hercy;
	World* danube;
	World* meditarian;
	World* northsea;
	//World** worlds;
	Player* player;

public:
	Game()
	{
		PrintStart();

		srand((unsigned)time(NULL));
		day = 1;
		remainingDays = 123;
		direction = 0;
		gameOver = false;
		location = NULL;

		player = new Player(username, 100, 100, 100, 100, 15);

		germans = new Country("THE GERMAN KINGDOM", "Ludwig der Deutsche", 10000, 200, NULL);
		francia = new Country("FRANCIA", "Clovis I", 20000, 150, NULL);
		roman = new Country("THE ROMAN EMPIRE", "Augustus", 50000, 1000, player);
		norse = new Country("THE NORSE KINGDOM", "Nori", 30000, 200, NULL);
		persian = new Country("PERSIAN EMPIRE", "Deioces", 50000, 300, NULL);
		barbarian = new Country("BARBARIANS", "Arminius", 1000, 120, NULL);
		alps = new Mountain("THE ALPS", NULL, 1000, 7000, 9000);
		hercy = new Forest("HERCYNIAN FOREST", NULL, 4000, 10000);
		danube = new SeaRiver("THE DANUBE", NULL, 3000, 200000);
		meditarian = new SeaRiver("THE MEDITARIAN SEA", NULL, 5000, 0);
		northsea = new SeaRiver("THE NORTH SEA", NULL, 4000, 0);
	}
	~Game()
	{
		delete germans;
		delete francia;
		delete roman;
		delete norse;
		delete persian;
		delete barbarian;
		delete alps;
		delete hercy;
		delete danube;
		delete meditarian;
		delete northsea;

		delete player;
		delete location;
	}
	void InitMap()
	{
		germans->SetMap(NULL, northsea, alps, hercy);
		francia->SetMap(NULL, alps, NULL, NULL);
		roman->SetMap(alps, NULL, meditarian, barbarian);
		norse->SetMap(NULL, NULL, northsea, NULL);
		persian->SetMap(danube, NULL, NULL, NULL);
		barbarian->SetMap(NULL, roman, NULL, NULL);
		alps->SetMap(germans, danube, roman, francia);
		hercy->SetMap(NULL, germans, NULL, NULL);
		danube->SetMap(northsea, NULL, persian, alps);
		meditarian->SetMap(roman, NULL, NULL, NULL);
		northsea->SetMap(norse, NULL, danube, germans);

		location = roman;
	}
	void StartGame()
	{
		InitMap();

		while (remainingDays > 0 && !gameOver)
		{
			Play();
			//system("cls");
		}
		if (remainingDays < 1)
		{
			cout << " RAN OUT OF TIME! YOU FAILED" << endl;
			cin.get();
		}
	}

	void Play()
	{
		PrintStats();
		cout << "\n General " << username << ", give me an order!\n" << endl;
		cout << " [1] - Look Map" << endl;
		cout << " [2] - Actions" << endl;
		cout << " [3] - Travel" << endl;
		cout << " >> ";
		int choice;
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			system("cls");
			PrintMap();
			cout << "press Enter to continue" << endl;
			cin.get();
		}
		else if (choice == 2)
		{
			location->Action();

			if (player->army.size() < 1)
			{
				cout << "\n All your soldiers have been defeated!" << endl;
				cout << " The enemy captures you!" << endl;
				cout << " You lost the game" << endl;

				gameOver = true;
				location = NULL;
				return;
			}

			if (player->GetFlags() == true)
				cout << " You have captured all flag! Return to emperor" << endl;

			if (player->GetFlags() == true && location->GetName() == "THE ROMAN EMPIRE")
			{
				cout << "\n Congratulations General, " << username << endl;
				cout << " You are victorious\n" << endl;

				gameOver = true;
				location = NULL;
				return;
			}
			cout << "\n Press ENTER to continue" << endl;
			std::cin.get();
			NextDay(1);
		}
		else if (choice == 3)
		{
			TravelMenu();
			Travel();
			NextDay(2);
		}
	}

	void NextDay(int day)
	{
		this->day += day;
		remainingDays -= day;
		player->resource[0]->SetAmount(player->resource[0]->GetAmount()
			- (player->army.size() / 10 * day + Player::cavalries / 10));
		player->resource[1]->SetAmount(player->resource[1]->GetAmount()
			- (player->army.size() / 10 * day + Player::cavalries / 10));
		player->resource[2]->SetAmount(player->resource[2]->GetAmount()
			- (player->army.size() / 7 * day + Player::cavalries / 10));
		player->resource[3]->SetAmount(player->resource[3]->GetAmount()
			- (player->army.size() / 8 * day + Player::cavalries / 10));

		for (int i = 0; i < player->army.size(); i++)
			player->army[i]->RecoveryHP();

		for (int i = 0; i < 4; i++)
		{
			if (i == 1) continue;
			if (player->resource[i]->GetAmount() < 10)
			{
				cout << " Your " << player->resource[i]->GetName() << " are low!!!" << endl;
				cout << " Some soldiers left you" << endl;
				for (int i = 0; i < player->army.size(); i++)
				{
					int index = rand() % player->army.size();
					if (player->army[index]->GetName() == "Bowman")
						Player::bowmans--;
					if (player->army[index]->GetName() == "Swordsman")
						Player::swordsmans--;
					if (player->army[index]->GetName() == "Cavalry")
						Player::cavalries--;
					delete player->army[index];
					player->army[index] = NULL;
					player->army.erase(player->army.begin() + index);
				}
			}
		}
		for (int i = 0; i < 4; i++)
			if (player->resource[i]->GetAmount() < 1) player->resource[i]->SetAmount(0);
	}

	void TravelMenu()
	{
		PrintMap();
		cout << " \n\n\t[1] - North\t[2] - East\t[3] - South\t[4] - West\n" << endl;
		cout << " >> ";
		int choice;
		cin >> choice;
		cin.ignore();
		direction = choice;
	}

	void Travel()
	{
		if (direction == 1)
		{
			if (location->GetNorth() == NULL)
			{
				cout << "\n uncharted territory" << endl;
				cout << " Please chose a different location\n";
				cout << " >> ";
				TravelMenu();
				Travel();
			}
			else
			{
				location->SetPlayer(NULL);
				location = location->GetNorth();
				location->SetPlayer(player);
				location->Info();
			}
		}
		else if (direction == 2)
		{
			if (location->GetEast() == NULL)
			{
				cout << "\n uncharted territory" << endl;
				cout << " Please chose a different location\n";
				cout << " >> ";
				TravelMenu();
				Travel();
			}
			else
			{
				location->SetPlayer(NULL);
				location = location->GetEast();
				location->SetPlayer(player);
				location->Info();
			}
		}
		else if (direction == 3)
		{
			if (location->GetSouth() == NULL)
			{
				cout << "\n uncharted territory" << endl;
				cout << " Please chose a different location\n";
				cout << " >> ";
				TravelMenu();
				Travel();
			}
			else
			{
				location->SetPlayer(NULL);
				location = location->GetSouth();
				location->SetPlayer(player);
				location->Info();
			}
		}
		else if (direction == 4)
		{
			if (location->GetWest() == NULL)
			{
				cout << "\n uncharted territory" << endl;
				cout << " Please chose a different location\n";
				cout << " >> ";
				TravelMenu();
				Travel();
			}
			else
			{
				location->SetPlayer(NULL);
				location = location->GetWest();
				location->SetPlayer(player);
				location->Info();
			}
		}
	}

	void PrintStats()
	{
		cout << "\n" << endl;
		cout << " ------------------------------------------------------- " << endl;
		cout << " | Current Day: " << day << endl;
		cout << " | Current Location: "; location->PrintLocation();
		cout << " | Remaining days: " << remainingDays << endl;
		cout << " -------------------------------------------------------" << endl;
		player->PrintInfo();
		cout << "\n ------------------------------------------------------- " << endl;
	}

	void PrintMap()
	{
		cout << endl << endl;
		cout << "   _____________________________________________________________________" << endl;
		cout << "   |                              NORTH                                |" << endl;
		cout << "   |      ^                                                            |" << endl;
		cout << "   |     / \\      **********                 THE NORSE KINGDOM         |" << endl;
		cout << "   |    /_ _\\       **********                     |                   |" << endl;
		cout << "   |      |                                        |          ~~ ~~    |" << endl;
		cout << "   |	  HERCYNIAN  ---- THE GERMAN  -------- THE NORTH SEA   ~~      |" << endl;
		cout << "   |       FOREST          KINGDOM                 |         ~~ ~~     |" << endl;
		cout << "   |                          |                    |         ~~ ~~     |" << endl;
		cout << "   |                       /\\ |  /\\                |                   |" << endl;
		cout << "   |                      /  \\| /  \\               |                   |" << endl;
		cout << "   |WEST    FRANCIA ------ THE ALPS  --------- THE DANUBE          EAST|" << endl;
		cout << "   |                          |                    |   ~~              |" << endl;
		cout << "   |                          |                    |  ~                |" << endl;
		cout << "   |                          |                   /  ~                 |" << endl;
		cout << "   |    BARBARIANS  ----  THE ROMAN           PERSIAN                  |" << endl;
		cout << "   |                        EMPIRE            EMPIRE                   |" << endl;
		cout << "   |                          |                                        |" << endl;
		cout << "   |                          |                                        |" << endl;
		cout << "   |                  THE MEDITARIAN SEA                   *******     |" << endl;
		cout << "   |   ~~~~  ~~   ~~~~     ~~~~~~~       ~~~~           *********      |" << endl;
		cout << "   |    ~~~~~   ~~      ~~~        SOUTH               ********        |" << endl;
		cout << "   |___________________________________________________________________|" << endl;
		cout << endl;
		location->PrintLocation();
	}

	void PrintStart()
	{
		cout << endl << endl;
		cout << "   __===========================================================       "<< endl;
		cout << "  |  |                                                          |      "<< endl;
		cout << "  |  |	 _____  _         _      ____  __  __     _     _   _   |       "<< endl;
		cout << "  |  |	|  ___|| |       / \\    / ___||  \\/  |   / \\   | \\ | |  |   "<< endl;
		cout << "  |  |	| |_   | |      / _ \\  | |  _ | |\\/| |  / _ \\  |  \\| |  |   "<< endl;
		cout << "  |  |	|  _|  | |___  / ___ \\ | |_| || |  | | / ___ \\ | |\\  |  |    "<< endl;
		cout << "  |  |	|_|    |_____|/_/   \\_\\ \\____||_|  |_|/_/   \\_\\|_| \\_|  | "<< endl;
		cout << "  |  |                                                          |" << endl;
		cout << "  |  |                                                          |" << endl;
		cout << "  |  |=========================================================="  << endl;
		cout << "  |  |" << endl;
		cout << "  |  |" << endl;
		cout << "  |  |                        20040301051		 " << endl;
		cout << "  |  |                       Burak Saribas		 " << endl;
		cout << "  |  |" << endl;
		cout << "  |  |" << endl;
		cout << "  |  |" << endl;
		cout << "  |__|                    Press Enter to Play..." << endl << endl;
		cin.get();
		system("cls");
		cout << "Enter your name: ";
		getline(cin, username);
		cout << " Welcome general " << username << endl;
		cout << " Your mission is to conquer all countries \nand bring their flags to the Eoman Emperor Augustus " << endl;
		cout << " ... " << endl;
		cout << " press Enter to continue" << endl;
		cin.get();
	}
};


