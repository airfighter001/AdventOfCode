#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define LINE_SIZE 128

typedef struct alu {
  long regA, regB, regC;
  long op[16], ops;
  char opStr[64];
} Alu;
long ml = LONG_MAX;

int readInput(char prompts[][LINE_SIZE]){
	FILE *input = fopen("./17input.txt", "r");
	int i = 0;
	if (input != NULL){
		while (fgets(prompts[i++],LINE_SIZE,input) != NULL) {}
	}
	return (fclose(input) & 0) | (i - 1);
}

Alu parseInput(char input[][LINE_SIZE]) {
	Alu alu;
	sscanf(input[0], "Register A: %ld", &alu.regA);
    const char *ptr = input[4];
    int i = 0;
    char * progStart = strchr(input[4], ' ') + 1;
    strcpy(alu.opStr, progStart);
	while (sscanf(ptr, "%*[^0-9]%ld", &alu.op[i]) == 1) {
		ptr = strchr(ptr, alu.op[i++] + '0');
		if (ptr) ptr++;
	}
    alu.ops = i - 1;
    return alu;
}

char * runInstr(Alu alu, char program[64]) {
    int opPos = 0, progPos = 0, cycles = 0;
    while (1) {
        cycles++;
        if (opPos >= alu.ops || cycles > 10000) {program[progPos++] = '\0'; return program;}
        switch (alu.op[opPos]) {
            case 0: {
                long denom = -1;
                if (alu.op[opPos + 1] < 4) denom = alu.op[opPos + 1];
                if (alu.op[opPos + 1] == 4) denom = alu.regA;
                if (alu.op[opPos + 1] == 5) denom = alu.regB;
                if (alu.op[opPos + 1] == 6) denom = alu.regC;
                alu.regA = alu.regA / pow(2, denom);
                opPos += 2;
                break;
            }
            case 1: {
                alu.regB = alu.regB ^ alu.op[opPos + 1];
                opPos += 2;
                break;
            }
            case 2: {
                long operand = 0;
                if (alu.op[opPos + 1] < 4) operand = alu.op[opPos + 1];
                if (alu.op[opPos + 1] == 4) operand = alu.regA;
                if (alu.op[opPos + 1] == 5) operand = alu.regB;
                if (alu.op[opPos + 1] == 6) operand = alu.regC;
                alu.regB = operand % 8;
                opPos += 2;
                break;
            }
            case 3: {
                if (alu.regA == 0) {
                    opPos += 2;
                    break;
                }
                opPos = alu.op[opPos + 1];
                break;
            }
            case 4: {
                alu.regB = alu.regB ^ alu.regC;
                opPos += 2;
                break;
            }
            case 5: {
                long operand = 0;
                if (alu.op[opPos + 1] < 4) operand = alu.op[opPos + 1];
                if (alu.op[opPos + 1] == 4) operand = alu.regA;
                if (alu.op[opPos + 1] == 5) operand = alu.regB;
                if (alu.op[opPos + 1] == 6) operand = alu.regC;
                if (progPos != 0) program[progPos++] = ',';
                program[progPos++] = '0' + (operand % 8);
                opPos += 2;
                break;
            }
            case 6: {
                long denom = -1;
                if (alu.op[opPos + 1] < 4) denom = alu.op[opPos + 1];
                if (alu.op[opPos + 1] == 4) denom = alu.regA;
                if (alu.op[opPos + 1] == 5) denom = alu.regB;
                if (alu.op[opPos + 1] == 6) denom = alu.regC;
                alu.regB = alu.regA / pow(2, denom);
                opPos += 2;
                break;
            }
            case 7: {
                long denom = -1;
                if (alu.op[opPos + 1] < 4) denom = alu.op[opPos + 1];
                if (alu.op[opPos + 1] == 4) denom = alu.regA;
                if (alu.op[opPos + 1] == 5) denom = alu.regB;
                if (alu.op[opPos + 1] == 6) denom = alu.regC;
                alu.regC = alu.regA / pow(2, denom);
                opPos += 2;
                break;
            }
        }
    }
}

void buildArray(char out[64], long nums[]) {
    char *ptr = out;
    int i = 0;
    while (*ptr != '\0') {
        if (sscanf(ptr, "%*[^0-9]%ld", &nums[i]) == 1) {
            printf("Parsed number: %ld\n", nums[i]);
            while (*ptr != '\0' && (*ptr < '0' || *ptr > '9')) {
                ptr++;
            }
            while (*ptr >= '0' && *ptr <= '9') {
                ptr++;
            }
            i++;
        } else {
            break;
        }
    }

    printf("\nFinal numbers in the array:\n");
    for (int j = 0; j <= i; j++) {
        printf("%ld ", nums[j]);
    }
    printf("\n");
}

void minReg(Alu alu, int iter, long regA) {
    if (iter > alu.ops) return;
    long baseReg = 8 * regA;
    char prog[64];
    for (int i = 0; i < 8; i++) {
      alu.regA = baseReg + i;
      runInstr(alu, prog);
	  int isValid = !strcmp(prog, &alu.opStr[strlen(alu.opStr) - strlen(prog)]);
      if (isValid && iter == alu.ops) {
        if(ml == LONG_MAX) {
          printf("%ld\n", baseReg + i);
          ml=0;
        }
        return;
      }
      if (isValid) { minReg(alu, iter + 1, baseReg + i);}
      if (iter > alu.ops + 1) return;
    }
}

int main(int argc, char** argv) {
	char input[5][LINE_SIZE];
	readInput(input);
    char program[64];
    Alu instr = parseInput(input);
    instr.regB = 0;
    instr.regC = 0;
    runInstr(instr, program);
    printf("Output: %s\n", program);
    minReg(instr, 0, 0);
	return 0;
}