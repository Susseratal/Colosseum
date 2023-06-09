#define _CRT_SECURE_NO_WARNINGS
#include "Engine.h"

#define KEY_UP 72       // down arrow 
#define KEY_DOWN 80     // up arrow
#define KEY_ENTER '\r'  // enter key

using namespace std;

Engine::Engine() {
	// seed the random number generator
	srand(time(NULL));
}

string Engine::toTitle(string s) {
	const int length = s.length();
	char* charArray = new char[length + 1];
    strcpy(charArray, s.c_str());
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            charArray[i] = toupper(charArray[i]);
        }
        else {
            charArray[i] = tolower(charArray[i]);
        }
    }
    string returnStr(charArray);
    return returnStr;
}

string Engine::toLower(string s) {
	const int length = s.length();
	char* chararray = new char[length + 1];
	strcpy(chararray, s.c_str());
	for (int i = 0; i < length; i++) {
		chararray[i] = tolower(chararray[i]);
	}
	string returnstr(chararray);
	return returnstr;
}

string Engine::toUpper(string s) {
	const int length = s.length();
	char* chararray = new char[length + 1];
	strcpy(chararray, s.c_str());
	for (int i = 0; i < length; i++) {
		chararray[i] = toupper(chararray[i]);
	}
	string returnstr(chararray);
	return returnstr;
}

Engine::status Engine::rollDie(int threshold) {
    status success;
    int total = 0;
    int roll = 0;

    for (int i = 0; i < 3; i++) {
        roll = rand() % 6 + 1;
        total += roll;
    };
    
    cout << total << "\n";

    if (total == 3 || total == 4) {
        success = status::criticalFailure;
    }
    else if (total == 17 || total == 18) {
        success = status::criticalSuccess;
    }
    else if (total <= threshold) {
        success = status::success;
    }
    else { // should obnly trigger if total is greater than threshold but isn't 17 or 18
        success = status::failure;
    }

    return success;
}

int Engine::selector(string prompt, string options[], int optionsLen) {
    int selected = 0;
    bool selecting = true;
    bool updated = true;
    char c;

    do {
        if (updated) {
            system("cls");
            cout << prompt << "\n";
            for (int i = 0; i < optionsLen; i++) {
                if (selected == i) {
                    cout << options[i] << " <<<\n";
                }
                else {
                    cout << options[i] << "\n";
                }
            }
            updated = false;
        }

        switch ((c = _getch())) {
        case KEY_UP:
            if (selected > 0) { // don't decrement if it's at the first option
                selected--;
                updated = true;
            }
            break;

        case KEY_DOWN:
            if (selected < optionsLen - 1) { // don't increment if we're at the last option
                selected++;
                updated = true;
            }
            break;
            
        case KEY_ENTER:
            selecting = false;
            break;

        default:
            break;
        }
    } while (selecting);

    return(selected);
}

void Engine::saveGame() {
    // Do this later
}

void Engine::loadGame() {
    cout << "Load\n";
}

int Engine::quitGame() {
    cout << "Press return to quit...";
    _getch();
    system("cls");
    return 0;
}

