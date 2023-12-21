#include <stdio.h>
#include <string.h>

#define file "./xxinput.txt" 
#define testfile "./xxtest.txt"
#define LINE_SIZE 128
#define LINES 64

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen(file, "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
	int lineCount = readInput(input);
	for (int i = 0; i < lineCount; i++) {
		fprintf(stdout, "%d %s",i, input[i]);
	}
	return 0;
}
