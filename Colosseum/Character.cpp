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

	string pointsArray[6] = { "8", "10", "12", "13", "14", "15" };

	do {
		optionsLen = sizeof(pointsArray) / sizeof(professionArray[0]);
		choiceIndex = engine->selector((title + "\nAllocate points to {SKILL}: "), pointsArray, optionsLen);

		for (int i = choiceIndex; i < optionsLen; i++) {
			pointsArray[i] = pointsArray[i + 1];
		}
	} while (optionsLen > 0);


	readCharacterSheet();
}

string Character::getName() {
	return name;
}

void Character::readCharacterSheet() {
	system("cls");
	cout << "\t========== CHARACTER SHEET ==========\n"; 
	cout << "Name: " << name;
	cout << "\nRace: " << race;
	cout << "\nClass: " << profession;
	cout << "\nLevel: " << level;
	cout << "\nHP: " << currentHp << "/" << maxHp;
	cout << "\nStrength: " << strength;
	cout << "\nDexterity: " << dexterity;
	cout << "\nConstitution: " << constitution;
	cout << "\nIntelligence: " << intelligence;
	cout << "\nWisdom: " << wisdom;
	cout << "\nCharisma: " << charisma;
	cout << "\n";
}
