#include <stdio.h>
#include <string.h>

#define file "./15input.txt" 
#define testfile "./15test.txt"
#define LINE_SIZE 22802
//#define LINE_SIZE 53
#define LINES 1

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen(file, "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int gethash(char input[LINE_SIZE]) {
	char *token, *rest;
	int result = 0, sum = 0;
	rest = strtok(input, "\n");
	while ((token = strtok_r(rest, ",", &rest)) != NULL) {
		printf("%s\n", token);
		for (int i = 0; i < (int)strlen(token); i++) {
			result += token[i];
			result *= 17;
			result %= 256;
			//printf("%d\n", result);
		}
		sum += result;
		result = 0;
	}
	return sum;
}

int main() {
	char input[LINES][LINE_SIZE];
	readInput(input);
	char hash[LINE_SIZE];
	strncpy(hash, *input, LINE_SIZE);
	printf("Hash value is: %d\n", gethash(hash));
	//fprintf(stdout, "%s", hash);
	return 0;
}
