#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_SIZE 3500
#define LINES 1001

int readInput(char prompts[][LINE_SIZE]){
    FILE *input = fopen("./03input.txt", "r");
    int i = 0;
    if (input != NULL){
        while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
    }
    return (fclose(input) & 0) | (i - 1);
}

void parseInput(const int lines, char input[][LINE_SIZE]) {
  int sum = 0;
    for (int i = 0; i < lines; i++) {
      int running = 0, num1 = 0, num2 = 0;
        for (int j = 0; ; j++) {
          printf("%d %d %c\n", j, running, input[i][j]);
          if (input[i][j] == '\n') {
            break;
          }
          if (input[i][j] == 'l' && input[i][j-1] == 'u' && input[i][j-2] == 'm') {
            puts("running 1");
            running = 1;
            continue;
          }
          if (running == 1) {
            if (input[i][j] == '(') {
              puts("running 2");
              running = 2;
              continue;
            } else {
            running = 0;
          	}
          }
          if (running == 2) {
            if (isdigit(input[i][j])) {
              puts("running 3");
              num1 = 10 * num1 + (input[i][j] -'0');
            } else if (input[i][j] == ',' && num1 > 0) {
              running = 3;
              continue;
              } else {
                running = 0;
                num1 = 0;
              }
          }
          if (running == 3) {
            if (isdigit(input[i][j])) {
              num2 = 10 * num2 + (input[i][j] -'0');
            } else if (input[i][j] == ')' && num2 > 0) {
              printf(" %d %d %d\n", num1, num2, num1 * num2);
              sum += num1 * num2;
              running = 0;
              num1 = 0;
              num2 = 0;
              running = 0;
              continue;
              } else {
                puts("running 3 resetting");
                running = 0;
                num1 = 0;
                num2 = 0;
              }
          }
    }
  }
  printf("The sum of the number is %d.\n", sum);
}

int main(int argc, char *argv[]) {
    char input[LINES][LINE_SIZE];
    const int lineCount = readInput(input);
    for (int i = 0; i < lineCount; i++) {
		fprintf(stdout, "%d %s",i, input[i]);
	}
    parseInput(lineCount, input);

    return 0;
}