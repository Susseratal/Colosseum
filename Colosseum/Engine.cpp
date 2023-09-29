#include "Engine.h"
#include <iostream>
#include <time.h>

Engine::Engine() {
	srand(time(NULL)); 
}

Engine::RollData Engine::skillCheck(int diToRoll, int modifier, int threshold) {
	int total = 0;

	for (int i = 0; i < diToRoll; i++) {
		total += rand() % 6 + 1;
	}

	Engine::RollData resultData{R_Fail, 0};

	if (total == diToRoll) { 
		// if all di rolled 1, it's a CritFail
		resultData.result = R_CritFail;
		resultData.margin = threshold;
	}
	else if (total == (6 * diToRoll)){
		// if all di rolled 6, it's a CritSuccess
		resultData.result = R_CritSuccess;
		resultData.margin = threshold;
	}
	else if ((total + modifier) <= threshold) {
		// if the result isn't a crit, add modifiers
		resultData.result = R_Success;
		resultData.margin = (threshold - (total + modifier));
	}
	else if ((total + modifier) > threshold){
		// if the result isn't a crit and is greater than threshold
		resultData.result = R_Fail;
		resultData.margin = ((total + modifier) - threshold);
	}

	return resultData;
}

bool Engine::isEven(int n) {
	/*
	if the final bit of n is 1, that means it's odd, otherwise it's even 
	Bitwise AND only returns 1 if BOTH bits are 1
		1011 - 11
	  & 0001 - 1
	  ------
		0001 - 1

		1110 - 14
	  & 0001 - 1
	  ------
		0000 - 0
	*/
	return (!(n & 1));
}
