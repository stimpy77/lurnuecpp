#include "FBullCowGame.h"

int32 FBullCowGame::getUserTries() const { return triesInputted; }
bool FBullCowGame::isWon() const { return won; }
bool FBullCowGame::getUserWantsToExit() const { return wantExit; }
int32 FBullCowGame::getMaxTries() const { return maxTries; }

FBullCowGame::FBullCowGame()
{
	//Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;

	maxTries = MAX_TRIES;
	triesInputted = 0;
	currentGuess = "";
	won = false;
	wantExit = false;
	processedCurrentGuess = false;
}

void FBullCowGame::PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a stupid word guessing game.\n";
}

void FBullCowGame::PrintQuestion()
{
	std::cout << "Can you guess the " << currentWord.length();
	std::cout << " letter isogram I'm thinking of?\n";
}

FString FBullCowGame::PromptNewGuess()
{
	std::cout << "Try " << (triesInputted + 1) << ". ";
	std::cout << "You have " << (maxTries - triesInputted) << " tries including this one left.\n";
	FString guess = "";
	while (!CheckValidity(guess))
	{
		std::cout << "Enter your guess: ";
		std::getline(std::cin, guess);
		if (guess == "exit")
		{
			wantExit = true;
			return "";
		}
	}

	std::cout << "You guessed " + guess + ".\n";
	NewGuess(guess);

	return guess;
}

void FBullCowGame::NewGuess(FString guess)
{
	currentGuess = guess;
	triesInputted++;
}

FBullCowCount FBullCowGame::MatchGuess()
{
	processedCurrentGuess = true;
	bool isMatch = won = (currentGuess == currentWord);
	FBullCowCount result;
	for (int32 c = 0; c < currentGuess.length(); c++)
	{
		if (c < currentWord.length())
		{
			if (currentGuess[c] == currentWord[c])
				result.Bulls++;
			else if (currentGuess[c] != currentWord[c])
			{
				for (int32 cc = 0; cc < currentWord.length(); cc++)
				{
					if (currentWord[cc] == currentGuess[c])
						result.Cows++;
				}
			}
		}
	}
	result.IsMatch = isMatch;
	currentBullCowCount = result;
	return result;
}

bool FBullCowGame::isUserStillInGame() const
{
	return !won && getUserTries() < getMaxTries();
}

void FBullCowGame::PrintGuessResult()
{
	if ((processedCurrentGuess && won) || MatchGuess().IsMatch) {
		std::cout << "YOU GUESSED RIGHT!! *fireworks* *confetti*";
	}
	else
	{
		std::cout << "You guess wrong. *shame*";
		std::cout << std::endl;
		std::cout << "Bulls: " << currentBullCowCount.Bulls << "\n";
		std::cout << "Cows: " << currentBullCowCount.Cows << "\n";
	}
	std::cout << std::endl;
}
bool FBullCowGame::CheckValidity(FString str)
{
	return str != "";
}

void FBullCowGame::PrintGameOver()
{
	std::cout << "\nGame over.\n\n";
}

bool FBullCowGame::PromptPlayAgain()
{
	FString tryAgainAnswer = "";
	while (tryAgainAnswer.length() < 1 || (tryAgainAnswer[0] != 'y' && tryAgainAnswer[0] != 'Y' && tryAgainAnswer[0] != 'n' && tryAgainAnswer[0] != 'N'))
	{
		std::cout << "Would you like to try a new game?\n";
		std::getline(std::cin, tryAgainAnswer);
	}
	return tryAgainAnswer[0] == 'y' || tryAgainAnswer[0] == 'Y';
}
