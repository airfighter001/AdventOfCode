#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 142
#define LINES 140

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./12test.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int * getRegionPrice(char input[][LINE_SIZE], int lines, int plots[][LINE_SIZE], int x, int y, int fieldCount) {
    int maxDims[4] = {x,x,y,y};
	int *result = (int *)calloc(sizeof(int), 2);
    if (x - 1 < 0 || input[x-1][y] != input[x][y]) result[1]++;
	if (x + 1 > lines || input[x+1][y] != input[x][y]) result[1]++;
	if (y - 1 < 0 || input[x][y-1] != input[x][y]) result[1]++;
	if (y + 1 > lines || input[x][y+1] != input[x][y]) result[1]++;
    plots[x][y] = fieldCount;
    result[0]++;
	if (x - 1 >= 0 && input[x-1][y] == input[x][y] && plots[x-1][y] == 0) {
		int *upResult = getRegionPrice(input, lines, plots, x - 1, y, fieldCount);
		result[0] += upResult[0];
		result[1] += upResult[1];
	}
	if (x + 1 < lines && input[x+1][y] == input[x][y] && plots[x+1][y] == 0) {
		int *downResult = getRegionPrice(input, lines, plots, x + 1, y, fieldCount);
		result[0] += downResult[0];
		result[1] += downResult[1];
	}
	if (y - 1 >= 0 && input[x][y-1] == input[x][y] && plots[x][y-1] == 0) {
		int *leftResult = getRegionPrice(input, lines, plots, x, y - 1, fieldCount);
		result[0] += leftResult[0];
		result[1] += leftResult[1];
	}
	if (y + 1 < lines && input[x][y+1] == input[x][y] && plots[x][y+1] == 0) {
		int *rightResult = getRegionPrice(input, lines, plots, x, y + 1, fieldCount);
		result[0] += rightResult[0];
		result[1] += rightResult[1];
	}
	return result;
}

int getNewFenceRules(int plots[][LINE_SIZE], int lines, int x, int y) {
    int sum = 0, counting = 1, gap = 0;
	for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {
        	if (counting && plots[i][j] == plots[x][y] && (i - 1 < 0 || plots[i-1][j] != plots[x][y])) {
            	sum++;
                counting = 0;
        	}
            if (counting == 0 && (plots[i][j] != plots[x][y] || plots[i-1][j] == plots[x][y])) {
            	gap = 1;
            }
            if (counting == 0 && gap == 1) {
            	counting = 1;
                gap = 0;
            }
        }
	}
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < lines; j++) {
			if (counting && plots[i][j] == plots[x][y] && (i +1 > lines || plots[i+1][j] != plots[x][y])) {
				sum++;
				counting = 0;
			}
			if (counting == 0 && (plots[i][j] != plots[x][y] || plots[i+1][j] == plots[x][y])) {
				gap = 1;
			}
			if (counting == 0 && gap == 1) {
				counting = 1;
				gap = 0;
			}
		}
	}
	for (int j = 0; j < lines; j++) {
		for (int i = 0; i < lines; i++) {
			if (counting && plots[i][j] == plots[x][y] && (j - 1 < 0 || plots[i][j-1] != plots[x][y])) {
				sum++;
				counting = 0;
			}
			if (counting == 0 && (plots[i][j] != plots[x][y] || plots[i][j-1] == plots[x][y])) {
				gap = 1;
			}
			if (counting == 0 && gap == 1) {
				counting = 1;
				gap = 0;
			}
		}
	}
	for (int j = 0; j < lines; j++) {
		for (int i = 0; i < lines; i++) {
			if (counting && plots[i][j] == plots[x][y] && (j + 1 > lines || plots[i][j+1] != plots[x][y])) {
				sum++;
				counting = 0;
			}
			if (counting == 0 && (plots[i][j] != plots[x][y] || plots[i][j+1] == plots[x][y])) {
				gap = 1;
			}
			if (counting == 0 && gap == 1) {
				counting = 1;
				gap = 0;
			}
		}
	}
    return sum;
}

void buildFencingPrice(char input[][LINE_SIZE], int lines, int plots[][LINE_SIZE]) {
    int sum = 0, sum2 = 0, fieldCount = 1;
	for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines; j++) {
        	if (plots[i][j] == 0) {
                int * region = getRegionPrice(input, lines, plots,i,j, fieldCount);
                fieldCount++;
                sum += region[0] * region[1];
                sum2 += region[0] * getNewFenceRules(plots, lines, i, j);
        	}
        }
	}
    printf("Calculating method 1: %d\nCalculating method 2: %d\n", sum, sum2);
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
	int plots[LINES][LINE_SIZE] = {};
	int lineCount = readInput(input);
    buildFencingPrice(input, lineCount, plots);
	return 0;
}