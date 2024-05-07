#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_GUESSES_EASY 8
#define MAX_GUESSES_MEDIUM 6
#define MAX_GUESSES_HARD 4

#define MIN_NUMBER 1
#define MAX_NUMBER 100

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void printHangingMan(int numWrongGuesses) {
    if (numWrongGuesses == 0) {
        printf("\n");
    } else if (numWrongGuesses == 1) {
        printf("    O\n");
    } else if (numWrongGuesses == 2) {
        printf("    O\n");
        printf("    |\n");
    } else if (numWrongGuesses == 3) {
        printf("    O\n");
        printf("   /|\n");
    } else if (numWrongGuesses == 4) {
        printf("    O\n");
        printf("   /|\\\n");
    } else if (numWrongGuesses == 5) {
        printf("    O\n");
        printf("   /|\\\n");
        printf("   /\n");
    } else if (numWrongGuesses == 6) {
        printf("    O\n");
        printf("   /|\\\n");
        printf("   / \\\n");
    }
}

void displayColorfulText(char *text, char *color) {
    printf("%s%s\033[0m", color, text);
}

void displayIntroduction(int difficulty) {
    printf("Welcome to the Guess the Number game!\n");

    switch (difficulty) {
        case 1:
            printf("You've selected Easy difficulty. You have %d guesses.\n", MAX_GUESSES_EASY);
            break;
        case 2:
            printf("You've selected Medium difficulty. You have %d guesses.\n", MAX_GUESSES_MEDIUM);
            break;
        case 3:
            printf("You've selected Hard difficulty. You have %d guesses.\n", MAX_GUESSES_HARD);
            break;
        default:
            printf("Invalid difficulty level. Defaulting to Medium.\n");
    }

    printf("I have chosen a number between %d and %d.\n", MIN_NUMBER, MAX_NUMBER);
}

void displayResult(int guess, int numberToGuess, int numGuesses) {
    if (guess == numberToGuess) {
        displayColorfulText("Congratulations! You guessed the number ", "\033[1;32m");
        printf("%d", numberToGuess);
        displayColorfulText(" in ", "\033[1;32m");
        printf("%d", numGuesses);
        displayColorfulText(" guesses.\n", "\033[1;32m");
    } else {
        printf("Sorry, you didn't guess the number. It was %d.\n", numberToGuess);
        displayColorfulText("Better luck next time!\n", "\033[1;31m");
        printHangingMan(6);
    }
}

void playGame(int difficulty) {
    int numberToGuess, guess, numGuesses = 0;
    int maxGuesses;

    switch (difficulty) {
        case 1:
            maxGuesses = MAX_GUESSES_EASY;
            break;
        case 2:
            maxGuesses = MAX_GUESSES_MEDIUM;
            break;
        case 3:
            maxGuesses = MAX_GUESSES_HARD;
            break;
        default:
            maxGuesses = MAX_GUESSES_MEDIUM;
            break;
    }

    srand(time(NULL));
    numberToGuess = generateRandomNumber(MIN_NUMBER, MAX_NUMBER);

    displayIntroduction(difficulty);

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else if (guess > numberToGuess) {
            printf("Too high! Try again.\n");
        }

        numGuesses++;
    } while (guess != numberToGuess && numGuesses < maxGuesses);

    displayResult(guess, numberToGuess, numGuesses);
}

int main() {
    int choice;

    printf("Welcome to Guess the Number!\n");
    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    playGame(choice);

    return 0;
}

