#include <stdio.h>

int main(int argc, char *argv[]) {

	int i = 0;
	if (argc == 2) {
		printf("You only have one argument. Bleh.\n");
	} else if (argc == 1) {
				printf("I am cool for now!\n");
	} else if (argc > 1 && argc < 4) {
				printf("Here are your arguments:\n");
				
				for (i = 0; i < argc; i++) {
					printf("%s ", argv[i]);				
				}
				printf("\n");
			} else {
				printf("You have too many arguments. Staaaahp!!!!!\n");
			}
			
			return 0;
}
