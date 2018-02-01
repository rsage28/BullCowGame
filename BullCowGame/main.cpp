#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGuess(FText);
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());

	return 0;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	return;
}

void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";

	return;
}

FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Type a guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter world.\n"; break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess is not an isogram.\n"; break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Word is not in all lowercase.\n"; break;
		default:
			break;
		}
		std::cout << "\n";
	} while (Status != EGuessStatus::Ok);

	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You won!\n";
	}
	else {
		std::cout << "You lost. FeelsBadMan.\n";
	}
}
