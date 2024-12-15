#include <stdio.h>
#include <string.h>

#define LINE_SIZE 5000
#define LINES 80

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./15input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int parseInput(int lines, char input[][LINE_SIZE], int grid[][LINES], int botPos[2]) {
  int movementStart = 0, isGrid = 1;
  while(isGrid) {
    if(strlen(input[movementStart]) == 1) break;
    int i = 0;
    while(input[movementStart][i] != '\n') {
      if (input[movementStart][i] == '@') {
        botPos[0] = movementStart;
        botPos[1] = i;
      }
      grid[movementStart][i] = input[movementStart][i];
      i++;
    }
    i = 0;
    movementStart++;
  }
  return movementStart + 1;
}

void printGrid(int grid[][LINES]) {
  for(int i = 0; i < LINES/2; i++) {
    for(int j = 0; j < LINES/2; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }

}

void tryPushStones(int grid[][LINES], int botPos[2], int dir[2]) {
  int stonePos[2] = {botPos[0] + dir[0], botPos[1] + dir[1]};
  if(grid[stonePos[0]][stonePos[1]] == '.') return;
  if(grid[stonePos[0] + dir[0]][stonePos[1] + dir[1]] == 'O') {
    tryPushStones(grid, stonePos, dir);
  }
  if(grid[stonePos[0] + dir[0]][stonePos[1] + dir[1]] == '#') return;
  if(grid[stonePos[0] + dir[0]][stonePos[1] + dir[1]] == '.') {
    grid[stonePos[0] + dir[0]][stonePos[1] + dir[1]] = 'O';
    grid[stonePos[0]][stonePos[1]] = '.';
  }
}

void moveRobot(int start, int grid[][LINES], char input[][LINE_SIZE], int lines, int botPos[2]) {
  int dir[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}}, pos = 0, currDir = -1;
  while(start < lines) {
    if(input[start][pos] == '\n') {
      pos = 0;
      start++;
      continue;
    }
    if(input[start][pos] == '^') currDir = 2;
    if(input[start][pos] == 'v') currDir = 0;
    if(input[start][pos] == '>') currDir = 1;
    if(input[start][pos] == '<') currDir = 3;
    if(grid[botPos[0]+dir[currDir][0]][botPos[1]+dir[currDir][1]] == '#') {
      pos++;
      continue;
    }
    if(grid[botPos[0]+dir[currDir][0]][botPos[1]+dir[currDir][1]] == '.') {
      grid[botPos[0]][botPos[1]] = '.';
      botPos[0] = botPos[0] + dir[currDir][0];
      botPos[1] = botPos[1] + dir[currDir][1];
      grid[botPos[0]][botPos[1]] = '@';
      pos++;
      continue;
    }
    tryPushStones(grid, botPos, dir[currDir]);
    if(grid[botPos[0]+dir[currDir][0]][botPos[1]+dir[currDir][1]] == '.') {
      grid[botPos[0]][botPos[1]] = '.';
      botPos[0] = botPos[0] + dir[currDir][0];
      botPos[1] = botPos[1] + dir[currDir][1];
      grid[botPos[0]][botPos[1]] = '@';
      pos++;
      continue;
    }
    pos++;
    //printGrid(grid);
  }
}

int sumGPS(int grid[][LINES]) {
  int sum = 0;
  for(int i = 0; i < LINES; i++) {
    for(int j = 0; j < LINES; j++) {
      //printf("%d %d %d\n", sum, grid[i][j], 'O');
      if(grid[i][j] == 'O') sum += (100 * i + j);
    }
  }
  return sum;
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
  int botPos[2];
	int lineCount = readInput(input);
	//for (int i = 0; i < lineCount; i++) {
	//	fprintf(stdout, "%d %s",i, input[i]);
	//}
  int grid[LINES][LINES];
  int start = parseInput(lineCount, input, grid, botPos);
  //printf("%d \n", start);
  //printf("%d %d\n", botPos[0], botPos[1]);
  int dir[2] = {0,-1};
  moveRobot(start, grid, input, lineCount, botPos);
  int sum = sumGPS(grid);
  printf("%d\n", sum);
	return 0;
}
