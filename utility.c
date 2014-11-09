#include "hangman.h"

void gotoxy(int x,int y) {
	COORD coord={0,0}; 		// center of axis is set to (0,0)
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

char* getstr(char* name, int sizeof_arr, FILE* file) {
	fgets(name, sizeof_arr, file);
	if (strlen(name)>0 && name[strlen(name) - 1]=='\n')
		name[strlen(name) - 1] = '\0';
	return name;
}

void error(char * msg) {
	fprintf(stderr, "\n\n%s", msg);
	exit(1);
}

int line_count(FILE *file) {
	rewind(file);
	int ncount=0;
	while (!feof(file))
		if (fgetc(file) == '\n')
			ncount++;
	rewind(file);
	return ncount;
}

int alpha_count(char *word, int length) {
	int c = 0, found, i, j;
	char encountered[length];
	for (i=0; i<length; i++) {
		if (!isalpha(word[i])) continue;
		found = 0;
		for (j=0; j<c; j++) {
			if (word[i] == encountered[j]) found=1;
		}
		if (found) continue;
		encountered[c] = word[i]; c++;
	}
	return c;
}

int random(int n) {
	return (rand() % n);
}

char* s_toupper(char *string) {
	int i;
	for (i=0; i<strlen(string); i++) {
		if(isalpha(string[i]))
			string[i] = toupper(string[i]);
	}
	return string;
}

void swap_record(RECORD *r1, RECORD *r2) {
	RECORD temp;
	temp = *r1;
	*r1 = *r2;
	*r2 = temp;
}

void display_loading(void) {
	system("COLOR 0F");

	int x=25, y=10, i, j;
	gotoxy(x,y);
		printf("Loading...");
		for (j=0; j<50000000; j++);
	for (i=0; i<10; i++) {
		for (j=0; j<50000000; j++);
		gotoxy(x+i, y+2); printf("%c", 219);
	}

	for (j=0; j<100000000; j++);

	system("cls");
	gotoxy(x,y); printf("Press any key...");
	getch();
}

void display_hangman(int misguess) {
	//display the initial frame
	int x=52, y=6, i, j;
	gotoxy(x, y+0); 	printf("   _________ ");
	gotoxy(x, y+1); 	printf("   |      || ");
	gotoxy(x, y+2); 	printf("          || ");
	gotoxy(x, y+3); 	printf("          || ");
	gotoxy(x, y+4); 	printf("          || ");
	gotoxy(x, y+5); 	printf("          || ");
	gotoxy(x, y+6); 	printf("          || ");
	gotoxy(x, y+7); 	printf("          || ");
	gotoxy(x, y+8); 	printf("________  || ");
	gotoxy(x, y+9);		printf("||    ||  || ");
	gotoxy(x-1, y+10); printf("_||____||__|| ");

	// first, make the head
	if (misguess >= 1) {
		gotoxy(x, y+1); printf("  _|_     || ");
		gotoxy(x, y+2); printf(" /o o\\    || ");
		gotoxy(x, y+3); printf(" \\_0_/    || ");
	}

	// second, make the backbone
	if (misguess>=2) {
		gotoxy(x, y+4); printf("   |      || ");
		gotoxy(x, y+5); printf("   |      || ");
		gotoxy(x, y+6); printf("   |      || ");
	}

	// third, make one hands
	if (misguess >= 3) {
		gotoxy(x, y+5);	printf("  /|      || ");
		gotoxy(x, y+6); printf(" / |      || ");
	}

	// four, make another hand
	if (misguess >= 4) {
		gotoxy(x, y+5);	printf("  /|\\     || ");
		gotoxy(x, y+6); printf(" / | \\    || ");
	}

	// five, make one leg
	if (misguess >= 5) {
		gotoxy(x, y+7); printf("  /       || ");
		gotoxy(x, y+8); printf("_/______  || ");
	}

	// six, make another leg
	if (misguess >= 6) {
		gotoxy(x, y+7); printf("  / \\     || ");
		gotoxy(x, y+8); printf("_/___\\__  || ");
	}

	// seven, hang the man
	if (misguess >=7 ) {
		gotoxy(x, y+0);	printf("   _________");
		gotoxy(x, y+1);	printf("   |      ||");
		gotoxy(x, y+2);	printf("  _|_     ||");
		gotoxy(x, y+3);	printf(" /_ _\\    ||");
		gotoxy(x, y+4);	printf(" \\_^_/    ||");
		gotoxy(x, y+5);	printf("   |      ||");
		gotoxy(x, y+6);	printf("  /|\\     ||");
		gotoxy(x, y+7);	printf(" / | \\    ||");
		gotoxy(x, y+8);	printf("  / \\     ||");
		gotoxy(x, y+9);	printf(" /   \\    ||");
		gotoxy(x, y+10);printf("__________||");
	}
}

int nelem(FILE* file, int esize) {
	rewind(file);
	char* c = malloc(esize);

	int n;
	for (n=0; fread(c, esize, 1, file); n++);

	free(c); rewind(file);
	return n;
}

void display_footer(void) {
	gotoxy(0, 20);
	printf("  ---------------------------------------------------------------- \n");
	printf("    Press [Esc] to go to main menu ");
}

void save_record(char *name, int score) {
	FILE *scores = fopen("scorefile", "a");

	RECORD R;
	strcpy(R.name, name);
	R.score = score;

	fwrite(&R, sizeof(R), 1, scores);

	fclose(scores);
}
