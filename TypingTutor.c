#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define MAX_SENTENCES 10
#define MAX_SENTENCE_LENGTH 100
#define MAX_NAME_LENGTH 50
#define HIGH_SCORE_FILE "high_scores.txt"

struct HighScore {
    char name[MAX_NAME_LENGTH];
    int score;
};

void clearScreen() {
    system("cls");
}

void displayHighScores() {
    FILE* file = fopen(HIGH_SCORE_FILE, "r");
    if (file == NULL) {
        printf("No high scores available.\n");
        return;
    }

    printf("High Scores:\n");
    struct HighScore highScores[MAX_SENTENCES];
    int numHighScores = 0;

    while (fscanf(file, "%s %d\n", highScores[numHighScores].name, &highScores[numHighScores].score) != EOF) {
        printf("%s - %d\n", highScores[numHighScores].name, highScores[numHighScores].score);
        numHighScores++;
    }

    fclose(file);
}

void saveHighScore(char* playerName, int score) {
    FILE* file = fopen(HIGH_SCORE_FILE, "a");
    if (file == NULL) {
        printf("Unable to save high score.\n");
        return;
    }

    fprintf(file, "%s %d\n", playerName, score);
    fclose(file);
}

int main() {
    char sentences[MAX_SENTENCES][MAX_SENTENCE_LENGTH] = {
        "The quick brown fox jumps over the lazy dog.",
        "Programming is fun and challenging.",
        "Hello, world! This is a typing tutor.",
        "Practice makes perfect.",
        "Coding is a valuable skill to learn.",
        "Typing is an essential skill for computer users.",
        "Learning to type can improve your productivity.",
        "Accuracy is more important than speed in typing.",
        "Don't look at the keyboard while typing.",
        "Challenge yourself and type faster each day."
    };

    int numSentences = sizeof(sentences) / sizeof(sentences[0]);
    srand(time(NULL));

    printf("Welcome to the Typing Tutor!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Start Typing Test\n");
        printf("2. Display High Scores\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        fflush(stdin);

        clearScreen();

        switch (choice) {
            case 1: {
                printf("Enter your name: ");
                char playerName[MAX_NAME_LENGTH];
                fgets(playerName, sizeof(playerName), stdin);
                playerName[strcspn(playerName, "\n")] = '\0';

                int score = 0;
                int totalAttempts = 0;
                int numSentencesToType = 5;  // Adjust the number of sentences to type
				int i,j;
                for (i = 0; i < numSentencesToType; i++) {
                    int sentenceIndex = rand() % numSentences;
                    printf("Type the following sentence:\n\n%s\n\n", sentences[sentenceIndex]);

                    time_t startTime = time(NULL);
                    char input[MAX_SENTENCE_LENGTH];
                    fgets(input, sizeof(input), stdin);
                    time_t endTime = time(NULL);

                    double elapsedTime = difftime(endTime, startTime);
                    int sentenceLength = strlen(sentences[sentenceIndex]);
                    int errors = 0;

                    for (j = 0; j < sentenceLength; j++) {
                        if (input[j] != sentences[sentenceIndex][j]) {
                            errors++;
                        }
                    }

                    totalAttempts++;
                    printf("\nTime taken: %.2lf seconds\n", elapsedTime);
                    printf("Errors: %d\n", errors);

                    if (errors == 0) {
                        printf("Perfect!\n");
                        score++;
                    } else {
                        printf("Try again!\n");
                    }

                    printf("Press Enter to continue...\n");
                    fflush(stdin);
                    getchar();
                    clearScreen();
                }

                printf("Typing test completed!\n");
                printf("Your score: %d/%d\n", score, numSentencesToType);
                printf("Accuracy: %.2lf%%\n", ((double)score / numSentencesToType) * 100);

                saveHighScore(playerName, score);

                break;
            }
            case 2:
                displayHighScores();
                break;
            case 3:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

