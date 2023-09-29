#pragma once
class Engine
{
public:
	enum Result {
		R_CritFail,
		R_CritSuccess,
		R_Success,
		R_Fail
	};

	struct RollData {
		Result result;
		int margin;
	};

	Engine(); 
	// ~Engine();

	/**
	* Perform a skill check on a player action
	* 
	* @param diToRoll -- The number of 6 sided dice to roll
	* @param modifier -- Any additions or subtractions to be added. i.e. 4d+2 - modifier = +2
	* @param threshold -- The success/failure threshold. Usually the skill being checked of the character rolling
	* 
	* @return Result -- The success or failure type
	**/
	RollData skillCheck(int diToRoll, int modifier, int threshold);

	bool isEven(int n);
};

