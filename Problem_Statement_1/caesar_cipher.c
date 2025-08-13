#include <stdio.h>
#define MAXCHAR 10000
#define SHIFT 3

void take_input(char string[MAXCHAR]) {
  int c, i = 0;
  while ((c = getchar()) != EOF) {
    string[i] = c;
    i++;
  }
  string[i] = '\0';
}

void encode(char INPUT[MAXCHAR], char OUTPUT[MAXCHAR]) {
  int i = 0;
  while (INPUT[i] != '\0') {
    if ((INPUT[i] >= 'a' && INPUT[i] <= 'w') ||
        (INPUT[i] >= 'A' && INPUT[i] <= 'W')) {
      OUTPUT[i] = INPUT[i] + SHIFT;
    } else if ((INPUT[i] >= 'x' && INPUT[i] <= 'z') ||
               (INPUT[i] >= 'X' && INPUT[i] <= 'Z')) {
      OUTPUT[i] = INPUT[i] - 26 + SHIFT;
    } else {
      OUTPUT[i] = INPUT[i];
    }
    i++;
  }
}

void decode(char INPUT[MAXCHAR], char OUTPUT[MAXCHAR]) {
  int i = 0;
  while (INPUT[i] != '\0') {
    if ((INPUT[i] >= 'd' && INPUT[i] <= 'z') ||
        (INPUT[i] >= 'D' && INPUT[i] <= 'Z')) {
      OUTPUT[i] = INPUT[i] - SHIFT;
    } else if ((INPUT[i] >= 'a' && INPUT[i] <= 'c') ||
               (INPUT[i] >= 'A' && INPUT[i] <= 'C')) {
      OUTPUT[i] = INPUT[i] - SHIFT + 26;
    } else {
      OUTPUT[i] = INPUT[i];
    }
    i++;
  }
}

/*We can also use this program as a system utility by piping and combining it with some shell () commands
 To encode a file say caeser_cipher.case 
 bash 
 (echo e && cat caesar_cipher.c) |./a.out | tail -n +3 > encoded.c 

 echo e && cat caeser_cipher.c prints e followed by the contents of the file 
 | means to use the output of the previous command as the input of the next command
 we pipe the file prefixed with a e to our program which will then encode it but it will also print 2 additional line of (Instruction\n) which we remove using the tail -n + 3 command
 finally we use > to put this output into the encoded.c file
 
 Similarly we can use 
 bash
 (echo d && cat encoded.c) | ./a.out | tail -n +3 > decoded.c
  */

int main() {
  char INPUT[MAXCHAR] = {0};
  char OUTPUT[MAXCHAR] = {0};
  char oper;

  printf("Enter \"e\" to encode and \"d\" to decode the cipher : ");
  scanf("%c", &oper);
  printf("Enter Text [Press ctrl D twice to end input]: \n");
  take_input(INPUT);

  switch (oper) {
  case 'e': {
    encode(INPUT, OUTPUT);
    break;
  }
  case 'd': {
    decode(INPUT, OUTPUT);
    break;
  }
  }
  for (int i = 0; OUTPUT[i] != '\0'; i++) {
    putchar(OUTPUT[i]);
  }
}
