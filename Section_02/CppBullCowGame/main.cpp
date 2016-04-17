
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
		bcGame.PrintAllPossibleWords();
		while (!bcGame.getUserWantsToExit() && bcGame.isUserStillInGame())
		{
			FString guess = bcGame.PromptNewGuess();
			if (bcGame.getUserWantsToExit()) break;

			bcGame.SubmitGuess(guess);
			bcGame.PrintGuessResult();
			if (!bcGame.isUserStillInGame())
				bcGame.PrintGameSummary();
		}
	} while (!bcGame.getUserWantsToExit() && bcGame.PromptPlayAgain());
}
