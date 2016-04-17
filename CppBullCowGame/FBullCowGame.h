#pragma once

#include <iostream>
#include <string>

using FString = std::string;
using FText = std::string;
using int32 = unsigned int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
	bool IsMatch = false;
};

class FBullCowGame {

public:
	FBullCowGame();
	void Reset();
	void PrintIntro();
	int32 getMaxTries() const;
	int32 getUserTries() const;
	void PrintQuestion();
	bool isWon() const;
	bool getUserWantsToExit() const;
	bool CheckValidity(FString);
	void NewGuess(FString guess);
	FString PromptNewGuess();
	FBullCowCount MatchGuess();
	bool isUserStillInGame() const;
	void PrintGuessResult();
	void PrintGameOver();
	bool PromptPlayAgain();

private:
	int32 maxTries;
	int32 triesInputted;
	bool won;
	bool processedCurrentGuess = false;
	bool wantExit = false;
	FBullCowCount currentBullCowCount;
	FString currentGuess = "";
	FString currentWord = "horse";
};