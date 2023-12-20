#include <stdio.h>
#include <string.h>

#define file "./13input.txt" 
#define testfile "./13test.txt"
#define LINE_SIZE 20
#define LINES 1356
//#define LINES 16

typedef struct mirror {
	int columns;
	int lines;
	char field[25][25];
} Mirror;

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen(file, "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

int parseInput(char input[][LINE_SIZE], Mirror mirrors[LINES / 5]) {
	int mirrorCount = 0, count = 0;
	for (int i = 0; i < LINES; i++) {
		if (strlen(input[i]) == 1) {
			mirrors[mirrorCount].lines = count;
			mirrors[mirrorCount].columns = strlen(mirrors[mirrorCount].field[0]) - 1;
			count = 0;
			mirrorCount++;
		} else {
			strcpy(mirrors[mirrorCount].field[count], input[i]);
			count++;
		}
	}
	return mirrorCount;
}

Mirror rotateInput(Mirror mirror, Mirror rotation) {
	rotation.lines = mirror.columns;
	rotation.columns = mirror.lines;
	for (int j = 0; j < mirror.columns; j++) {
		//rotation.field[j][1] = '.';
		for (int i = 0; i <= mirror.lines; i++) {
			rotation.field[j][i] = mirror.field[i][j];
		}
	}
	return rotation;
}

int countDifferences(int columns, int indexA, int indexB, Mirror mirror) {
	//printf("%s", mirror.field[indexA]);
	//printf("%s", mirror.field[indexB]);
	int errCount = 0;
	for (int i = 0; i <= columns; i++) {
		if (mirror.field[indexA][i] != mirror.field[indexB][i]) {
			errCount++;	
		}
	}
	if (errCount == 1) {
	//printf("%d %s", indexA, mirror.field[indexA]);
	//printf("%d %s", indexB, mirror.field[indexB]);
	}
	return errCount;
}

int isValidMirror(Mirror mirror, int sideA, int sideB, int part) {
	int diffCount = 0;
	while (sideA >= 0 && sideB <= mirror.lines) {
		if (sideA < 0 || sideB >= mirror.lines) { return 1; }
		if (!strcmp(mirror.field[sideA], mirror.field[sideB])) {
			sideA--;
			sideB++;		
		} else {
			if (part == 1 || diffCount >= 1) { return 0; }
			if (countDifferences(mirror.columns, sideA, sideB, mirror) > 1) { return 0; }
			sideA--;
			sideB++;
			diffCount++;
		}
	}
	return 1;
}

int getMirrorValue(Mirror mirror, int isRotated, int part, int mirrorValue) {
	//printf("Part: %d\n", part);
	for (int i = 0; i < mirror.lines; i++) {
		if (i < mirror.lines - 1) {
			int diffs = countDifferences(mirror.columns, i, i + 1, mirror);
			if (diffs < 2 && isValidMirror(mirror, i, i + 1, part)) {
				int value = (i + 1) * 100;
				//printf("Value: %d\n", (i + 1) * 100);
				if (value != mirrorValue ) { return value; }
				//if (value != mirrorValue) { return (i + 1) * 100; }
			}
		}
	}
	if (!isRotated) {
		Mirror rotation = rotateInput(mirror, rotation);
		//printf("rotated\n");
		int value = getMirrorValue(rotation, 1, part, mirrorValue) / 100; 
		if (value != mirrorValue ) { return value; }
	}

	return mirrorValue;
}

int main() {
	char input[LINES][LINE_SIZE];
	Mirror mirrors[LINES / 5];
	readInput(input);
	int mirrorCount = parseInput(input, mirrors);
	int sum = 0, sum2 = 0;
//	for (int i = 0; i < mirrorCount; i++) {
//		int possibleSwaps = 0;
//		for (int j = 0; j < mirrors[i].columns - 1; j++) {
//			if (countDifferences(mirrors[i].columns, j, j + 1, mirrors[i]) == 1) {
//				possibleSwaps++;
//				printf("%d\n", isValidMirror(mirrors[i], j , j + 1, 2));
//			}
//		}
//		Mirror mirror = rotateInput(mirrors[i], mirror);
//		for (int j = 0; j < mirror.columns - 1; j++) {
//			if (countDifferences(mirror.columns, j, j + 1, mirror) == 1) {
//				possibleSwaps++;
//				printf("%d\n", isValidMirror(mirror, j , j + 1, 2));
//			}
//		}
//		printf("Mirror: %d Swaps: %d\n", i, possibleSwaps);
//	}

	//printf("%d\n", countDifferences(mirrors[1].columns, 5, 6, mirrors[1]));

	for (int i = 0; i < mirrorCount; i++) {
		printf("\nMirror: %d\n", i);
		int mirrorValue = getMirrorValue(mirrors[i], 0, 1, 0);
		sum += mirrorValue;
		sum2 += getMirrorValue(mirrors[i], 0, 2, mirrorValue);
		printf("%d\n", sum2);
	}
	printf("Part 1: %d\n", sum);
	printf("Part 2: %d\n", sum2);
	return 0;
}
