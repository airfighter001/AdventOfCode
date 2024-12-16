#include <stdio.h>
#include <string.h>

#define LINE_SIZE 143
#define LINES 143

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./16input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

void findPath(int lines, char input[][LINE_SIZE], int costMap[][LINES], int xStart, int yStart, int xDir, int yDir) {
	if (input[xStart + xDir][yStart + yDir] != '#' && costMap[xStart + xDir][yStart + yDir] > costMap[xStart][yStart] + 1) {
        costMap[xStart + xDir][yStart + yDir] = costMap[xStart][yStart] + 1;
        findPath(lines, input, costMap, xStart + xDir, yStart + yDir, xDir, yDir);
	}
    if (input[xStart+0][yStart+1] != '#' && costMap[xStart+0][yStart+1] > costMap[xStart][yStart] + 1001) {
    	costMap[xStart + 0][yStart + 1] = costMap[xStart][yStart] + 1001;
    	findPath(lines, input, costMap, xStart + 0, yStart + 1, 0, 1);
    }
	if (input[xStart+0][yStart-1] != '#' && costMap[xStart+0][yStart-1] > costMap[xStart][yStart] + 1001) {
		costMap[xStart + 0][yStart - 1] = costMap[xStart][yStart] + 1001;
		findPath(lines, input, costMap, xStart + 0, yStart - 1, 0, -1);
	}
	if (input[xStart+1][yStart+0] != '#' && costMap[xStart+1][yStart+0] > costMap[xStart][yStart] + 1001) {
		costMap[xStart + 1][yStart + 0] = costMap[xStart][yStart] + 1001;
		findPath(lines, input, costMap, xStart + 1, yStart + 0, 1, 0);
	}
	if (input[xStart-1][yStart+0] != '#' && costMap[xStart-1][yStart+0] > costMap[xStart][yStart] + 1001) {
		costMap[xStart - 1][yStart + 0] = costMap[xStart][yStart] + 1001;
		findPath(lines, input, costMap, xStart - 1, yStart + 0, -1, 0);
	}
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
	int lineCount = readInput(input);
    int costMap[LINES][LINES];
    for (int i = 0; i < lineCount; i++) {
      for (int j = 0; j < lineCount; j++) {
        costMap[i][j] = 90000000;
      }
    }
    costMap[lineCount - 2][1] = 0;
	findPath(lineCount, input, costMap, lineCount - 2, 1, 0,1);
	printf("Cheapest Path: %d\n", costMap[1][lineCount - 2]);
	return 0;
}
