#include "Engine.h"
#include <iostream>
#include <time.h>

Engine::Engine() {
	srand(time(NULL)); 
}

Engine::RollData Engine::skillCheck(int diToRoll, int modifier, int threshold) {
	std::cout << "Die to roll = " << diToRoll << "\n";
	std::cout << "Modifier = " << modifier << "\n";
	std::cout << "Threshold = " << threshold << "\n";
	int total = 0;
	std::cout << "Total = " << total << "\n";

	for (int i = 0; i < diToRoll; i++) {
		total += rand() % 6 + 1;
		std::cout << "Iteration: " << i << " Total = " << total << "\n";
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
		std::cout << "Result after modifiers = " << total + modifier << "\n";
		resultData.result = R_Success;
		resultData.margin = (threshold - (total + modifier));
	}
	else if ((total + modifier) > threshold){
		// if the result isn't a crit and is greater than threshold
		std::cout << "Result after modifiers = " << total + modifier << "\n";
		resultData.result = R_Fail;
		resultData.margin = ((total + modifier) - threshold);
	}

	return resultData;
}
