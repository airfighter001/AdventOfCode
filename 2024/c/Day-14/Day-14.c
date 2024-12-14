#include <stdio.h>
#include <string.h>

#define LINE_SIZE 128
#define LINES 512
//#define GRID_X 7
//#define GRID_Y 11
#define GRID_X 103
#define GRID_Y 101

typedef struct bot {
    int pos[2],vel[2];
} Bot;

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./14input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

void parseInput(char input[LINES][LINE_SIZE], int lines, Bot bots[]) {
  for (int i = 0; i < lines; i++) {
     sscanf(input[i], "p=%d,%d v=%d,%d\n", &bots[i].pos[1], &bots[i].pos[0], &bots[i].vel[1], &bots[i].vel[0]);
  }
}

void printGrid(int lines, Bot bots[]) {
  char grid[GRID_X][GRID_X];
  for (int i = 0; i < GRID_X; i++) {
    for (int j = 0; j < GRID_Y; j++) {
      grid[i][j] = '.';
    }
  }
  for (int i = 0; i < lines; i++) {
    grid[bots[i].pos[0]][bots[i].pos[1]] = 'X';
  }
  for (int i = 0; i < GRID_X; i++) {
    for (int j = 0; j < GRID_Y; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
}

void doCycles(int lines, Bot bots[]) {
  for (int i = 0; i < lines; i++) {
    bots[i].pos[0] = (bots[i].pos[0] + 100 * bots[i].vel[0]) % GRID_X;
    if (bots[i].pos[0] < 0) bots[i].pos[0] = GRID_X + bots[i].pos[0];
    bots[i].pos[1] = (bots[i].pos[1] + 100 * bots[i].vel[1]) % GRID_Y;
    if (bots[i].pos[1] < 0) bots[i].pos[1] = GRID_Y + bots[i].pos[1];
  }
}

int getSafetyLevel(int lines, Bot bots[]) {
  int counts[4] = {0};
  for (int i = 0; i < lines; i++) {
    if (bots[i].pos[0] < GRID_X/2 && bots[i].pos[1] < GRID_Y/2) counts[0]++;
    if (bots[i].pos[0] < GRID_X/2 && bots[i].pos[1] > GRID_Y/2) counts[1]++;
    if (bots[i].pos[0] > GRID_X/2 && bots[i].pos[1] < GRID_Y/2) counts[2]++;
    if (bots[i].pos[0] > GRID_X/2 && bots[i].pos[1] > GRID_Y/2) counts[3]++;
  }
  return counts[0] * counts[1] * counts[2] * counts[3];
}

void runEasterEgg(int lines, Bot bots[]) {
  for (int i = 0; i < lines; i++) {
    bots[i].pos[0] = (bots[i].pos[0] + bots[i].vel[0]) % GRID_X;
    if (bots[i].pos[0] < 0) bots[i].pos[0] = GRID_X + bots[i].pos[0];
    bots[i].pos[1] = (bots[i].pos[1] + bots[i].vel[1]) % GRID_Y;
    if (bots[i].pos[1] < 0) bots[i].pos[1] = GRID_Y + bots[i].pos[1];
  }
  //printGrid(lines, bots);
}

int checkBots(int lines, Bot bots[]) {
  int grid[GRID_X][GRID_Y] = {0};
  for (int i = 0; i < lines; i++) {
    grid[bots[i].pos[0]][bots[i].pos[1]]++;
  }
  for (int i = 0; i < GRID_X; i++) {
    for (int j = 0; j < GRID_Y; j++) {
      if (grid[i][j] > 1) {
        return 0;
      }
    }
  }
  return 1;
}

int main(int argc, char** argv) {
	char input[LINES][LINE_SIZE];
	int lineCount = readInput(input);
  Bot bots[lineCount];
  parseInput(input, lineCount, bots);
  doCycles(lineCount, bots);
  printf("Safety Level: %d\n",getSafetyLevel(lineCount, bots));
  parseInput(input, lineCount, bots);
  int i = 0;
  while (1) {
    runEasterEgg(lineCount, bots);
    i++;
    if (checkBots(lineCount, bots)) {
      printGrid(lineCount, bots);
      printf("%d\n", i);
    }
  }
  printGrid(lineCount, bots);
  printf("%d\n", i);
	return 0;
} 
