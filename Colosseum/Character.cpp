#include "Character.h"
#include "Engine.h"

using namespace std;

Engine* engine;

Character::Character() {
	engine = new Engine();
	createCharacter();
}

void Character::createCharacter() {
	int choiceIndex;
	int optionsLen;
	string tmpRow;
	level = 1;

	system("cls");
	string title = "\t========== CHARACTER CREATOR ==========\n"; 
	cout << title;
	cout << "Name thyself: ";
	cin >> name;
	name = engine->toTitle(name);
	tmpRow = "Name: " + name + "\n";
	title.append(tmpRow);

	string raceArray[4] = { "Human", "Dwarf", "Elf", "Ork" };
    optionsLen = sizeof(raceArray)/sizeof(raceArray[0]);
    choiceIndex = engine->selector((title + "\nChoose your race: "), raceArray, optionsLen);
	race = raceArray[choiceIndex];
	tmpRow = "Race: " + race + "\n";
	title.append(tmpRow);

	string professionArray[6] = { "Fighter", "Barbarian", "Ranger", "Rogue", "Monk", "Warlock" };
	optionsLen = sizeof(professionArray) / sizeof(professionArray[0]);
	choiceIndex = engine->selector((title + "\nChoose your class: "), professionArray, optionsLen);
	profession = professionArray[choiceIndex];

	static map<string, int> i_defaultHealth = {
		{"Fighter", 10},
		{"Barbarian", 12},
		{"Ranger", 10},
		{"Rogue", 8},
		{"Monk", 8},
		{"Warlock", 8}
	};

	maxHp = i_defaultHealth[profession];
	currentHp = maxHp;

	title = "\t========== ALLOCATE POINTS ==========\n"; 

	string pointsArray[6] = { "8", "10", "12", "13", "14", "15" };
	optionsLen = sizeof(pointsArray) / sizeof(professionArray[0]);
	string prompt;

	for (map<string, int>::iterator iterator = i_skillPoints.begin(); iterator != i_skillPoints.end(); iterator++) { 
		prompt = "\nAllocate points to " + iterator->first;
		choiceIndex = engine->selector((title + prompt), pointsArray, optionsLen);
		int skillAllocation = stoi(pointsArray[choiceIndex]);

		i_skillPoints[iterator->first] = skillAllocation; 

		for (int j = choiceIndex; j < optionsLen - 1; j++) {
			pointsArray[j] = pointsArray[j + 1];
		}
		--optionsLen;
	}
	readCharacterSheet();
}

string Character::getName() {
	return name;
}

void Character::readCharacterSheet() {
	system("cls");
	cout << "\t========== CHARACTER SHEET ==========\n"; 
	cout << "Name: " << name << "\n";
	cout << "Race: " << race << "\n";
	cout << "Class: " << profession << "\n";
	cout << "Level: " << level << "\n";
	cout << "HP: " << currentHp << "/" << maxHp << "\n";

	for (map<string, int>::iterator iterator = i_skillPoints.begin(); iterator != i_skillPoints.end(); iterator++) {
		cout << iterator->first << ": " << iterator->second << "\n";
	}
}
