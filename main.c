#include "hangman.h"

int main(void) {
	srand(time(NULL));
	display_loading();
	main_menu();
	return 0;
}
