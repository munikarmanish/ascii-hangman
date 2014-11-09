#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define ESC	27
#define ENTER	13

/* This is the function to make gotoxy() function work in CodeBlocks */
void gotoxy(int x, int y);

// data structure to store words
typedef struct wordstruct {
	char word[26];
	char topic[26];
} wordstruct;

// data structure to store names & scores
typedef struct score_record {
	char name[31];
	int  score;
} RECORD;

// This function below is a advancement of fgets() function.
// It inputs the string upto '\n' and converts that last '\n' into '\0'.
char* getstr(char* name, int sizeof_arr, FILE* file);

// A function to display error message
void error(char* msg);

// a function to count the number of lines (no of '\n') in a file
int line_count(FILE* file);

// a function to count the number of different letters in a word
int alpha_count(char* word, int length);

// a function that returns a random integer from 0 to n-1
int random(int n);

// A function that converts all the letters of a string into uppercase
char* s_toupper(char* string);

// A function to swap two 'RECORD' data structures
void swap_record(RECORD* r1, RECORD* r2);

void main_menu(void);
void display_title(void);
void rules(void);
void about_program(void);
void add_word(void);
void high_scores(void);

// A function that displays the loading animation
void display_loading(void);

void start_game(void);
void display_footer(void);
void save_record(char *name, int score);

// A function to display a hangman at side of screen according to number of misguesses
void display_hangman(int misguess);

int nelem(FILE* file, int esize);
