#include <iostream>
#include "Character.h"
#include "Engine.h"

using namespace std;

int main()
{
    system("cls");
    Engine* engine = new Engine();
    Character* player = new Character();

    int exitStatus = engine->quitGame();
    return exitStatus;
}

/*
 game loop
 player creates a character using a D&D character sheet
 The player fights in the colosseum against standard D&D enemies
 The player gains XP and gold
 When the player levels up, they can choose to increase skills for better luck during rolls
* MVP:
    - [x] Create a character
    - [ ] Character gets serialised and saved
    - [ ] Fight against enemies in the colosseum
        - [ ] 5 enemies available
    - [ ] level up skills

* PUSH:
    - buy new weapons and armour
    - complex inventory
    - multiple weapon types for different classes
*/
