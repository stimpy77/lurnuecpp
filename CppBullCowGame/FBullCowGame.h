#pragma once

#include <iostream>
#include <string>
#include <map>
#define TMap std::map

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
	int32 getMaxTries();
	int32 getUserTries() const;
	void PrintQuestion();
	bool isWon() const;
	bool getUserWantsToExit() const;
	EGuessValidity Validate(FString guess);
	void SubmitGuess(FString guess);
	FString PromptNewGuess();
	FBullCowCount MatchGuess();
	bool isUserStillInGame();
	void PrintGuessResult();
	void PrintGameSummary();
	bool PromptPlayAgain();
	void PrintAllPossibleWords();

private:
	int32 triesInputted;
	bool processedCurrentGuess = false;
	bool wantExit = false;
	FBullCowCount currentBullCowCount;
	FString currentGuess = "";
	FString currentWord = "undefined";
	FString getNewHiddenWord();
	bool IsIsogram(FString word);
	const int32 wordCount = 4;
	const FString words[4] = { "horse", "cow", "zebra", "choice" };
	int32 IncrementTryCount(int32);
	TMap<int32, int32> wordLengthToMaxTries{ { 3,5 },{ 4,5 },{ 5,6 },{ 6,7 } };
};