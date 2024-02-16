#include <stdio.h>
#include <stdlib.h>

#define DBLEN 30000 // data buffer len
#define CMDLEN 30000 // max commands in a program

struct command
{
  char com;
  int operand;
};

void readc(FILE *file, struct command *commands, int *cp)
{
  char ch = '\0';
  char prevch = '\0';
  int bn = 0; // bracket number
  while (ch != EOF) {
    prevch = ch;
    ch = fgetc(file);
    commands[*cp].operand = 1;
    if (ch != prevch) {
      switch (ch) {
        case '+':
          commands[*cp].com = '+';
          (*cp)++;
          break;
        case '-':
          commands[*cp].com = '-';
          (*cp)++;
          break;
        case '>':
          commands[*cp].com = '>';
          (*cp)++;
          break;
        case '<':
          commands[*cp].com = '<';
          (*cp)++;
          break;
        case '[':
          commands[*cp].com = '[';
          commands[*cp].operand = bn;
          bn++;
          (*cp)++;
          break;
        case ']':
          commands[*cp].com = ']';
          bn--;
          commands[*cp].operand = bn;
          (*cp)++;
          break;
        case '.':
          commands[*cp].com = '.';
          (*cp)++;
          break;
        case ',':
          commands[*cp].com = ',';
          (*cp)++;
          break;
        default:
          break;
      }
    } else if (ch == '[') {
      commands[*cp].com = '[';
      commands[*cp].operand = bn;
      bn++;
      (*cp)++;
    } else if (ch == ']') {
      commands[*cp].com = ']';
      bn--;
      commands[*cp].operand = bn;
      (*cp)++;
    } else {
      commands[*cp-1].operand++;
    }
    if (bn < 0) {
      puts("Unclosed `]`!");
      exit(-1);
    }
  }
  if (bn != 0) {
    puts("Unclosed `[`!");
    exit(-1);
  }
}

void interpretate(struct command *coms, int max_cp) {
  char *db = calloc(DBLEN, 1); // data buffer
  if (db == NULL) {
    puts("Data buffer did not created!");
    free(coms);
    exit(-1);
  }
  int dp = 0; // data pointer
  int thisop = 0; // this operand

  for (int i = 0; i < max_cp; i++) {
    switch (coms[i].com) {
      case '+':
        db[dp] += coms[i].operand;
        break;
      case '-':
        db[dp] -= coms[i].operand;
        break;
      case '>':
        dp += coms[i].operand;
        break;
      case '<':
        dp -= coms[i].operand;
        break;
      case '.':
        for (int j = 0; j < coms[i].operand; j++) {
          putchar(db[dp]);
        }
        break;
      case ',':
        for (int j = 0; j < coms[i].operand; j++) {
          db[dp] = fgetc(stdin);
        }
        break;
      case '[':
        thisop = coms[i].operand;
        if (db[dp] == 0) {
          while(coms[i].com != ']' || coms[i].operand != thisop) {
            i++;
          }
        }
        break;
      case ']':
        thisop = coms[i].operand;
          while(coms[i].com != '[' || coms[i].operand != thisop) {
            i--;
          }
          i--;
        break;
    }
  }

  free(db);
}

void printcom(struct command com) {
  printf("{com: %c, operand: %d}\n", com.com, com.operand);
}

int main(int argc, char **argv)
{
  struct command *coms = malloc(CMDLEN*sizeof(struct command)); // command buffer
  if (coms == NULL) {
    puts("Command buffer did not created!");
    return -1;
  }
  int cp = 0; // command pointer
  FILE *file;

  if (argc < 2) {
    puts("No arguments!");
    free(coms);
    return -1;
  }
  if (!(file = fopen(argv[1], "r"))) {
    puts("File does not exist!");
    free(coms);
    return -1;
  }

  readc(file, coms, &cp);
  /*
  for (int i = 0; i < cp; i++) {
    printcom(coms[i]);
  }
  */
  interpretate(coms, cp);
  putchar('\n');

  fclose(file);
  free(coms);

  return 0;
}
