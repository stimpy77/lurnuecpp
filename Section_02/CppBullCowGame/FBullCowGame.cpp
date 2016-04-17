#include <algorithm>
#include <string>
#include <cstdlib> 
#include <ctime>
#include "FBullCowGame.h"

int32 FBullCowGame::getUserTries() const { return triesInputted; }
bool FBullCowGame::isWon() const { return currentBullCowCount.IsMatch; }
bool FBullCowGame::getUserWantsToExit() const { return wantExit; }

FBullCowGame::FBullCowGame()
{
	//Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;

	triesInputted = 0;
	currentGuess = "";
	currentBullCowCount = FBullCowCount();
	wantExit = false;
	processedCurrentGuess = false;
	currentWord = getNewHiddenWord();
}

FString FBullCowGame::getNewHiddenWord()
{
	srand((unsigned)time(0));
	int32 rnd = rand() % wordCount;
	return words[rnd];
}

int32 FBullCowGame::getMaxTries() { 
	return wordLengthToMaxTries[currentWord.length()];
}

EGuessValidity FBullCowGame::Validate(FString word)
{
	if (word == "") return EGuessValidity::Empty;
	if (word.length() != currentWord.length()) return EGuessValidity::WrongLength;
	const FString validChars = "abcdefghijklmnopqrstuvwxyz";
	for (int32 c = 0; c < word.length(); c++)
	{
		char ch = word[c];
		if (validChars.find(ch) == std::string::npos) return EGuessValidity::BadChars;
	}
	if (!IsIsogram(word))
		return EGuessValidity::NotIsogram;
	return EGuessValidity::OK;
}

bool FBullCowGame::IsIsogram(FString word)
{
	int32 aToZ[(int32)'z'+1]{};
	for (char c : word)
	{
		if (aToZ[(int32)c]++ > 0) return false;
	}
	return true;
}

int32 FBullCowGame::IncrementTryCount(int32 incr)
{
	triesInputted += incr;
	std::cout << "\nTry " << (triesInputted + 1) << " [" << (triesInputted + 1) << "/" << getMaxTries() << "]\n";
	return triesInputted;
}

void FBullCowGame::PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a stupid word guessing game.\n";
}

void FBullCowGame::PrintQuestion()
{
	std::cout << "Can you guess the " << currentWord.length() << " letter isogram I'm thinking of?\n";
}

FString FBullCowGame::PromptNewGuess()
{
	processedCurrentGuess = false;
	IncrementTryCount(0);
	FString guess = "";
	EGuessValidity validation;
	while ((validation = Validate(guess)) != EGuessValidity::OK && triesInputted < getMaxTries()-1)
	{
		switch (validation)
		{
		case EGuessValidity::BadChars:
			std::cout << "Invalid input. Please enter ONE WORD (a-z lowercase only).\n";
			break;
		case EGuessValidity::NotIsogram:
			std::cout << "WRONG!!! That is not an isogram! An isogram must not have repeating letters.\n";
			std::cout << "You've been penalized a turn.\n";
			IncrementTryCount(1);
			break;
		case EGuessValidity::WrongLength:
			std::cout << "Wrong length! My word is " << currentWord.length() << " long, yours was " << guess.length() << " long.\n";
			std::cout << "You've been penalized a turn.\n";
			IncrementTryCount(1);
			break;
		}

		std::cout << "Guess my " << currentWord.length() << "-letter isogram: ";
		std::getline(std::cin, guess);
		//std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
		if (guess == "exit")
		{
			wantExit = true;
			return "";
		}
	}
	std::cout << "You guessed " + guess + ".\n\n";
	return guess;
}

void FBullCowGame::SubmitGuess(FString guess)
{
	currentGuess = guess;
	triesInputted++;
	FBullCowGame::MatchGuess();
}

FBullCowCount FBullCowGame::MatchGuess()
{
	if (processedCurrentGuess) return currentBullCowCount;
	processedCurrentGuess = true;
	FBullCowCount result;
	for (int32 c = 0; c < currentGuess.length(); c++)
	{
		if (c < currentWord.length())
		{
			if (c < currentWord.length() && currentGuess[c] == currentWord[c])
				result.Bulls++;
			else
			{
				for (int32 cc = 0; cc < currentWord.length(); cc++)
				{
					if (currentWord[cc] == currentGuess[c])
						result.Cows++;
				}
			}
		}
	}
	result.IsMatch = currentGuess == currentWord;
	currentBullCowCount = result;
	return result;
}

bool FBullCowGame::isUserStillInGame()
{
	return !currentBullCowCount.IsMatch && getUserTries() < getMaxTries();
}

void FBullCowGame::PrintGuessResult()
{
	if ((processedCurrentGuess && currentBullCowCount.IsMatch) || MatchGuess().IsMatch) {
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

void FBullCowGame::PrintGameSummary()
{
	std::cout << "GAME OVER\n";
	if (currentBullCowCount.IsMatch) {
		std::cout << "You are a big fat winner.\n";

		std::cout << "                                       /;    ;\\\n";
		std::cout << "                                   __  \\\\____//\n";
		std::cout << "                                  /{_\\_/   `'\\____\n";
		std::cout << "                                  \\___   (o)  (o  }\n";
		std::cout << "       _____________________________/          :--'\n";
		std::cout << "   ,-,'`@@@@@@@@       @@@@@@         \\_    `__\n";
		std::cout << "  ;:(  @@@@@@@@@        @@@             \\___(o'o)\n";
		std::cout << "  :: )  @@@@          @@@@@@        ,'@@(  `===='\n";
		std::cout << "  :: : @@@@@:          @@@@         `@@@:\n";
		std::cout << "  :: \\  @@@@@:       @@@@@@@)    (  '@@@'\n";
		std::cout << "  ;; /\\      /`,    @@@@@@@@@\\   :@@@@@)                \n";
		std::cout << "  ::/  )    {_----------------:  :~`,~~;\n";
		std::cout << " ;;'`; :   )                  :  / `; ;\n";
		std::cout << ";;;; : :   ;                  :  ;  ; :\n";
		std::cout << "`'`' / :  :                   :  :  : :\n";
		std::cout << "    )_ \\__;      \";\"          :_ ;  \\_\\       `,','\n";
		std::cout << "    :__\\  \\    * `,'*         \\  \\  :  \\   *  8`;'*  * \n";
		std::cout << "        `^'     \\ :/           `^'  `-^-'   \\v/ :  \\/   \n";
	}
	else
	{
		std::cout << "You are a big fat LOSER!!\n";
		std::cout << "      db         db             \n";
		std::cout << "    d88           88             \n";
		std::cout << "   888            888             \n";
		std::cout << "  d88             888b         \n";
		std::cout << "  888             d88P         \n";
		std::cout << "  Y888b  /``````\\8888             \n";
		std::cout << ",----Y888        Y88P`````\\     \n";
		std::cout << "|        ,'`\\_/``\\ |,,    |     \n";
		std::cout << " \\,,,,-| | o | o / |  ```'     \n";
		std::cout << "       |  """ """  |             \n";
		std::cout << "      /             \\             \n";
		std::cout << "     |               \\         \n";
		std::cout << "     |  ,,,,----'''```|         \n";
		std::cout << "     |``   @    @     |         \n";
		std::cout << "      \\,,    ___    ,,/         \n";
		std::cout << "         \\__|   |__/             \n";
		std::cout << "            | | |                 \n";
		std::cout << "            \\_|_/                 \n";
		std::cout << "                                 \n";
		std::cout << "     _                         \n";
		std::cout << " \\\\ |_|  _   _  _  _  _  | //     \n";
		std::cout << "    |   (_\\ |  |  |  |_| o     \n";
		std::cout << "                     |         \n";
	}
}

bool FBullCowGame::PromptPlayAgain()
{
	FString tryAgainAnswer = "";
	while (tryAgainAnswer.length() < 1 || (tryAgainAnswer[0] != 'y' && tryAgainAnswer[0] != 'Y' && tryAgainAnswer[0] != 'n' && tryAgainAnswer[0] != 'N'))
	{
		std::cout << "Would you like to try a new game?\n (y/n) ";
		std::getline(std::cin, tryAgainAnswer);
	}
	return tryAgainAnswer[0] == 'y' || tryAgainAnswer[0] == 'Y';
}

void FBullCowGame::PrintAllPossibleWords()
{
	std::cout << "Here are all possible words:\n";
	for (int32 w = 0; w < wordCount; w++)
	{
		if (w > 0) std::cout << ", ";
		if (w % 5 == 0) std::cout << std::endl;
		std::cout << words[w];
	}
	std::cout << "\n\n";
}


