#include <stdio.h>
#include <string.h>

#define file "./14input.txt" 
#define testfile "./14test.txt"
#define LINE_SIZE 102
#define LINES 100
//#define LINES 10

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen(file, "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

void moveStone(char input[][LINE_SIZE], int x, int y) {
	input[x][y] = '.';
	while (x > -1 && !strchr("#O", input[x][y])) {
		x--;
	}
	input[x + 1][y] = 'O';
	printf(" -> %d %d\n", x + 1, y);
}

void tiltPlatform(char input[][LINE_SIZE]) {
	for (int i = 1; i < LINES; i++) {
		for (int j = 0; j < (int)strlen(input[0]) - 1; j++) {
			if (input[i][j] == 'O') { 
				printf("%d %d", i, j);
				moveStone(input, i, j); 
			}		
		}
	}
}

int countWeight(char input[][LINE_SIZE]) {
	int sum = 0;
	for (int i = 0; i < LINES; i++) {
		for (int j = 0; j < (int)strlen(input[0]); j++) {
			if (input[i][j] == 'O') { sum += LINES - i; printf("%d %d %d\n", LINES - i, i, j);}	
		}
	
	}
	return sum;
}

int main() {
	char input[LINES][LINE_SIZE];
	puts("here");
	readInput(input);
	puts("here");
	//printf("%ld\n", strlen(input[0]));
	//printf("%c\n", input[1][3]);
	puts("test");
	tiltPlatform(input);
	puts("test2");
	for (int i = 0; i < LINES; i++) {
		fprintf(stdout, "%d %s",i, input[i]);
	}
	int result = countWeight(input);
	printf("%d\n", result);
	return 0;
}
