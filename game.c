#include "hangman.h"

void start_game(void) {

	int x = 2, y = 7; // starting position of text (after title)
	int i, j;
	// declaration of necessary variables
	int	asked = 0,			// number of words asked
		lives = 5,			// number of lives left
		answerd = 0,		// number of words anwered correctly
		length = 0,			// length of current word
		punctuation=0,		// number of non alphabets in the current word
		mistake_limit = 7,	// number of mischoice for losing a word
		new_word = 1,		// flag to ask a new word
		n_lines = 0,		// number of words (or lines) in the database file
		letter_count=0,		// number of letters guessed in a word
		misguess=0,			// number of misguesses in a word
		correct_guess = 0,	// number of letters guessed correctly
		guessed = 0,		// a flag to see whether an alphabet of the word is guessed
		already_guessed=0	// a flag to see if the entered letter is already guessed
		;
	char 	word[21],				// current word
			topic[16],				// current topic
			line_string[37],		// a variable to store the whole string of a single line in file (eg. "WORD|TOPIC")
			c,						// currently chosen letter in a word
			guessed_letters[26]={0},// array of letters guessed by users
			name[31];				// name of player

	// read all the words (or lines) of the file into array of data structure
	FILE *fp = fopen("words", "r");
	n_lines = line_count(fp);

	wordstruct* data = malloc(n_lines * sizeof(*data));
	//char words_asked[n_lines][21];		// an array of words already asked

	char** words_asked = malloc(n_lines * sizeof(*words_asked));
	for (i=0; i<n_lines; ++i)
		words_asked[i] = malloc(21 * sizeof(*words_asked[i]));

	rewind(fp);
	for (i=0; i<n_lines; i++) {
		getstr(line_string, sizeof(line_string), fp);

		// if the line contains only '\n' (eg. the last line), then directly goto next line
		if (strlen(line_string) < 3) continue;

		// store the word and topic of current line into data structure
		strcpy(data[i].word, strtok(s_toupper(line_string), "|"));
		strcpy(data[i].topic, strtok(NULL, "|"));
	}

	fclose(fp);


	gotoxy(0, y); new_word = 1;
	while (lives) {
		for (i=0; i<99999999; i++); // wait for a second to get new word
		int n = random(n_lines);
		strcpy(word, data[n].word);
		strcpy(topic, data[n].topic);

		// check to see if the word is already asked earlier
		int already_asked=0;
		for (i=0; i<=asked; i++) {
			if (strcmp(word, words_asked[i])==0) {
					already_asked = 1;
			}
		}

		// if the word is not asked before, then add it to words_asked[] and increase asked++;
		if (already_asked) continue;

		strcpy(words_asked[asked], word); asked++;

		length = strlen(word);

		system("cls");
		display_title();

		x=2; y=7;
		guessed_letters[26] = "";
		letter_count = 0;

		gotoxy(x+2, y+0);
			printf("WORD #%d", asked);
		gotoxy(35, 7); printf("Lives: %d", lives);
		gotoxy(x+2, y+2);
			printf("HINT: The following word is about %s", topic);
		gotoxy(x+7, y+4);
		for (i=0; i<length; i++) {
			if (isalpha(word[i])) { printf("_ "); }
			else { printf("%c ", word[i]); punctuation++; }
		}
		display_hangman(0);
		gotoxy(4,14); printf("Guessed letters:");
		display_footer();
		misguess=0; new_word = 0;
		while ((misguess < mistake_limit) && (new_word == 0)) {
			char c = getch();

			// if user enters [Esc] then directly goto main menu
			if (c == ESC) { main_menu(); break; }

			if (!isalpha(c)) continue;

			// check if the letter is already guessed before
			already_guessed = 0;
			for (i=0; i<letter_count; i++)
				if (toupper(c) == guessed_letters[i]) already_guessed=1;
			if (already_guessed) continue;

			// if not already guessed
			guessed_letters[letter_count] = toupper(c); letter_count++;

			// display the guessed letters
			for (i=0; i<letter_count; i++) {
				gotoxy(4+2*i, 15); printf("%c ", toupper(guessed_letters[i]));
			}

			// check if the guessed letter belongs to the current word and display in blank
			for (i=0; i<length; i++) {
				for (j=0; j<letter_count; j++) {
					if (word[i] == guessed_letters[j]) {
						gotoxy(9+i*2, 11);
						printf("%c", word[i]);
					}
				}
			}

			// count the number of correct guesses
			correct_guess=0; int encountered;
			for (i=0; i<length; i++) {
				guessed = 0; // assume that word is not guessed

				// check if the letter repeates in the word
				encountered = 0;
				for (j=i+1; j<length; j++) {
					if (word[i] == word[j]) encountered=1;
				}

				// if a letter doesn't repeat after that position, then check whether it is guessed
				if (encountered) continue;
				for (j=0; j<letter_count; j++)
						if (word[i] == guessed_letters[j]) guessed=1;
				if (guessed) correct_guess++;
			}

			misguess = letter_count - correct_guess;
			display_hangman(misguess);

			// if 7 miguesses are made
			if (misguess == 7) {
				lives--;
				gotoxy(4, 18); printf("TIME UP! The word was %s. Press any key to continue", word);
				new_word = 1;
				if (getch() == ESC) main_menu();
			}

			// if the word is completed
			if (correct_guess == alpha_count(word, length)) {
				answerd++;
				gotoxy(4, 18); printf("YES! You got it right! Press any key to continue...");
				new_word = 1;
				if (getch() == ESC) main_menu();
			}
		}

	}

	free(data);
	free(words_asked);

	// if the player loses all lives
	system("cls");
	display_title();

	gotoxy(4, 8);
	printf("You solved %d out of %d words", answerd, asked);
	display_footer();

	gotoxy(4, 10); printf("Enter your name? "); getstr(name, sizeof(name), stdin);
	save_record(name, answerd);

	gotoxy(4, 13); printf("Record added successfully!");
	getch(); main_menu();
}
