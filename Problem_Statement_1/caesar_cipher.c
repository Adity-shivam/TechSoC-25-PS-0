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

void encode(char INPUT[MAXCHAR], char OUTPUT[MAXCHAR], int shift) {
  int i = 0;
  while (INPUT[i] != '\0') {
    if ((INPUT[i] >= 'a' && INPUT[i] <= 'z' - shift) ||
        (INPUT[i] >= 'A' && INPUT[i] <= 'Z' - shift)) {
      OUTPUT[i] = INPUT[i] + shift;
    } else if ((INPUT[i] > 'z' - shift && INPUT[i] <= 'z') ||
               (INPUT[i] > 'Z' - shift && INPUT[i] <= 'Z')) {
      OUTPUT[i] = INPUT[i] - 26 + shift;
    } else {
      OUTPUT[i] = INPUT[i];
    }
    i++;
  }
  OUTPUT[i] = '\0';
}

void decode__(char INPUT[MAXCHAR], char OUTPUT[MAXCHAR], int shift) {
  int i = 0;
  while (INPUT[i] != '\0') {
    if ((INPUT[i] >= 'a' + shift && INPUT[i] <= 'z') ||
        (INPUT[i] >= 'A' + shift && INPUT[i] <= 'Z')) {
      OUTPUT[i] = INPUT[i] - shift;
    } else if ((INPUT[i] >= 'a' && INPUT[i] < 'a' + shift) ||
               (INPUT[i] >= 'A' && INPUT[i] < 'A' + shift)) {
      OUTPUT[i] = INPUT[i] - shift + 26;
    } else {
      OUTPUT[i] = INPUT[i];
    }
    i++;
  }
  OUTPUT[i] = '\0';
}

/*We can also use this program as a system utility by piping and combining it
 with some shell () commands To encode a file say caeser_cipher.c
 bash (echo
 e && cat caesar_cipher.c) |./a.out | tail -n +3 > encoded.c

 echo e && cat caeser_cipher.c prints e followed by the contents of the file
 | means to use the output of the previous command as the input of the next
 command we pipe the file prefixed with a e to our program which will then
 encode it but it will also print 2 additional line of (Instruction\n) which we
 remove using the tail -n + 3 command finally we use > to put this output into
 the encoded.c file

 Similarly we can use
 bash
 (echo d && cat encoded.c) | ./a.out | tail -n +3 > decoded.c
  */

void get_freq(char INPUT[MAXCHAR], double frequency[26]) {

  // make sure to initialize frequency[26] = {0}
  int count = 0;
  for (int i = 0; INPUT[i] != '\0' && i < MAXCHAR; i++) {
    if (INPUT[i] >= 'a' && INPUT[i] <= 'z') {
      frequency[INPUT[i] - 'a']++;
      count++;
    } else if (INPUT[i] >= 'A' && INPUT[i] <= 'Z') {
      frequency[INPUT[i] - 'A']++;
      count++;
    }
  }

  for (int j = 0; j < 26; j++)
    frequency[j] = frequency[j] / count;
}

/* i want to make a function which will match this freq array with actual
   english alphabet data i will use something called chi-squared distance to
   measure deviation from actual frequency

   Found the expex_freq value from
   https://mathcenter.oxford.emory.edu/site/math125/englishLetterFreqs/
   */

double chi_square(double act_freq[26]) {

  double expec_freq[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
                           0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
                           0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                           0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
                           0.01974, 0.00074};

  double chi_square = 0;

  for (int i = 0; i < 26; i++)
    chi_square = chi_square + ((act_freq[i] - expec_freq[i]) *
                               (act_freq[i] - expec_freq[i]) / expec_freq[i]);

  return chi_square;
}

int decode_shift(char string[MAXCHAR]) {

  double shifted_freq[26] = {0};
  char temp[MAXCHAR];
  double variance;
  double minimum;
  int shift = 0;
  int calc_shift = 0;

  decode__(string, temp, shift);
  get_freq(temp, shifted_freq);
  variance = chi_square(shifted_freq);
  minimum = variance;

  for (int shift = 1; shift < 26; shift++) {

    decode__(string, temp, shift);
    get_freq(temp, shifted_freq);
    variance = chi_square(shifted_freq);

    if (variance < minimum) {
      minimum = variance;
      calc_shift = shift;
    }
  }

  return calc_shift;
}

int main() {
  char INPUT[MAXCHAR] = {0};
  char OUTPUT[MAXCHAR] = {0};
  char oper;

  printf("Enter \"e\" to encode and \"d\" to decode the cipher : ");
  scanf("%c", &oper);

  switch (oper) {
  case 'e': {

    printf("enter shift value : ");
    int shift;
    scanf("%d", &shift);
    printf("Enter Text [Press ctrl D twice to end input]: \n");
    take_input(INPUT);
    encode(INPUT, OUTPUT, shift);
    break;
  }
  case 'd': {
    printf("Enter Text [Press ctrl D twice to end input]: \n");
    take_input(INPUT);

    int shift;
    shift = decode_shift(INPUT);
    decode__(INPUT, OUTPUT, shift);

    break;
  }
  }
  for (int i = 0; OUTPUT[i] != '\0'; i++) {
    putchar(OUTPUT[i]);
  }
}
