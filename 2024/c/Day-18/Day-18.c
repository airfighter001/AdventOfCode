#include <stdio.h>
#include <string.h>

#define LINE_SIZE 32
#define LINES 3450
#define DIM 71
#define P1 1024

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./18input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

void parseInput(char input[][LINE_SIZE], char grid[DIM][DIM]) {
    int x = 0 ,y = 0;
	for (int i = 0; i < P1; i++) {
		sscanf(input[i], "%d,%d", &y, &x);
        grid[x][y] = '#';
    }
}

void findPath(char grid[DIM][DIM], int costmap[DIM][DIM], int x, int y, int cost) {
	if(x < 0 || x >= DIM || y < 0 || y >= DIM) return;
    if(costmap[x][y] <= cost || grid[x][y] == '#') return;
    costmap[x][y] = cost;
    findPath(grid,costmap,x+1,y,cost + 1);
	findPath(grid,costmap,x-1,y,cost + 1);
	findPath(grid,costmap,x,y+1,cost + 1);
	findPath(grid,costmap,x,y-1,cost + 1);
}

void findBlockCoords(char grid[DIM][DIM], char input[][LINE_SIZE]) {
    int i = P1;
	while (1) {
		int x = 0 ,y = 0;
		sscanf(input[i++], "%d,%d", &y, &x);
		grid[x][y] = '#';
        int costmap[DIM][DIM];
		for (int a = 0; a < DIM; a++) {
			for (int b = 0; b < DIM; b++) {
				costmap[a][b] = 99999999;
			}
		}
		costmap[0][0] = 1;
		findPath(grid, costmap, 0, 0, 0);
        if (costmap[DIM-1][DIM-1] == 99999999) {
        	printf("First blocking byte: (%d,%d)\n", y,x);
            return;
        }
    }
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE], grid[DIM][DIM];
    int costmap[DIM][DIM] = {0};
	int lineCount = readInput(input);
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            grid[i][j] = '.';
            costmap[i][j] = 99999999;
        }
    }
    parseInput(input, grid);
    costmap[0][0] = 1;
    findPath(grid, costmap, 0, 0, 0);
    printf("Minimum steps: %d\n", costmap[DIM-1][DIM-1]);
    findBlockCoords(grid, input);
	return 0;
}