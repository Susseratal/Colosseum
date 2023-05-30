#pragma once
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <conio.h>

class Engine {
public:
	Engine();

	std::string toTitle(std::string s);
	std::string toLower(std::string s);
	std::string toUpper(std::string s);

	int rollDie(int maxRoll);

	int selector(std::string prompt, std::string options[], int optionsLen);
};


