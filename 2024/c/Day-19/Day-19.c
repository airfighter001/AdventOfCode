#include <stdio.h>
#include <string.h>

#define LINE_SIZE 3000
#define LINES 500

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./19input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

void parseInput(char inputs[][LINE_SIZE], char exPats[][20], char desPats[][100]) {
	int i = 0, exPatCount = 0, desPatCount = 0;
	char *token = strtok(inputs[i], ",");
	while (token != NULL) {
		char filteredToken[20] = {0};
		int k = 0;
		for (int j = 0; token[j] != '\0'; j++) {
			if (token[j] != ' ') {
				filteredToken[k++] = token[j];
			}
		}
		filteredToken[k] = '\0';
		strncpy(exPats[exPatCount], filteredToken, 19);
		exPats[exPatCount][19] = '\0';
		exPatCount++;
		token = strtok(NULL, ",");
	}
	i++;
	while (inputs[++i][0] != '\0') {
		strncpy(desPats[desPatCount], inputs[i], 99);
		desPats[desPatCount][strlen(inputs[i]) -1] = '\0';
		desPatCount++;
	}
}

int findMatchingPatternsRecursive(const char *desPat, char exPats[][20], int exPatCount, int position) {
	int desPatLen = strlen(desPat);
	if (position == desPatLen) {
		return 1;
	}
	for (int j = 0; j < exPatCount; j++) {
		int exPatLen = strlen(exPats[j]);
		if (exPatLen > 0 && position + exPatLen <= desPatLen && strncmp(&desPat[position], exPats[j], exPatLen) == 0) {
			if (findMatchingPatternsRecursive(desPat, exPats, exPatCount, position + exPatLen)) {
				return 1;
			}
		}
	}
	return 0;
}

int findMatchingPatterns(const char *desPat, char exPats[][20], int exPatCount) {
	if (findMatchingPatternsRecursive(desPat, exPats, exPatCount, 0)) {
		return 1;
	}
	return 0;
}

int main() {
	char input[LINES][LINE_SIZE] = {0};
	char exPats[LINES][20] = {0};
	char desPats[LINES][100] = {0};
	int lineCount = readInput(input);
	parseInput(input, exPats, desPats);
	int matchCount = 0;
	for (int i = 0; i < LINES && desPats[i][0] != '\0'; i++) {
		if (findMatchingPatterns(desPats[i], exPats, LINES)) {
			matchCount++;
		}
	}
	printf("Possible designs: %d\n", matchCount);
	return 0;
}