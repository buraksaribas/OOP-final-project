#pragma once
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

class World 
{
public:
	World(string name, Player* player) 
		: name(name), player(player), north(NULL), east(NULL), west(NULL), south(NULL)
	{
	}
	~World(){}
	virtual void Info() = 0;
	virtual void Action() = 0;
	void PrintLocation() { 
		cout << "You are in " << name << endl; 
	}

	World* GetNorth() { return north; }
	World* GetEast() { return east; }
	World* GetSouth() { return south; }
	World* GetWest() { return west; }
	string GetName() { return name; }

	void SetMap(World* north, World* east, World* south, World* west)
	{
		this->north = north;
		this->east = east;
		this->south = south;
		this->west = west;
	}
	void SetPlayer(Player* player)
	{
		this->player = player;
	}

protected:
	string name;
	Player* player;

	World* north;
	World* east;
	World* south;
	World* west;
};