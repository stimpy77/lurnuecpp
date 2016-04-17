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

enum class EGuessValidity
{
	OK,
	NotIsogram,
	BadChars,
	WrongLength,
	Empty
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
	EGuessValidity Validate(FString guess);
	void SubmitGuess(FString guess);
	FString PromptNewGuess();
	FBullCowCount MatchGuess();
	bool isUserStillInGame() const;
	void PrintGuessResult();
	void PrintGameOver();
	bool PromptPlayAgain();
	void PrintAllPossibleWords();

private:
	int32 maxTries;
	int32 triesInputted;
	bool processedCurrentGuess = false;
	bool wantExit = false;
	FBullCowCount currentBullCowCount;
	FString currentGuess = "";
	FString currentWord = "undefined";
	FString getNewHiddenWord();
	bool IsIsogram(FString word);
	const int32 wordCount = 3;
	const FString words[3] = { "horse", "cow", "zebra" };
	int32 IncrementTryCount(int32);
};