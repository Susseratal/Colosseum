#pragma once
#include <iostream>
#include <ios>
#include <string>
#include <random>
#include <fstream>
#include <time.h>
#include <conio.h>

class Engine {
public:
	Engine();

	enum class status { success, failure, criticalSuccess, criticalFailure };

	std::string toTitle(std::string s);
	std::string toLower(std::string s);
	std::string toUpper(std::string s);

	int selector(std::string prompt, std::string options[], int optionsLen);

	status rollDie(int threshold);

	void saveGame();
	void loadGame();

	int quitGame();
};


