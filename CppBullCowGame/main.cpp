/*
This is the console shell executable program which makes use of the FBullCowGame class.
This acts as the view in an MVC pattern, and is responsiblef or all user interaction.
For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

FBullCowGame bcGame;
void playGame();

int main() 
{
	playGame();
	return 0;
}

void playGame()
{
	bcGame.PrintIntro();
	do
	{
		bcGame.Reset();
		bcGame.PrintQuestion();
		while (!bcGame.getUserWantsToExit() && bcGame.isUserStillInGame())
		{
			bcGame.PromptNewGuess();
			if (bcGame.getUserWantsToExit()) break;
			bcGame.PrintGuessResult();
			if (!bcGame.isUserStillInGame())
				bcGame.PrintGameOver();
		}
	} while (!bcGame.getUserWantsToExit() && bcGame.PromptPlayAgain());
}