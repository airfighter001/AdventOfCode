#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 142
#define LINES 140

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./12input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int * getRegionPrice(char input[][LINE_SIZE], int lines, int traversed[][LINE_SIZE], int x, int y) {
	int *result = (int *)calloc(sizeof(int), 2);
    if (x - 1 < 0 || input[x-1][y] != input[x][y]) result[1]++;
	if (x + 1 > lines || input[x+1][y] != input[x][y]) result[1]++;
	if (y - 1 < 0 || input[x][y-1] != input[x][y]) result[1]++;
	if (y + 1 > lines || input[x][y+1] != input[x][y]) result[1]++;
    traversed[x][y] = 1;
    result[0]++;
	if (x - 1 >= 0 && input[x-1][y] == input[x][y] && traversed[x-1][y] == 0) {
		int *upResult = getRegionPrice(input, lines, traversed, x - 1, y);
		result[0] += upResult[0];
		result[1] += upResult[1];
	}
	if (x + 1 < lines && input[x+1][y] == input[x][y] && traversed[x+1][y] == 0) {
		int *downResult = getRegionPrice(input, lines, traversed, x + 1, y);
		result[0] += downResult[0];
		result[1] += downResult[1];
	}
	if (y - 1 >= 0 && input[x][y-1] == input[x][y] && traversed[x][y-1] == 0) {
		int *leftResult = getRegionPrice(input, lines, traversed, x, y - 1);
		result[0] += leftResult[0];
		result[1] += leftResult[1];
	}
	if (y + 1 < lines && input[x][y+1] == input[x][y] && traversed[x][y+1] == 0) {
		int *rightResult = getRegionPrice(input, lines, traversed, x, y + 1);
		result[0] += rightResult[0];
		result[1] += rightResult[1];
	}
	return result;
}

void buildFencingPrice(char input[][LINE_SIZE], int lines, int traversed[][LINE_SIZE], int traversed2[][LINE_SIZE]) {
    int sum = 0, sum2 = 0;
	for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {
        	if (traversed[i][j] == 0) {
                int * region = getRegionPrice(input, lines, traversed,i,j);
                sum += region[0] * region[1];
        	}
        }
	}
    printf("The sum of the fencing prices is %d\n", sum);
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
	int traversed[LINES][LINE_SIZE] = {};
    int traversed2[LINES][LINE_SIZE] = {};
	int lineCount = readInput(input);
    buildFencingPrice(input, lineCount, traversed, traversed2);
	return 0;
}
