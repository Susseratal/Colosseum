#include <iostream>
#include "Character.h"
#include "Engine.h"

using namespace std;

int main()
{
    system("cls");
    Engine* engine = new Engine();

    Engine::status result = engine->rollDie(13);
    // Character* player = new Character();

    switch (result) {
    case Engine::status::success:
        cout << "success\n";
        break;

    case Engine::status::failure:
        cout << "failure\n";
        break;

    case Engine::status::criticalSuccess:
        cout << "critical success\n";
        break;

    case Engine::status::criticalFailure:
        cout << "critical failure\n";
        break;

    default:
        cout << "Invalid output\n";
        break;
    }


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
