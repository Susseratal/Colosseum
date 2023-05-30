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
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;

public:
	int level;

	Character();
	void createCharacter();
	string getName();
	void readCharacterSheet();
};

#endif

