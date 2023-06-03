#pragma once
#include <iostream>
#include <string>
#include <map>
#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character
{
private:
	string name;
	string race;
	string profession;
	int maxHp;
	int currentHp;
	int armourClass;

	// Should be updated to use a vector or a list to stop it sorting alphabetically I hate this stupid language
	// do this another time, it works for now 
	map<string, int> i_skillPoints = {
		{"Strength", 0},
		{"Dexterity", 0},
		{"Constitution", 0},
		{"Intelligence", 0},
		{"Wisdom", 0},
		{"Charisma", 0},
	};

public:
	int level;

	Character();
	void createCharacter();
	string getName();
	void readCharacterSheet();
};

#endif

