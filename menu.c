#include "hangman.h"

void main_menu(void) {
	char choice;

	system("cls");
	display_title();
	display_hangman(6);

	// display copyright info ;p
	gotoxy(0, 20);
	printf("  ---------------------------------------------------------------- \n");
	printf("                   All rights reserved. Manish & Brihat (070-BCT)");

	// Display main menu (options)
	gotoxy(0,6);
	printf("\n%s",
		"    MAIN MENU  |  Choose an option              \n\n"
		"     [1]   Play the game            \n"
		"     [2]   Read the rules           \n"
		"     [3]   Add words to dictionary  \n"
		"     [4]   View high scores         \n"
		"     [5]   About the program        \n"
		"     [Esc] Exit                     \n\n");

		// Manipulate the choice of user
		choice = getch();
		switch (choice) {
			case '1': start_game(); break;
			case '2': rules(); break;
			case '3': add_word(); break;
			case '4': high_scores(); break;
			case '5': about_program(); break;
			case ESC : exit(0); break;
			default:  main_menu(); break;
		}

}

void display_title(void) {
	gotoxy(0,0);
	printf("\n%s",
		"  ----------------------------------------------------------------\n"
		"                                                                \n"
		"    HANGMAN by MANISH & BRIHAT  ;p                             \n"
		"                                                                \n"
		"  ================================================================\n");
}

void rules(void) {
	system("cls");
	display_title();

	printf("\n%s",
		"    RULES OF THIS GAME :\n\n"
		"    1. You need to guess the words by entering \n"
		"       its letters with less than 7 misguesses. \n"
		"    2. If you fail to solve 5 words, it's \n"
		"       GAME OVER! >:D \n"
		"    3. Now try to solve as much words as you can! \n"
		"       \n"
		"       BEST OF LUCK! :p ");
	display_hangman(6);
	display_footer();
	while (getch() != ESC) { NULL; }
	main_menu();

}

void about_program(void) {
	system("cls");
	display_title();

	printf("\n%s",
		"    Hangman (R) is a small console based word   \n"
		"    game developed by Manish Munikar (070-BCT-520)  \n"
		"    and Brihat Ratna Bajracharya (070-BCT-513) \n"
		"    as a mini project in the first sememster at  \n"
		"    Pulchowk Campus, IOE. \n"
		"    \n"
		"    Find Manish @ facebook.com/manish.munikar \n"
		"    Find Brihat @ facebook.com/...            \n");

	display_hangman(6);
	display_footer();
	while (getch() != ESC) NULL;
	main_menu();
}

void add_word(void) {
	char new_word[26],		// a variable to store the new word entered by user
		 topic[26];			// a variable to store the new topic entered by user
	int	len_alpha=0;

	system("cls");
	display_title();
	display_footer();

	int x=4, y=7, i, j;
	gotoxy(0,y);
		printf("%s", "    Enter a word: (4 to 25 characters) \n    ");

	// This is a user-defined function to input string properly
	getstr(new_word, sizeof(new_word)+1, stdin);
	for (i=0; i<strlen(new_word); i++)
		if (isalpha(new_word[i])) len_alpha++;

	// if length of new_word is <4 or >20, then display error message and goto main menu
	if (len_alpha < 4) {
		printf("\n    SORRY, TOO FEW LETTERS");
		getch(); main_menu();
	}
	if (strlen(new_word) > 25) {
		gotoxy(x, y+2); printf("\n    SORRY, TOO LONG");
		getch(); main_menu();
	}

	// Similarlly for topic
		printf("\n    What is %s about? (4 to 25 characters) \n    ", s_toupper(new_word));
		getstr(topic, sizeof(topic)+1, stdin);

	if (strlen(topic) < 4 || strlen(topic) > 25) {
		printf("\n    INVALID ENTRY");
		getch(); main_menu();
	}

	// if everything is OK, then append the word & topic in the daatabase file
	FILE *file = fopen("words", "a");

	fprintf(file, "%s|%s\n", s_toupper(new_word), s_toupper(topic));

	fclose(file);

	printf("\n    WORD ADDED SUCCESSFULLY! :) ");
	getch(); main_menu();
}

void high_scores(void) {
	FILE *file = NULL;
	int x=5, y=7, i, j;

	system("cls");
	display_title();

	file = fopen("scorefile", "r");
	if (!file) {
		gotoxy(x+2,y);
		printf("No records available!");
		getch();
		main_menu();
	}

	int n = nelem(file, sizeof(RECORD));
	RECORD* data = malloc(n * sizeof(*data));

	fread(data, sizeof(*data), n, file);

	fclose(file);

	// Sorting the data according to descending score
	RECORD temp;
	for (i=0; i<n; i++) {
		for (j=i; j<n; j++)
			if (data[j].score > data[i].score)
				swap_record(&data[i], &data[j]);
	}

	// Printing the data
	gotoxy(x+2, y);
	printf("%4s %-20s %5s", "RANK", "NAME", "SCORE");
	gotoxy(x+2, y+1);
	printf("-------------------------------");

	for (i=0; i<n && i<10; i++) {
		gotoxy(x+2, y+2+i);
		printf("%3d. %-20s %5d", i+1, data[i].name, data[i].score);
	}

	free(data);

	display_hangman(6);
	display_footer();

	while (getch() != ESC) NULL;
	main_menu();
}

